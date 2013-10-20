#pragma once
#include "IState.h"

class IStateManager
{
public:
   virtual void setDimension(int index, float value)=0;
   virtual void update()=0;
};