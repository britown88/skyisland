#pragma once

#include "IComponent.h"
#include "Text.h"

class TextComponent
{
public:
   static const unsigned int ID = 1823498715;
   TextComponent(std::string str, Float2 drawPos, std::shared_ptr<TextFont> font, Colorf color):
      font(std::move(font)), drawPos(drawPos), color(color), str(std::move(str)){}

   std::shared_ptr<TextFont> font;
   Float2 drawPos;
   Colorf color;
   std::string str;
};
