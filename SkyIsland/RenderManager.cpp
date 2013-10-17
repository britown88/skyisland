#include <GLFW/glfw3.h>

#include "RenderManager.h"
#include "PositionComponent.h"
#include "MeshComponent.h"
#include "Renderables.h"

#include "Renderer.h"

RenderManager::RenderManager()
{
   m_renderer.reset(new Renderer());
   m_renderThread.reset(new RenderThread());
   m_renderThread->start();
}

RenderManager::~RenderManager()
{
   
}

void RenderManager::terminate()
{
   m_renderThread->stop();
}

bool RenderManager::renderViewport(IViewport &vp)
{
   auto &camera = vp.getCamera();
   auto &scene = camera->getScene();

   if(!m_renderer->newScene(vp, *camera))
      return false;

   for(auto ent : scene->getEntities(camera->getBounds()))
   {
      if(ent->hasComponent<MeshComponent>())
      {
         buildMeshRenderable(*ent)->render(*m_renderer); 
      }
   }

   return true;
}

void RenderManager::finalizeRender()
{
   m_renderThread->resetQueue(std::move(m_renderer->drawQueue()));     

}

