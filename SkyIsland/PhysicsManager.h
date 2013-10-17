#pragma once

#include "IScene.h"
#include "Rect.h"
#include "IEntityManager.h"

class PhysicsManager : public IEntityManager
{
public:
   void updateOnScreenEntity(Entity &e);
   void updateOffScreenEntity(Entity &e);

   bool onlyUpdateVisible(){return false;}
};