#pragma once

#include "IComponent.h"
#include "Vector.h"

class GraphicalBoundsComponent : public IComponent
{
public:
   GraphicalBoundsComponent(Float2 size):size(size){}

   Float2 size;
};