#pragma once

#include "IPositionComponent.h"
#include "Vector.h"

class PositionComponent : public IPositionComponent
{
   Float2 m_pos;
public:
   PositionComponent(Float2 pos):m_pos(pos){}

   Float2 getPosition(){return m_pos;}
   void setPosition(Float2 pos){m_pos = pos;}
};