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
   std::weak_ptr<FBO> fbo;
   std::vector<DrawQueue> drawQueue;
   DrawPass(){drawQueue.resize((int)RenderLayer::COUNT);}
   DrawPass(std::weak_ptr<FBO> FBO):fbo(std::move(FBO)){drawQueue.resize((int)RenderLayer::COUNT);}

   DrawPass(DrawPass && ref):fbo(std::move(ref.fbo)), drawQueue(std::move(ref.drawQueue)){}
   DrawPass &operator=(DrawPass && ref){fbo = std::move(ref.fbo); drawQueue = std::move(ref.drawQueue); return *this;}
};

class DrawScene
{
private:   
   std::vector<DrawQueue> m_drawQueue;
   std::vector<DrawPass> m_passes;
   Rectf m_vpBounds;
   Rectf m_camBounds;
   Rectf m_scissorBounds;
   bool m_scissor;

   void renderObjectList(std::vector<DrawQueue> &queues);

public:
   DrawScene(IViewport &vp, ICamera &camera);
   DrawScene(IViewport &vp, ICamera &camera, Rectf scissorBounds);

   void addObjectToPass(IViewport::Pass pass, RenderLayer layer, std::unique_ptr<IDrawObject> obj);
   void addObject(RenderLayer layer, std::unique_ptr<IDrawObject> obj);
   void draw();

};