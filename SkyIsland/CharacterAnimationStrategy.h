#pragma once

#include "IAnimationStrategy.h"
#include "Animations.h"
#include "StringTable.h"

class CharacterAnimationStrategy : public IAnimationStrategy
{
public:
   std::unique_ptr<IAnimation<int>> createAnimation(int frameCount)
   {
      return std::unique_ptr<IAnimation<int>>(new BasicAnimation(frameCount, 0.1f));
   }
};

class BlinkAnimationStrategy : public IAnimationStrategy
{
   std::vector<float> m_frames;
public:
   BlinkAnimationStrategy(float firstFrame, float secndFrame)
   {
      m_frames.push_back(firstFrame);
      m_frames.push_back(secndFrame);
   }

   std::unique_ptr<IAnimation<int>> createAnimation(int frameCount)
   {
      return std::unique_ptr<IAnimation<int>>(new FrameLengthAnimation(std::move(m_frames)));
   }
};
