#pragma once

#include "IViewport.h"
#include "Camera.h"

class Viewport : public IViewport
{
   Rectf m_bounds;
   std::shared_ptr<ICamera> m_camera;

   ViewportList m_children;

public:
   Viewport(Rectf bounds, std::shared_ptr<ICamera> camera);

   std::shared_ptr<ICamera> getCamera();
   Rectf getBounds();

   ViewportList &getChildren();
};