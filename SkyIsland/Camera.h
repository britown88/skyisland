#pragma once

#include "ICamera.h"

class Camera : public ICamera
{
   const IScene& m_scene;
   Rectf m_bounds;

public:
   Camera(Rectf bounds, const IScene& scene);

   const IScene& getScene() const;

   const Rectf getBounds() const;
};