#pragma once

#include "ICamera.h"

class Camera : public ICamera
{
   std::shared_ptr<IScene> m_scene;
   Rectf m_bounds;
   std::unordered_map<Pass, std::shared_ptr<FBO>> m_frameBuffers;

public:
   Camera(Rectf bounds, std::shared_ptr<IScene> scene);
   std::unordered_map<Pass, std::shared_ptr<FBO>> &getFBOs();
    void addFBOPass(Pass passs);

   std::shared_ptr<IScene> getScene();

   Rectf getBounds();
   void setBounds(Rectf bounds);
};