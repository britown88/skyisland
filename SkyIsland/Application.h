#pragma once

#include "GLWindow.h"
#include <memory>
#include <stdlib.h>
#include <time.h>

enum class EntityTag : int
{
   PlayerControlled = 0,
   COUNT
};


class Application : public std::enable_shared_from_this<Application>
{
   std::shared_ptr<Entity> m_taggedEntites[static_cast<int>(EntityTag::COUNT)];

public:
   static const unsigned int ID = 3070040466;
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

   std::shared_ptr<Entity> getTag(EntityTag tag);
   void setTag(EntityTag tag, std::shared_ptr<Entity> entity);

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
