#include <GLFW/glfw3.h>

#include "DrawScene.h"

DrawScene::DrawScene(IViewport &vp, ICamera &camera):
   m_vpBounds(vp.getBounds()), m_camBounds(camera.getBounds())
{}

void DrawScene::addObject(std::unique_ptr<IDrawObject> obj)
{
   m_drawQueue.push_back(std::move(obj));
}

void DrawScene::draw()
{
   glViewport(m_vpBounds.left, m_vpBounds.top, m_vpBounds.right, m_vpBounds.bottom);
   //glScissor(m_vpBounds.left, m_vpBounds.top, m_vpBounds.right, m_vpBounds.bottom);
   //glEnable(GL_SCISSOR_TEST);
   //glClear(GL_COLOR_BUFFER_BIT);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0, m_camBounds.width(), m_camBounds.height(), 0, 1.0f, -1.0f);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   glTranslatef(-m_camBounds.left, -m_camBounds.top, 0.0f);

   for(auto &DO : m_drawQueue)
      DO->draw();
}
