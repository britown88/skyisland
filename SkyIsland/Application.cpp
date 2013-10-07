
#include <GLFW/glfw3.h>
#include "Application.h"

void Application::start()
{
   onAppStart();

   auto winSize = getWindowSize();
   auto winTitle = getWindowTitle();
   auto winMonitor = getWindowMonitor();

   if(winMonitor == NULL)
      m_window.reset(new GLWindow(winSize, winTitle));
   else
      m_window.reset(new GLWindow(winSize, winTitle, winMonitor));

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