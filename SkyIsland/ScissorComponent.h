#pragma once

#include "IComponent.h"
#include "Rect.h"

class ScissorComponent : public IComponent
{
public:
   Rectf bounds;
   bool enable;

   ScissorComponent(bool enable, Rectf bounds = Rectf()):bounds(bounds), enable(enable){}
};