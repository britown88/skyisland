#include <GLFW/glfw3.h>
#include "RenderThread.h"
#include "IOCContainer.h"
#include "GLWindow.h"

RenderThread::RenderThread():
   m_queueUpdated(false),
   m_queueCurrent(Renderer::SceneList(new std::vector<Renderer::DScenePtr>())),
   m_queueFilling(Renderer::SceneList(new std::vector<Renderer::DScenePtr>()))
{
   m_isRunning = false;

   m_texManager = std::make_shared<TextureManager>(100000);
   IOC.add(m_texManager);
}

void RenderThread::_run()
{
   auto &win = IOC.resolve<GLWindow>();
   win.makeContextCurrent();

   while(true)
   {
      glClear(GL_COLOR_BUFFER_BIT);
   
      for(auto& scene : *m_queueCurrent)
         scene->draw();

      win.swapBuffers();

      m_mutex.lock();
      if(m_queueUpdated)
      { 
         m_queueCurrent = std::move(m_queueFilling);
         m_queueUpdated = false;         
      } 
      m_mutex.unlock();

      if(!m_isRunning)
         break;
   }
}

void RenderThread::start()
{
   m_isRunning = true;
   m_thread = std::thread(&RenderThread::_run, this);
}

void RenderThread::stop()
{
   m_isRunning = false;
   m_thread.join();
}

void RenderThread::resetQueue(Renderer::SceneList queue)
{
   m_mutex.lock();
      m_queueFilling = std::move(queue);
      m_queueUpdated = true;
   m_mutex.unlock();
   

}
