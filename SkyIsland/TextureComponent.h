#pragma once

#include "IComponent.h"
#include "StringTable.h"
#include <string>

class TextureComponent : public IComponent
{
public:
   static const int ID = 2790841951;
   TextureComponent(InternString name):texture(name){}

   InternString texture;

};