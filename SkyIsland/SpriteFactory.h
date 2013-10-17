#pragma once

#include "Sprite.h"

class SpriteFactory
{
   std::unordered_map<std::string, std::shared_ptr<Sprite>> m_createdSprites;

public:
   static const int ID = 2909225244;
   std::shared_ptr<Sprite> buildSprite(std::string filepath, float speed);
};