#pragma once

#include "GLWindow.h"
#include "IRenderer.h"
#include "RenderThread.h"
#include "IEntityManager.h"

class RenderManager
{
   std::unique_ptr<IRenderer> m_renderer;
   std::unique_ptr<RenderThread> m_renderThread;
   
public:
   static const int ID = 1432355531;

   RenderManager();
   ~RenderManager();
   
   void finalizeRender();
   bool renderViewport(IViewport &vp); //returns whether VP will be drawn
   void renderEntity(Entity &entity, TransformList transforms);
   void terminate();

};