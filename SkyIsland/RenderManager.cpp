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
#include "GraphicComponents.h"

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
      CompHelpers::updatePositionBind(*ent);

   eList = seanSort(std::move(eList), [&](const std::shared_ptr<Entity> &e1, const std::shared_ptr<Entity> &e2)->bool
   {
      auto bot1 = e1->partitionBounds.bottom;
      auto bot2 = e2->partitionBounds.bottom;

      if(bot1 < bot2) 
         return true;
      if(bot1 > bot2) 
         return false;
      
      return e1 < e2;
   });

   for(auto ent : eList)
   {
      //skip entity if it has a parent and that parent still exists
      if(auto rpc = ent->getComponent<RenderParentComponent>())
         if(rpc->parent.lock())
            continue;

      renderEntity(*ent);
   }
      


   return true;
}

void RenderManager::renderEntity(Entity &entity)
{
   auto childrenComp = entity.getComponent<RenderChildrenComponent>();

   if(childrenComp)
   {
      for(auto child : childrenComp->bgChildren)
         if(auto e = child.lock())
            renderEntity(*e);
   }

   if(auto mc = entity.getComponent<MeshComponent>())
      buildMeshRenderable(entity)->render(*m_renderer); 

   if(auto tc = entity.getComponent<TextComponent>())
      buildTextRenderable(entity)->render(*m_renderer);

   if(childrenComp)
   {
      for(auto child : childrenComp->fgChildren)
         if(auto e = child.lock())
            renderEntity(*e);
   }
      
}

void RenderManager::finalizeRender()
{
   m_renderThread->resetQueue(std::move(m_renderer->drawQueue()));     

}

