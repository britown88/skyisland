#pragma once

#include "IAnimationStrategy.h"
#include "Animations.h"

class CharacterAnimationStrategy : public IAnimationStrategy
{
public:
   std::unique_ptr<IAnimation<int>> createAnimation(const std::string &faceName, int frameCount)
   {
      return std::unique_ptr<IAnimation<int>>(new BasicAnimation(frameCount, 0.1f));
   }
};