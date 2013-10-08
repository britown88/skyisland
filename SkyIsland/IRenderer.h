#pragma once

#include <vector>
#include <memory>
#include "Vertex.h"
#include "IDrawObject.h"
#include "Transform.h"
#include "DrawScene.h"

class IRenderer
{
public:
   typedef std::unique_ptr<DrawScene> DScenePtr;

   virtual ~IRenderer(){}

   virtual void drawTriangles(const std::vector<Vertex> & vertices, const std::vector<int> &faces, Transform transform = Transform()) const=0;

   //clears the drawobject queue
   virtual void clearQueue()=0;
   virtual std::vector<DScenePtr> &drawQueue()=0;
   virtual void newScene(IViewport &vp, ICamera &cam)=0;

};