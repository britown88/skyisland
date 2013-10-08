#include "Renderer.h"

void Renderer::drawTriangles(const std::vector<Vertex> & vertices, const std::vector<int> &faces, Transform transform) const
{
   m_drawQueue.back()->addObject(std::unique_ptr<IDrawObject>(new DrawTriangle(vertices, faces, transform)));
}

std::vector<Renderer::DScenePtr> &Renderer::drawQueue()
{
   return std::move(m_drawQueue);
}

//clears the drawobject queue
void Renderer::clearQueue()
{
   m_drawQueue.clear();
}

void Renderer::newScene(IViewport &vp, ICamera &cam)
{
   m_drawQueue.push_back(Renderer::DScenePtr(new DrawScene(vp, cam)));
}