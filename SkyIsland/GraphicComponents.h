#pragma once

#include "IComponent.h"
#include "Vector.h"
#include "Sprite.h"
#include "StringTable.h"
#include "Entity.h"
#include <memory>

class GraphicalBoundsComponent : public IComponent
{
public:
   static const int ID = 2867340569;

   GraphicalBoundsComponent(Float2 size, Float2 center = Float2()):size(size), center(center){}

   Float2 size, center;
};

class SpriteComponent : public IComponent
{
public:
   static const int ID = 1102563874;
   std::shared_ptr<Sprite> sprite;

   float dtMultiplier, elapsedTime;
   InternString face;

   SpriteComponent(std::shared_ptr<Sprite> sprite, InternString face):
      sprite(std::move(sprite)), dtMultiplier(1.0f), elapsedTime(0.0f), face(face){}

   void updateTime();
   
   
};

//layers are drawn in this order!
//no component = default
enum class RenderLayer
{
   Default,
   DamageMarkers,   
   
   COUNT
};

class LayerComponent : public IComponent
{
public:
   static const int ID = 109205117;
   RenderLayer layer;

   LayerComponent(RenderLayer layer):layer(layer){}

};

class RenderChildrenComponent : public IComponent
{
public:
   static const int ID = 3156851391;

   RenderChildrenComponent(){}

   std::vector<std::weak_ptr<Entity>> bgChildren, fgChildren;
};

class RenderParentComponent : public IComponent
{
public:
   static const int ID = 329001145;

   RenderParentComponent(std::weak_ptr<Entity> parent):parent(std::move(parent)){}

   std::weak_ptr<Entity> parent;
};