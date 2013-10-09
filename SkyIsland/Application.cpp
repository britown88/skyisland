
#include <GLFW/glfw3.h>
#include "Application.h"
#include "RenderManager.h"
#include "KeyHandler.h"
#include "IOCContainer.h"

IOCContainer IOC;

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

   RenderManager *rManager = new RenderManager();
   IOC.add(rManager);

   KeyHandler *kHandler = new KeyHandler();
   IOC.add(kHandler);

   IOC.add(this);

   onAppStart();

   m_appRunning = true;   
}

double Application::getTime()
{
   return glfwGetTime();
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
   delete &IOC.resolve<KeyHandler>();
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

