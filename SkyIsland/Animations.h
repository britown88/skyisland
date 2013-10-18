#pragma once

#include "IAnimation.h"

class BasicAnimation : public IAnimation<int>
{
   int m_frameCount;
   float m_speed;
public:
   BasicAnimation(int frameCount, float speed):
      m_frameCount(frameCount), m_speed(speed){}

   int get(float time){return (int)(time / m_speed) % m_frameCount;}
   float getLength(){return m_speed * m_frameCount;}
   bool isInfinite(){return true;}
   int getFrameCount(){return m_frameCount;}
};