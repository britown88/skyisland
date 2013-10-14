#pragma once

#include "IComponent.h"
#include <string>

class TextureComponent : public IComponent
{
public:
   TextureComponent(std::string name):texture(name){}

   std::string texture;

};