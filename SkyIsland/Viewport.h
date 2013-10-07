#pragma once

#include "IViewport.h"
#include "Camera.h"

class Viewport : public IViewport
{
   Rectf m_bounds;
   const Camera &m_camera;


public:
   Viewport(Rectf bounds, const Camera &camera);

   const ICamera& getCamera();
   Rectf getBounds();
};