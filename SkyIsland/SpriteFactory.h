#pragma once

#include "Sprite.h"
#include "IAnimationStrategy.h"
#include "StringTable.h"

class SpriteFactory
{
public:
   static const int ID = 2909225244;
   std::shared_ptr<Sprite> buildSprite(InternString filepath, IAnimationStrategy &animStrat);
};