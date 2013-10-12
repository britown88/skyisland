#pragma once

#include "ICamera.h"
#include "IViewport.h"
#include "IDrawObject.h"

#include <vector>
#include <memory>

class DrawScene
{
public:
   typedef std::vector<std::unique_ptr<IDrawObject> > DrawQueue;

private:
   DrawQueue m_drawQueue;
   Rectf m_vpBounds;
   Rectf m_camBounds;
   Rectf m_scissorBounds;
   bool m_scissor;

public:
   typedef std::vector<std::unique_ptr<IDrawObject> > DrawQueue;

   DrawScene(IViewport &vp, ICamera &camera);
   DrawScene(IViewport &vp, ICamera &camera, Rectf scissorBounds);

   void addObject(std::unique_ptr<IDrawObject> obj);
   void draw();

};