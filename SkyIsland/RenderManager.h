#pragma once

#include "GLWindow.h"
#include "IRenderer.h"

class RenderManager
{
   GLWindow& m_window;
   std::unique_ptr<IRenderer> m_renderer;
   
public:
   RenderManager(GLWindow &window);

   void render();

};