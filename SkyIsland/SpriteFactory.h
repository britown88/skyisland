#pragma once

#include "Sprite.h"
#include "IAnimationStrategy.h"

class SpriteFactory
{
public:
   static const int ID = 2909225244;
   std::shared_ptr<Sprite> buildSprite(const std::string &filepath, IAnimationStrategy &animStrat);
};