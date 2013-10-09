#include <GLFW/glfw3.h>

#include "RenderManager.h"
#include "PositionComponent.h"
#include "MeshComponent.h"
#include "Renderables.h"

#include "Renderer.h"

RenderManager::RenderManager()
{
   m_renderer.reset(new Renderer());
}

void RenderManager::renderViewport(IViewport &vp)
{
   auto &camera = vp.getCamera();
   auto &scene = camera->getScene();

   m_renderer->newScene(vp, *camera);

   for(auto &ent : scene.getEntities(camera->getBounds()))
   {
      if(ent.hasComponent<MeshComponent>())
         buildMeshRenderable(ent)->render(*m_renderer); 
   }
}

void RenderManager::finalizeRender()
{
   auto &queue = m_renderer->drawQueue();
   
   glClear(GL_COLOR_BUFFER_BIT);
   
   for(auto& scene : queue)
      scene->draw();      

   m_renderer->clearQueue();
}

