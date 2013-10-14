#pragma once

#include "IComponent.h"
#include "Vector.h"
#include "Sprite.h"
#include <memory>

class GraphicalBoundsComponent : public IComponent
{
public:
   GraphicalBoundsComponent(Float2 size, Float2 center = Float2()):size(size), center(center){}

   Float2 size, center;
};

class SpriteComponent : public IComponent
{
public:
   std::shared_ptr<Sprite> sprite;
   float startTime;
   std::string face;

   SpriteComponent(std::shared_ptr<Sprite> sprite, float startTime, std::string face):
      sprite(std::move(sprite)), startTime(startTime), face(face){}
};