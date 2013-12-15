#pragma once

#include <vector>
#include <memory>
#include "Vertex.h"
#include "IDrawObject.h"
#include "Transform.h"
#include "DrawScene.h"
#include "StringTable.h"
#include "Text.h"
#include "GraphicComponents.h"

class IRenderer
{
public:
   typedef std::unique_ptr<DrawScene> DScenePtr;
   typedef std::vector<DScenePtr> SceneList;
   typedef std::unique_ptr<SceneList> SceneListPtr;
   
   virtual ~IRenderer(){}

   virtual void drawTriangles(RenderLayer layer, std::shared_ptr<VertexList> vertices, std::shared_ptr<std::vector<int>> faces, Transform transform = Transform()) const=0;
   virtual void drawTexture(RenderLayer layer, InternString texture, std::shared_ptr<VertexList> vertices, std::shared_ptr<std::vector<int>> faces, Transform transform = Transform()) const=0;
   virtual void drawText(RenderLayer layer, std::shared_ptr<TextString> text, Transform transform=Transform()) const=0;


   virtual SceneListPtr drawQueue()=0;
   virtual bool newScene(IViewport &vp, ICamera &cam)=0; //returns whether new scene will be drawn

};