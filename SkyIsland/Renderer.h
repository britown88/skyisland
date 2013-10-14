#pragma once

#include "IRenderer.h"
#include "IDrawObject.h"
#include "DrawTriangle.h"

#include <vector>
#include <memory>

class Renderer : public IRenderer
{
   SceneList m_drawQueue;

public:
   Renderer();

   void drawTriangles(VertexList vertices, std::vector<int> faces, Transform transform = Transform()) const;
   void drawTexture(std::string texture, VertexList vertices, std::vector<int> faces, Transform transform = Transform()) const;

   SceneList drawQueue();
   bool newScene(IViewport &vp, ICamera &cam);
};