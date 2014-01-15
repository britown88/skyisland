#pragma once

#include "IAnimation.h"
#include <cmath>

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

class FrameLengthAnimation : public IAnimation<int>
{
   std::vector<float> m_frames;
   float m_len;
public:
   FrameLengthAnimation(std::vector<float> &frames):
      m_frames(std::vector<float>(frames))
   {
      m_len = 0.0f;
      for(auto i : m_frames)
         m_len += i;
   }

   int get(float time)
   {
      float currTime = std::fmod(time, m_len);
      float currLen = 0.0f;
      for(int i = 0; i < m_frames.size(); ++i)
      {

         if(currLen <= currTime && (i == m_frames.size() - 1 ||
            (i < m_frames.size() - 1 && m_frames[i+1] > currTime)))
            if(i < m_frames.size())
               return i;

         currLen += m_frames[i];

      }

      return 0;
   }

   float getLength(){return m_len;}
   bool isInfinite(){return true;}
   int getFrameCount(){return m_frames.size();}
};
