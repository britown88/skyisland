#include "CameraController.h"
#include "IPositionComponent.h"
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
void CameraController::followEntity(std::weak_ptr<Entity> entity){m_entity = entity;}

void CameraController::updateCamera()
{
   //if following an entity
   if(auto e = m_entity.lock())
   {
      if(e->hasComponent<IPositionComponent>())
      {
         m_targetPos = e->getComponent<IPositionComponent>().getPosition();

         //center
         if(e->hasComponent<GraphicalBoundsComponent>())
            m_targetPos += e->getComponent<GraphicalBoundsComponent>().size * 0.5f;
      }
   }

   //update positiona ccording to strategy
   if(m_pos != m_targetPos)
      m_pos = m_strategy->moveCamera(m_pos, m_targetPos);


   //clip to world
   if(m_clipToScene)
   {
      if(m_pos.x - (m_camera->getBounds().width() * m_center.x) < 0.0f)
         m_pos.x = m_camera->getBounds().width() * m_center.x;

      if(m_pos.x + (m_camera->getBounds().width() * (1.0f - m_center.x)) >= m_camera->getScene().getSize().x)
         m_pos.x = m_camera->getScene().getSize().x - m_camera->getBounds().width() * (1.0f - m_center.x);
      
      if(m_pos.y - (m_camera->getBounds().height() * m_center.y) < 0.0f)
         m_pos.y = m_camera->getBounds().height() * m_center.y;

      if(m_pos.y + (m_camera->getBounds().height() * (1.0f - m_center.y)) >= m_camera->getScene().getSize().y)
         m_pos.y = m_camera->getScene().getSize().y - m_camera->getBounds().height() * (1.0f - m_center.y);
   
   }

   //set camera bounds
   Rectf newBounds;
   newBounds.left = m_pos.x - m_camera->getBounds().width() * m_center.x;
   newBounds.top = m_pos.y - m_camera->getBounds().height() * m_center.y;
   newBounds.right = newBounds.left + m_camera->getBounds().width();
   newBounds.bottom = newBounds.top + m_camera->getBounds().height();

   m_camera->setBounds(newBounds);
}
