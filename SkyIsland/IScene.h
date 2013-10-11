#pragma once

#include "Vector.h"
#include "Rect.h"
#include "Entity.h"

#include <vector>
#include <memory>

#include "IOCContainer.h"

class IScene
{
public:
   virtual ~IScene(){}
   virtual Float2 getSize() = 0;
   virtual void addEntity(Entity &entity)=0;

   virtual EntityList &getEntities()=0;
   virtual EntityList &getEntities(const Rectf bounds)=0;


};