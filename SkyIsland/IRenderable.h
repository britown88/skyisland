#pragma once

#include "IRenderer.h"

class IRenderable
{
public:
   virtual ~IRenderable(){}
   virtual bool render(const IRenderer &renderer) const=0;
};