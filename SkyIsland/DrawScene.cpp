#include <GLFW/glfw3.h>

#include "DrawScene.h"

DrawScene::DrawScene(IViewport &vp, ICamera &camera):
   m_vpBounds(vp.getBounds()), m_camBounds(camera.getBounds())
{
   m_scissor = false;
}

DrawScene::DrawScene(IViewport &vp, ICamera &camera, Rectf scissorBounds):
   m_vpBounds(vp.getBounds()), m_camBounds(camera.getBounds()), m_scissorBounds(scissorBounds)
{
   m_scissor = true;
}

void DrawScene::addObject(std::unique_ptr<IDrawObject> obj)
{
   m_drawQueue.push_back(std::move(obj));
}

void DrawScene::draw()
{
   glViewport(m_vpBounds.left, m_vpBounds.top, m_vpBounds.right, m_vpBounds.bottom);
   if(m_scissor)
   {
      glScissor(m_scissorBounds.left, m_scissorBounds.top, m_scissorBounds.right, m_scissorBounds.bottom);
      glEnable(GL_SCISSOR_TEST);
   }
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0, m_camBounds.width(), m_camBounds.height(), 0, 1.0f, -1.0f);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();   

   glTranslatef(-m_camBounds.left, -m_camBounds.top, 0.0f);
   for(auto &DO : m_drawQueue)
      DO->draw();

   if(m_scissor)
      glDisable(GL_SCISSOR_TEST);
}
