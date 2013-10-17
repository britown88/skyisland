#pragma once

#include "Vector.h"

class PositionComponent : public IComponent
{
public:
   PositionComponent(Float2 pos):pos(pos){}

   Float2 pos, oldPos;
};