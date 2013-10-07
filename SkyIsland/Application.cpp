
#include <GLFW/glfw3.h>
#include "Application.h"
#include "RenderManager.h"
#include "IOCContainer.h"

void Application::start()
{
   if(!glfwInit())
      throw std::exception("GLFW Failed to initialize");

   auto winSize = getWindowSize();
   auto winTitle = getWindowTitle();
   auto winMonitor = getWindowMonitor();

   if(winMonitor == NULL)
      m_window.reset(new GLWindow(winSize, winTitle));
   else
      m_window.reset(new GLWindow(winSize, winTitle, winMonitor));

   RenderManager *rManager = new RenderManager(*m_window);
   IOC.add(rManager);

   onAppStart();

   m_appRunning = true;   
}

void Application::step()
{
   onStep();

   if(m_window->shouldClose())
         m_appRunning = false;
}

void Application::terminate()
{
   onTerminate();

   delete &IOC.resolve<RenderManager>();
}

bool Application::isRunning()
{
   return m_appRunning;
}

Int2 Application::getWindowSize()
{
   return Int2(800, 600);
}

std::string Application::getWindowTitle()
{
   return "Window Title";
}

GLFWmonitor *Application::getWindowMonitor()
{
   return NULL;
}