#pragma once

#include "Vector.h"
#include "IComponent.h"

class PositionComponent : public IComponent
{
public:
   static const unsigned int ID = 1389350839;
   PositionComponent(Float2 pos):pos(pos) {}

   Float2 pos, oldPos;
};
