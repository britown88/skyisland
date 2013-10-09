#pragma once

#include "ICamera.h"

class Camera : public ICamera
{
   IScene& m_scene;
   Rectf m_bounds;

public:
   Camera(Rectf bounds, IScene& scene);

   IScene& getScene();

   Rectf getBounds();
   void setBounds(Rectf bounds);
};