#pragma once

#include "Vector.h"
#include "Rect.h"
#include "IEntity.h"

#include <vector>

class IScene
{
public:
   virtual Float2 getSize() = 0;
   virtual void addEntity(const IEntity &entity)=0;

   virtual std::vector<IEntity*> getEntities()=0;
   virtual std::vector<IEntity*> getEntities(Rectf bounds)=0;


};