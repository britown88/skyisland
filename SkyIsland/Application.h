#pragma once

#include "GLWindow.h"
#include <memory>
#include <stdlib.h>
#include <time.h> 

class Application : std::enable_shared_from_this<Application>
{
public:
   void start();
   void terminate();
   bool isRunning();
   void step();

   Int2 windowSize();

   double getTime();
   double frameTime();
   double dt();

   int rand(int lower, int upper);

   std::shared_ptr<Application> getptr() {return shared_from_this();}

protected:
   std::shared_ptr<GLWindow> m_window;
   bool m_appRunning;

   double m_frameRate, m_dt, m_lastUpdated;

   virtual Int2 getDefaultWindowSize();
   virtual std::string getWindowTitle();
   virtual GLFWmonitor *getWindowMonitor();

   virtual void onAppStart(){}
   virtual void onStep(){}
   virtual void onTerminate(){}

   
};