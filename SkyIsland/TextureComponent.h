#pragma once

#include "IComponent.h"
#include <string>

class TextureComponent : public IComponent
{
public:
   static const int ID = 2790841951;
   TextureComponent(std::string name):texture(name){}

   std::string texture;

};