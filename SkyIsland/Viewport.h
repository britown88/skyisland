#pragma once

#include "IViewport.h"
#include "Camera.h"

class Viewport : public IViewport
{
   Rectf m_bounds;
   Camera &m_camera;


public:
   Viewport(Rectf bounds, Camera &camera);

   ICamera& getCamera();
   Rectf getBounds();
};