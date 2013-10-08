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
   IViewport &m_viewport;
   ICamera &m_camera;

public:
   typedef std::vector<std::unique_ptr<IDrawObject> > DrawQueue;

   DrawScene(IViewport &vp, ICamera &camera);

   void addObject(std::unique_ptr<IDrawObject> obj);
   void draw();

};