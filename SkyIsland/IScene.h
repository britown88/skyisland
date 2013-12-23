#pragma once

#include "Vector.h"
#include "Rect.h"

#include <vector>
#include <memory>

#include "IOCContainer.h"

class Entity;
class IEntityManager;

class IScene
{
   virtual void addEntity(std::shared_ptr<Entity> entity)=0;
   virtual void removeEntity(std::shared_ptr<Entity> entity)=0;
public:
   friend Entity;

   virtual ~IScene(){}
   virtual Float2 getSize() = 0;

   //add an entitymanager that will get called when the scene is updated
   virtual void registerEntityManager(std::shared_ptr<IEntityManager> em)=0;

   //set the visibility rects within the scene for the next update
   virtual void setVisibleRects(std::vector<Rectf> rects) = 0;

   //update scene entities
   virtual void update() = 0;

   //retrieve entities
   virtual std::vector<std::shared_ptr<Entity>> getEntities()=0;
   virtual std::vector<std::shared_ptr<Entity>> getEntities(Rectf bounds)=0;


};
