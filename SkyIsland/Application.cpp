
#include <GLFW/glfw3.h>
#include "Application.h"
#include "RenderManager.h"
#include "PhysicsManager.h"
#include "KeyHandler.h"
#include "IOCContainer.h"
#include "MouseHandler.h"
#include "TextureManager.h"
#include "ColorFilter.h"
#include "SpriteFactory.h"
#include "StringTable.h"
#include "FBODebugger.h"
#include "SkeletalAnimationsManager.h"
#include "Text.h"

#include <chrono>
#include <thread>

IOCContainer IOC;

void Application::start()
{
   srand (time(NULL));
   m_lastUpdated = 0.0;
   m_dt = 1.0;

   if(!glfwInit())
      throw std::exception("GLFW Failed to initialize");

   auto winSize = getDefaultWindowSize();
   auto winTitle = getWindowTitle();
   auto winMonitor = getWindowMonitor();

   if(winMonitor == NULL)
      m_window.reset(new GLWindow(winSize, winTitle));
   else
      m_window.reset(new GLWindow(winSize, winTitle, winMonitor));

   //global systems
   IOC.add<Application>(getptr());
   IOC.add<GLWindow>(m_window);
   IOC.add<RenderManager>(std::make_shared<RenderManager>());
   IOC.add<KeyHandler>(std::make_shared<KeyHandler>());
   IOC.add<MouseHandler>(std::make_shared<MouseHandler>());
   IOC.add<SpriteFactory>(std::make_shared<SpriteFactory>());
   IOC.add<StringTable>(std::make_shared<StringTable>()); 
   IOC.add<FontEngine>(std::make_shared<FontEngine>());
   IOC.add<ColorFilterManager>(std::make_shared<ColorFilterManager>());
   IOC.add<SkeletalAnimationsManager>(std::make_shared<SkeletalAnimationsManager>());
   buildSkeletalAnimations();
   IOC.add<FBODebugger>(std::make_shared<FBODebugger>());

   onAppStart();

   m_appRunning = true;   
}

Int2 Application::windowSize()
{
   return m_window->getSize();
}

double Application::getTime()
{
   return glfwGetTime();
}

double Application::dt()
{
   return m_dt;
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
   m_lastUpdated = getTime();   

   onStep();

   if(m_window->shouldClose())
         m_appRunning = false;

   double deltaTime = getTime() - m_lastUpdated;
   m_dt = deltaTime / (frameTime() / 1000.0);
   //if(m_dt < 1.0)
      //std::this_thread::sleep_for(std::chrono::milliseconds((long)(frameTime() * m_dt)));
}

std::shared_ptr<Entity> Application::getTag(EntityTag tag)
{
   if(tag < EntityTag::COUNT)
      return m_taggedEntites[(int)tag];
   
   return nullptr;
}

void Application::setTag(EntityTag tag, std::shared_ptr<Entity> entity)
{
   if(tag < EntityTag::COUNT)
      m_taggedEntites[(int)tag] = std::move(entity);
} 

void Application::terminate()
{
   IOC.resolve<RenderManager>()->terminate();

   onTerminate();
}

bool Application::isRunning()
{
   return m_appRunning;
}

Int2 Application::getDefaultWindowSize()
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

