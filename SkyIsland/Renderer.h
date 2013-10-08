#pragma once

#include "IRenderer.h"
#include "IDrawObject.h"
#include "DrawTriangle.h"

#include <vector>
#include <memory>

class Renderer : public IRenderer
{
   std::vector<DScenePtr> m_drawQueue;

public:
   void drawTriangles(const std::vector<Vertex> & vertices, const std::vector<int> &faces, Transform transform = Transform()) const;

   std::vector<DScenePtr> &drawQueue();
   void clearQueue();
   void newScene(IViewport &vp, ICamera &cam);
};