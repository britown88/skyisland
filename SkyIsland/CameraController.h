#pragma once

#include "ICamera.h"
#include "Vector.h"
#include "Entity.h"

class CameraController
{
   std::shared_ptr<ICamera> m_camera;
   Float2 m_pos, m_targetPos, m_center;
   std::weak_ptr<Entity> m_entity;
   std::unique_ptr<ICameraMoveStrategy> m_strategy;

   bool m_clipToScene;
   
public:
   CameraController(std::shared_ptr<ICamera> camera, std::unique_ptr<ICameraMoveStrategy> strategy);

   void updateCamera();
   void followEntity(std::weak_ptr<Entity> entity);
   void stopFollowing();
   void setTarget(Float2 pos);
   void moveToTarget();
   void setClipToSceneBounds(bool clip);
   void setCameraCenter(Float2 center);//0.0 - 1.0
};