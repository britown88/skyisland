#include <GLFW/glfw3.h>

#include "RenderManager.h"
#include "PositionComponent.h"
#include "GraphicsComponent.h"

#include "Renderer.h"

RenderManager::RenderManager(GLWindow &window):m_window(window)
{
   m_renderer.reset(new Renderer());
}

void RenderManager::render()
{
   auto vps = m_window.getViewports();

   for(auto vp : vps)
   {
      const ICamera *camera = &vp->getCamera();
      IScene *scene = (IScene *)&camera->getScene();

      for(auto &ent : *scene->getEntities(camera->getBounds()))
      {
         if(ent.hasComponent<PositionComponent>() && ent.hasComponent<GraphicsComponent>())
         {
            auto g = ent.getComponent<GraphicsComponent>();
            auto p = ent.getComponent<PositionComponent>();

            g.getRenderable().render(p.getPosition(), *m_renderer);            
         }
      }

      auto doList = m_renderer->getDrawQueue();

      glViewport(vp->getBounds().left, vp->getBounds().top, vp->getBounds().right, vp->getBounds().bottom);
      glClear(GL_COLOR_BUFFER_BIT);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

      for(auto DO : *doList)
         DO->draw();

      m_window.swapBuffers();

      m_renderer->clearQueue();
   }
}