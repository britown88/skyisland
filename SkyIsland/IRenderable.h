#pragma once

#include "IRenderer.h"

class IRenderable
{
public:
   virtual ~IRenderable(){}
   virtual void render(Float2 drawPos, const IRenderer &renderer) const=0;
};