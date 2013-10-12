#pragma once

#include "ICamera.h"

class Camera : public ICamera
{
   std::shared_ptr<IScene> m_scene;
   Rectf m_bounds;

public:
   Camera(Rectf bounds, std::shared_ptr<IScene> scene);

   std::shared_ptr<IScene> getScene();

   Rectf getBounds();
   void setBounds(Rectf bounds);
};