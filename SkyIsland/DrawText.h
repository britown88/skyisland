#pragma once

#include "IDrawObject.h"

#include <memory>
#include "Transform.h"
#include "Text.h"

class DrawText : public IDrawObject
{
   std::shared_ptr<TextString> m_text;
   Transform m_transform;

public:
   DrawText(std::shared_ptr<TextString> text, Transform transform=Transform());

   void draw();

};