#pragma once

#include "IComponent.h"
#include "Vector.h"
#include "Sprite.h"
#include "StringTable.h"
#include "Entity.h"
#include <memory>
#include <set>
#include <deque>

class GraphicalBoundsComponent : public IComponent
{
public:
   static const unsigned int ID = 2867340569;

   GraphicalBoundsComponent(Float2 size, Float2 center = Float2()):size(size), center(center){}

   Float2 size, center;
};

//add to entity to designate it as a light source
class LightComponent : public IComponent
{
public:
   static const int unsigned ID = 3308791299;
};

class SpriteComponent : public IComponent
{
public:
   static const int unsigned ID = 1102563874;
   std::shared_ptr<Sprite> sprite;

   float dtMultiplier, elapsedTime;
   InternString face;

   SpriteComponent(std::shared_ptr<Sprite> sprite, InternString face):
      sprite(std::move(sprite)), dtMultiplier(1.0f), elapsedTime(0.0f), face(face){}

   void updateTime();


};

//used to keep faces and animspeed in sprites synced between two entities
class BindAnimationComponent : public IComponent
{
public:
   static const unsigned int ID = 1563562358;

   BindAnimationComponent(std::weak_ptr<Entity> entity):entity(std::move(entity)){}
   std::weak_ptr<Entity> entity;
};

//layers are drawn in this order!
//no component = default
enum class RenderLayer
{
   Backdrop,
   Default,
   DamageMarkers,

   COUNT
};

class LayerComponent : public IComponent
{
public:
   static const unsigned int ID = 109205117;
   RenderLayer layer;

   LayerComponent(RenderLayer layer):layer(layer){}

};


typedef std::deque<std::shared_ptr<Entity>>::iterator ParentIter;


class RenderParentComponent : public IComponent
{
public:
   static const unsigned int ID = 329001145;

   RenderParentComponent(std::shared_ptr<Entity> parent):parent(std::move(parent)){}

   std::shared_ptr<Entity> parent;
   ParentIter parentIter;
};

class RenderChildrenComponent : public IComponent
{
public:
   static const unsigned int ID = 3156851391;
   int parentIndex;


   RenderChildrenComponent():parentIndex(0){}

   std::deque<std::shared_ptr<Entity>> children;

   enum class Layer
   {
      Foreground,
      Background
   };

   void removeChild(ParentIter child)
   {
      if(child - children.begin() < parentIndex)
         --parentIndex;

      children.erase(child);
   }

   void addChild(std::shared_ptr<Entity> parent, std::shared_ptr<Entity> child, Layer layer)
   {
      ParentIter iter;

      if(layer == Layer::Background)
      {
         children.insert(children.begin() + parentIndex, child);
         iter = children.begin() + parentIndex++;
      }
      else
      {
         children.push_back(child);
         iter = children.end() - 1;
      }


      if(auto rpc = child->getComponent<RenderParentComponent>())
      {
         rpc->parent = parent;
         rpc->parentIter = iter;
      }
      else
      {
         auto newParentComp = std::make_shared<RenderParentComponent>(parent);
         newParentComp->parentIter = iter;
         child->addComponent<RenderParentComponent>(newParentComp);

      }

   }

};

