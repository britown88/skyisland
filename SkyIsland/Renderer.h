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

   void addObjectToScene(ICamera::Pass pass, RenderLayer layer, std::unique_ptr<IDrawObject> DO) const;

public:
   Renderer();

   void drawTriangles(ICamera::Pass pass, RenderLayer layer, std::shared_ptr<VertexList> vertices, std::shared_ptr<std::vector<int>> faces, Transform transform = Transform()) const;
   void drawTexture(ICamera::Pass pass, RenderLayer layer, InternString texture, std::shared_ptr<VertexList> vertices, std::shared_ptr<std::vector<int>> faces, Transform transform = Transform()) const;
   void drawText(ICamera::Pass pass, RenderLayer layer, std::shared_ptr<TextString> text, Transform transform=Transform()) const;

   SceneListPtr drawQueue();
   bool newScene(IViewport &vp, ICamera &cam);
};