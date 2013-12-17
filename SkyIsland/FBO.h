#pragma once

#include "Rect.h"

class FBO
{
   unsigned int m_fboHandle, m_texHandle;
   Rectf m_bounds;

public:
   FBO(Rectf bounds);
   ~FBO();

   void bind();
   void render();
};