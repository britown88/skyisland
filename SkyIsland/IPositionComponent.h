#pragma once

#include "IComponent.h"
#include "Vector.h"

class IPositionComponent : public IComponent
{
public:
   virtual Float2 getPosition()=0;
   virtual void setPosition(Float2 pos)=0;
};