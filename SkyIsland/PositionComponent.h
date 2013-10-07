#pragma once

#include "IComponent.h"
#include "Vector.h"

class PositionComponent : public IComponent
{
   Float2 m_pos;
public:
   PositionComponent(Float2 pos):m_pos(pos){}

   Float2 getPosition(){return m_pos;}
};