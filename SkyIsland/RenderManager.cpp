#include <GLFW/glfw3.h>

#include "RenderManager.h"
#include "PositionComponent.h"
#include "MeshComponent.h"
#include "Renderables.h"

#include "Renderer.h"
#include "ComponentHelpers.h"
#include "SeanSort.h"
#include "PhysicsComponents.h"
#include "TextComponent.h"

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

   for(auto ent : eList)
   {
      if(auto p = ent->getComponent<PositionComponent>())
      if(auto bind = ent->getComponent<PositionBindComponent>())
      if(auto bindEntity = bind->entity.lock())
      if(auto bindPos = bindEntity->getComponent<PositionComponent>())
      {
         p->pos = bindPos->pos + bind->offset;
         if(auto elev = bindEntity->getComponent<ElevationComponent>())
            p->pos.y -= elev->elevation;
      }
   }

   eList = seanSort(std::move(eList), [&](const std::shared_ptr<Entity> &e1, const std::shared_ptr<Entity> &e2)->bool
   {
      auto bot1 = CompHelpers::getEntityBounds(*e1).bottom;
      auto bot2 = CompHelpers::getEntityBounds(*e2).bottom;
      float layer1 = 0.0f, layer2 = 0.0f;

      if(auto pc1 = e1->getComponent<PositionComponent>()) layer1 = pc1->layer;
      if(auto pc2 = e2->getComponent<PositionComponent>()) layer2 = pc2->layer;         

      if(bot1 < bot2 || layer1 < layer2) 
         return true;
      if(bot1 > bot2 || layer1 > layer2) 
         return false;
      
      return e1 < e2;
   });

   for(auto ent : eList)
   {
      if(auto mc = ent->getComponent<MeshComponent>())
         buildMeshRenderable(*ent)->render(*m_renderer); 

      if(auto tc = ent->getComponent<TextComponent>())
         buildTextRenderable(*ent)->render(*m_renderer);
   }

   return true;
}

void RenderManager::finalizeRender()
{
   m_renderThread->resetQueue(std::move(m_renderer->drawQueue()));     

}

