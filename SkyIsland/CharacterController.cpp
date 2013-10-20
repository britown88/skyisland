#include "CharacterController.h"
#include "PhysicsComponents.h"
#include "GraphicComponents.h"
#include "Animations.h"
#include "IOCContainer.h"
#include "Application.h"

CharacterController::CharacterController(std::weak_ptr<Entity> entity):
   m_entity(std::move(entity))
{
   m_accel = 0.5f;
   m_runAccel = 1.0f;
   m_maxVelocity = 10.0f;
   m_friction = 0.5f;
   m_minAnimSpeed = 0.09f;
   m_maxAnimSpeed = 0.5f;
}


void CharacterController::move(Float2 vector)
{
   if(vector != Float2()) 
      m_facing = vector;

   if(auto e = m_entity.lock())
   {
      if(auto ac = e->getComponent<AccelerationComponent>())
      if(auto fc = e->getComponent<FrictionComponent>())
      {
         fc->friction = 0.0f;
         ac->direction = vector;
         ac->acceleration = m_accel;
         ac->maxVelocity = m_maxVelocity;
      }
   }
   
}

void CharacterController::stop()
{
   if(auto e = m_entity.lock())
   {
      if(auto ac = e->getComponent<AccelerationComponent>())
      if(auto fc = e->getComponent<FrictionComponent>())
      {
         fc->friction = m_friction;
         ac->acceleration = 0.0f;
      }
   }
}

void CharacterController::updateAnimation()
{
   if(auto e = m_entity.lock())
   {
      if(auto ac = e->getComponent<AccelerationComponent>())
      if(auto fc = e->getComponent<FrictionComponent>())
      if(auto vc = e->getComponent<VelocityComponent>())
      if(auto spr = e->getComponent<SpriteComponent>())
      {
         if(vc->velocity == Float2())
         {
            //stopped, set face
            if(fabs(m_facing.x) > fabs(m_facing.y))
               spr->face = m_facing.x >= 0.0f ? "stand_right" : "stand_left";
            else
               spr->face = m_facing.y >= 0.0f ? "stand_up" : "stand_down";
         }
         else
         {
            //moving, set face
            if(fabs(vc->velocity.x) > fabs(vc->velocity.y))
               spr->face = vc->velocity.x >= 0.0f ? "run_right" : "run_left";
            else
               spr->face = vc->velocity.y >= 0.0f ? "run_down" : "run_up";

            //now reset anim speed base don velocity
            auto &v = vc->velocity;
            float mag = v.x * v.x + v.y * v.y;
           
            spr->dtMultiplier = mag / (ac->maxVelocity * ac->maxVelocity);
            
         }
      }
   }
}