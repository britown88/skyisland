#pragma once

#include "GLWindow.h"
#include <memory>
#include <stdlib.h>
#include <time.h> 

class Application
{
public:
   void start();
   void terminate();
   bool isRunning();
   void step();

   double getTime();
   double frameTime();

   int rand(int lower, int upper);

protected:
   std::unique_ptr<GLWindow> m_window;
   bool m_appRunning;

   double m_frameRate;

   virtual Int2 getWindowSize();
   virtual std::string getWindowTitle();
   virtual GLFWmonitor *getWindowMonitor();

   virtual void onAppStart(){}
   virtual void onStep(){}
   virtual void onTerminate(){}

   
};