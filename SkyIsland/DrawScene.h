#pragma once

#include "ICamera.h"
#include "IViewport.h"
#include "IDrawObject.h"
#include "GraphicComponents.h"
#include "FBO.h"

#include <vector>
#include <memory>

typedef std::vector<std::unique_ptr<IDrawObject>> DrawQueue;

struct DrawPass
{
   std::unique_ptr<FBO> fbo;
   DrawQueue drawQueue[RenderLayer::COUNT];
};

class DrawScene
{
private:   
   DrawQueue m_drawQueue[RenderLayer::COUNT];
   DrawPass m_passes[IViewport::Pass::COUNT];
   Rectf m_vpBounds;
   Rectf m_camBounds;
   Rectf m_scissorBounds;
   bool m_scissor;

   void renderObjectList(DrawQueue *queues);

public:
   DrawScene(IViewport &vp, ICamera &camera);
   DrawScene(IViewport &vp, ICamera &camera, Rectf scissorBounds);

   void addObjectToPass(IViewport::Pass pass, RenderLayer layer, std::unique_ptr<IDrawObject> obj);
   void addObject(RenderLayer layer, std::unique_ptr<IDrawObject> obj);
   void draw();

};