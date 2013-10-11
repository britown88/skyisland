
#include <GLFW/glfw3.h>
#include "Application.h"
#include "RenderManager.h"
#include "KeyHandler.h"
#include "IOCContainer.h"
#include "MouseHandler.h"

IOCContainer IOC;

void Application::start()
{
   srand (time(NULL));

   if(!glfwInit())
      throw std::exception("GLFW Failed to initialize");

   auto winSize = getWindowSize();
   auto winTitle = getWindowTitle();
   auto winMonitor = getWindowMonitor();

   if(winMonitor == NULL)
      m_window.reset(new GLWindow(winSize, winTitle));
   else
      m_window.reset(new GLWindow(winSize, winTitle, winMonitor));

   //global systems
   IOC.add<GLWindow>(m_window);
   IOC.add<RenderManager>(std::make_shared<RenderManager>());
   IOC.add<KeyHandler>(std::make_shared<KeyHandler>());
   IOC.add<MouseHandler>(std::make_shared<MouseHandler>());
   IOC.add<Application>(getptr());


   onAppStart();

   m_appRunning = true;   
}

double Application::getTime()
{
   return glfwGetTime();
}

double Application::frameTime()
{
   return 1000.0 / m_frameRate;
}

int Application::rand(int lower, int upper)
{
   return (::rand() % (upper - lower)) + lower;
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

