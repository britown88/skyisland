#pragma once

template <typename T>
class IAnimation
{
public:
   virtual T get(float time)=0;
   virtual float getLength()=0;
   virtual bool isInfinite()=0;
   virtual int getFrameCount()=0;
};