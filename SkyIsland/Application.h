#pragma once

#include "GLWindow.h"
#include <memory>

class Application
{
public:
   void start();
   void terminate();
   bool isRunning();
   void step();

   double getTime();

protected:
   std::unique_ptr<GLWindow> m_window;
   bool m_appRunning;

   virtual Int2 getWindowSize();
   virtual std::string getWindowTitle();
   virtual GLFWmonitor *getWindowMonitor();

   virtual void onAppStart(){}
   virtual void onStep(){}
   virtual void onTerminate(){}

   
};