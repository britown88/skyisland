#pragma once

#include "IRenderer.h"
#include "IDrawObject.h"
#include "DrawTriangle.h"
#include "StringTable.h"

#include <vector>
#include <memory>

class Renderer : public IRenderer
{
   SceneList m_drawQueue;

public:
   Renderer();

   void drawTriangles(std::shared_ptr<VertexList> vertices, std::shared_ptr<std::vector<int>> faces, Transform transform = Transform()) const;
   void drawTexture(InternString texture, std::shared_ptr<VertexList> vertices, std::shared_ptr<std::vector<int>> faces, Transform transform = Transform()) const;


   SceneList drawQueue();
   bool newScene(IViewport &vp, ICamera &cam);
};