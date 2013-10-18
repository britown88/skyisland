#pragma once

#include "IAITask.h"
#include "IOCContainer.h"
#include "Application.h"
#include <memory>

class WaitTask : public IAITask
{
   double m_waitTime, m_startTime;
public:
   WaitTask(double waitTime):m_waitTime(waitTime){}

   void start(){m_startTime = IOC.resolve<Application>()->getTime();}
   void update(){}
   void halt(){}
   bool isDone(){return IOC.resolve<Application>()->getTime() - m_startTime >= m_waitTime;}
   int getPriority(){ return 0; }
};