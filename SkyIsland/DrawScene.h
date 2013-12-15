#pragma once

#include "ICamera.h"
#include "IViewport.h"
#include "IDrawObject.h"
#include "GraphicComponents.h"

#include <vector>
#include <memory>

class DrawScene
{
public:
   typedef std::vector<std::unique_ptr<IDrawObject>> DrawQueue;

private:
   DrawQueue m_drawQueue[RenderLayer::COUNT];
   Rectf m_vpBounds;
   Rectf m_camBounds;
   Rectf m_scissorBounds;
   bool m_scissor;

public:
   DrawScene(IViewport &vp, ICamera &camera);
   DrawScene(IViewport &vp, ICamera &camera, Rectf scissorBounds);

   void addObject(RenderLayer layer, std::unique_ptr<IDrawObject> obj);
   void draw();

};