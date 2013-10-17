#include <GLFW/glfw3.h>

#include "RenderManager.h"
#include "PositionComponent.h"
#include "MeshComponent.h"
#include "Renderables.h"

#include "Renderer.h"
#include "ComponentHelpers.h"
#include "SeanSort.h"

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

   auto eList = scene->getEntities(camera->getBounds());
   eList = seanSort(std::move(eList), [&](const std::shared_ptr<Entity> &e1, const std::shared_ptr<Entity> &e2)->bool
   {
      auto bot1 = CompHelpers::getEntityBounds(*e1).bottom;
      auto bot2 = CompHelpers::getEntityBounds(*e2).bottom;
      if(bot1 < bot2) 
         return true;
      if(bot1 > bot2) 
         return false;
      
      return e1 < e2;
   });

   for(auto ent : eList)
   {
      if(camera->getBounds().contains(CompHelpers::getEntityBounds(*ent)))
      {
         if(auto mc = ent->getComponent<MeshComponent>())
            buildMeshRenderable(*ent)->render(*m_renderer); 
      }
   }

   return true;
}

void RenderManager::finalizeRender()
{
   m_renderThread->resetQueue(std::move(m_renderer->drawQueue()));     

}

