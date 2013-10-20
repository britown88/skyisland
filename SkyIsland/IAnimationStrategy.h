#pragma once

#include "IAnimation.h"
#include <memory>
#include <string>

class IAnimationStrategy
{
public:
   virtual ~IAnimationStrategy(){}

   virtual std::unique_ptr<IAnimation<int>> createAnimation(const std::string &faceName, int frameCount)=0;
};