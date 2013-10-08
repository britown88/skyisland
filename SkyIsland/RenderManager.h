#pragma once

#include "GLWindow.h"
#include "IRenderer.h"

class RenderManager
{
   std::unique_ptr<IRenderer> m_renderer;
   
public:
   RenderManager();

   void finalizeRender();
   void renderViewport(IViewport &vp);

};