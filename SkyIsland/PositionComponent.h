#pragma once

#include "Vector.h"
#include "IComponent.h"

class PositionComponent : public IComponent
{
public:
   static const int ID = 1389350839;
   PositionComponent(Float2 pos, float layer = 0.0f):pos(pos), layer(layer){}

   Float2 pos, oldPos;
   float layer;
};