#include "Renderer.h"

Renderer::Renderer():m_drawQueue(SceneList(new std::vector<DScenePtr>()))
{   
}

void Renderer::drawTriangles(const std::vector<Vertex> & vertices, const std::vector<int> &faces, Transform transform) const
{
   m_drawQueue->back()->addObject(std::unique_ptr<IDrawObject>(new DrawTriangle(vertices, faces, transform)));
}

Renderer::SceneList Renderer::drawQueue()
{
   auto ret = std::move(m_drawQueue);

   m_drawQueue.reset(new std::vector<DScenePtr>());
   return ret;
}


void Renderer::newScene(IViewport &vp, ICamera &cam)
{
   m_drawQueue->push_back(Renderer::DScenePtr(new DrawScene(vp, cam)));
}