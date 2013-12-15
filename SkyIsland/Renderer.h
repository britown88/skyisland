#pragma once

#include "IRenderer.h"
#include "IDrawObject.h"
#include "DrawTriangle.h"
#include "StringTable.h"

#include <vector>
#include <memory>

class Renderer : public IRenderer
{
   SceneListPtr m_drawQueue;

public:
   Renderer();

   void drawTriangles(RenderLayer layer, std::shared_ptr<VertexList> vertices, std::shared_ptr<std::vector<int>> faces, Transform transform = Transform()) const;
   void drawTexture(RenderLayer layer, InternString texture, std::shared_ptr<VertexList> vertices, std::shared_ptr<std::vector<int>> faces, Transform transform = Transform()) const;
   void drawText(RenderLayer layer, std::shared_ptr<TextString> text, Transform transform=Transform()) const;

   SceneListPtr drawQueue();
   bool newScene(IViewport &vp, ICamera &cam);
};