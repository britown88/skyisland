#pragma once

#include "IRenderer.h"

class IRenderable
{
public:
   virtual ~IRenderable(){}
   virtual void render(const IRenderer &renderer) const=0;
};