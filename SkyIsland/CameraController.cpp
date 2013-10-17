#include "CameraController.h"
#include "PositionComponent.h"
#include "GraphicComponents.h"

CameraController::CameraController(std::shared_ptr<ICamera> camera, std::unique_ptr<ICameraMoveStrategy> strategy)
   :m_camera(camera), m_strategy(std::move(strategy))
{
   m_clipToScene = true;
}

void CameraController::stopFollowing(){m_entity.reset();}
void CameraController::setTarget(Float2 pos){m_targetPos = pos;}
void CameraController::moveToTarget(){m_pos = Float2(m_targetPos.x, m_targetPos.y);}
void CameraController::setClipToSceneBounds(bool clip){m_clipToScene = clip;}
void CameraController::setCameraCenter(Float2 center){m_center = center;}
void CameraController::followEntity(std::weak_ptr<Entity> entity){m_entity = entity; updateCamera();}

void CameraController::targetEntity()
{
   //if following an entity
   if(auto e = m_entity.lock())
      if(auto pc = e->getComponent<PositionComponent>())
         m_targetPos = pc->pos;
}

void CameraController::updateCamera()
{
   
   targetEntity();

   //update positiona ccording to strategy
   m_pos = m_strategy->moveCamera(m_pos, m_targetPos);

   //set camera bounds
   Rectf newBounds;
   newBounds.left = m_pos.x - m_camera->getBounds().width() * m_center.x;
   newBounds.top = m_pos.y - m_camera->getBounds().height() * m_center.y;
   newBounds.right = newBounds.left + m_camera->getBounds().width();
   newBounds.bottom = newBounds.top + m_camera->getBounds().height();

   //clip to world
   if(m_clipToScene)
   {
      if(newBounds.left < 0) newBounds.offset(Float2(-newBounds.left, 0.0f));
      if(newBounds.top < 0) newBounds.offset(Float2(0.0f, -newBounds.top));
      if(newBounds.right >= m_camera->getScene()->getSize().x) newBounds.offset(Float2(-(newBounds.right - m_camera->getScene()->getSize().x), 0.0f));
      if(newBounds.bottom >= m_camera->getScene()->getSize().y) newBounds.offset(Float2(0.0f, -(newBounds.bottom - m_camera->getScene()->getSize().y)));
   }

   m_camera->setBounds(newBounds);
}
