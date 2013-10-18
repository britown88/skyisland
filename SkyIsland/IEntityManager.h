#pragma once

#include "Entity.h"

class IEntityManager
{
public:
   virtual void updateOnScreenEntity(Entity &e)=0;
   virtual void updateOffScreenEntity(Entity &e)=0;

};