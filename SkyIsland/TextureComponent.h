#pragma once

#include "IComponent.h"
#include "StringTable.h"
#include "Vector.h"
#include <string>

class TextureComponent : public IComponent
{
public:
   static const int ID = 2790841951;
   unsigned int blendS, blendD;
   TextureComponent(InternString name);
   void setBlendFunc(unsigned int sFactor, unsigned int dFactor){blendS = sFactor; blendD = dFactor;}

   InternString texture;
   Float2 size;
   bool yFlipped, xFlipped;

};