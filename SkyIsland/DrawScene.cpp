#include <GLFW/glfw3.h>

#include "DrawScene.h"

DrawScene::DrawScene(IViewport &vp, ICamera &camera):
m_viewport(vp), m_camera(camera)
{}

void DrawScene::addObject(std::unique_ptr<IDrawObject> obj)
{
   m_drawQueue.push_back(std::move(obj));
}

void DrawScene::draw()
{
   auto vpBounds = m_viewport.getBounds();
   auto camBounds = m_camera.getBounds();

   glViewport(vpBounds.left, vpBounds.top, vpBounds.right, vpBounds.bottom);
   glClear(GL_COLOR_BUFFER_BIT);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0, camBounds.width(), camBounds.height(), 0, 1.0f, -1.0f);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   glTranslatef(-camBounds.left, -camBounds.top, 0.0f);

   for(auto &DO : m_drawQueue)
      DO->draw();
}
