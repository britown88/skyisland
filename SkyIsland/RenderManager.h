#pragma once

#include "GLWindow.h"
#include "IRenderer.h"
#include "RenderThread.h"

class RenderManager
{
   std::unique_ptr<IRenderer> m_renderer;
   std::unique_ptr<RenderThread> m_renderThread;
   
public:
   RenderManager();
   ~RenderManager();
   
   void finalizeRender();
   void renderViewport(IViewport &vp);

};