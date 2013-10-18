#pragma once

class IAITask
{
public:
   virtual void start()=0;
   virtual void update()=0;
   virtual void halt()=0;
   virtual bool isDone()=0;
   virtual int getPriority()=0;
};