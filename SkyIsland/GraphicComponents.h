#pragma once

#include "IComponent.h"
#include "Vector.h"

class GraphicalBoundsComponent : public IComponent
{
public:
   GraphicalBoundsComponent(Float2 size, Float2 center = Float2()):size(size), center(center){}

   Float2 size, center;
};