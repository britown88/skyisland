#include <GLFW/glfw3.h>

#include "CharacterController.h"

#include "IOCContainer.h"

#include "PhysicsComponents.h"


CharacterController::CharacterController(std::weak_ptr<Entity> entity):
   m_entity(entity)
{
   m_accel = 1.0f;
   m_runAccel = 1.0f;
   m_maxVelocity = 10.0f;
   m_friction = 0.5f;

   upPressed = false;
   downPressed = false;
   leftPressed = false;
   rightPressed = false;

   
   registerKeyEvent(Keystroke(GLFW_KEY_RIGHT, GLFW_PRESS, 0), KeyEvent([&](){this->onRightPress();}));
   registerKeyEvent(Keystroke(GLFW_KEY_RIGHT, GLFW_RELEASE, 0), KeyEvent([&](){this->onRightRelease();}));   
   registerKeyEvent(Keystroke(GLFW_KEY_LEFT, GLFW_PRESS, 0), KeyEvent([&](){this->onLeftPress();}));
   registerKeyEvent(Keystroke(GLFW_KEY_LEFT, GLFW_RELEASE, 0), KeyEvent([&](){this->onLeftRelease();}));
   registerKeyEvent(Keystroke(GLFW_KEY_UP, GLFW_PRESS, 0), KeyEvent([&](){this->onUpPress();}));
   registerKeyEvent(Keystroke(GLFW_KEY_UP, GLFW_RELEASE, 0), KeyEvent([&](){this->onUpRelease();}));
   registerKeyEvent(Keystroke(GLFW_KEY_DOWN, GLFW_PRESS, 0), KeyEvent([&](){this->onDownPress();}));
   registerKeyEvent(Keystroke(GLFW_KEY_DOWN, GLFW_RELEASE, 0), KeyEvent([&](){this->onDownRelease();}));

}

void CharacterController::registerKeyEvent(Keystroke k, KeyEvent e)
{
   m_events.push_back(std::move(e));
   IOC.resolve<KeyHandler>().registerEvent(k, &m_events[m_events.size()-1]);
}

void CharacterController::onUpPress()
{
   if(auto e = m_entity.lock())
   {
      auto &a = e->getComponent<AccelerationComponent>();
      e->getComponent<FrictionComponent>().friction = m_friction / 2.0f;

      a.acceleration = m_accel;

      a.direction = 90.0f;
      upPressed = true;
      downPressed = false;
      
      if(leftPressed)
         a.direction = 135.0f; 
      else if(rightPressed)
         a.direction = 45.0f;   
   }
   
}

void CharacterController::onUpRelease()
{
   if(auto e = m_entity.lock())
   if(upPressed)
   {
      auto &a = e->getComponent<AccelerationComponent>();
      upPressed = false;
      if(leftPressed)
         a.direction = 180.0f; 
      else if(rightPressed)
         a.direction = 0.0f;
      else
      {
         a.acceleration = 0.0f;
         e->getComponent<FrictionComponent>().friction = m_friction;
      }
         
   }
}

void CharacterController::onLeftPress()
{
   if(auto e = m_entity.lock())
   {
      auto &a = e->getComponent<AccelerationComponent>();
      e->getComponent<FrictionComponent>().friction = m_friction / 2.0f;

      a.acceleration = m_accel;
      a.direction = 180.0f;
      leftPressed = true;
      rightPressed = false;
      
      if(upPressed)
         a.direction = 135.0f; 
      else if(downPressed)
         a.direction = 225.0f;   
   }

}

void CharacterController::onLeftRelease()
{
   if(auto e = m_entity.lock())
   if(leftPressed)
   {
      auto &a = e->getComponent<AccelerationComponent>();
      leftPressed = false;
      if(upPressed)
         a.direction = 90.0f; 
      else if(downPressed)
         a.direction = 270.0f;
      else
      {
         a.acceleration = 0.0f;
         e->getComponent<FrictionComponent>().friction = m_friction;
      }
   }
}

void CharacterController::onDownPress()
{
   if(auto e = m_entity.lock())
   {
      auto &a = e->getComponent<AccelerationComponent>();
      e->getComponent<FrictionComponent>().friction = m_friction / 2.0f;

      a.acceleration = m_accel;
      a.direction = 270.0f;
      downPressed = true;
      upPressed = false;
      
      if(leftPressed)
         a.direction = 225.0f; 
      else if(rightPressed)
         a.direction = 315.0f; 
   }
     
}

void CharacterController::onDownRelease()
{   
   if(auto e = m_entity.lock())
   if(downPressed)
   {
      auto &a = e->getComponent<AccelerationComponent>();
      downPressed = false;
      if(leftPressed)
         a.direction = 180.0f; 
      else if(rightPressed)
         a.direction = 0.0f;
      else
      {
         a.acceleration = 0.0f;
         e->getComponent<FrictionComponent>().friction = m_friction;
      }
   }
}

void CharacterController::onRightPress()
{
   if(auto e = m_entity.lock())
   {
      auto &a = e->getComponent<AccelerationComponent>();
      e->getComponent<FrictionComponent>().friction = m_friction / 2.0f;

      a.acceleration = m_accel;
      a.direction = 0.0f;
      rightPressed = true;
      leftPressed = false;
      
      if(upPressed)
         a.direction = 45.0f; 
      else if(downPressed)
         a.direction = 315.0f;  
   }
}

void CharacterController::onRightRelease()
{   
   if(auto e = m_entity.lock())
   if(rightPressed)
   {
      auto &a = e->getComponent<AccelerationComponent>();

      rightPressed = false;
      if(upPressed)
         a.direction = 90.0f; 
      else if(downPressed)
         a.direction = 270.0f;
      else
      {
         a.acceleration = 0.0f;
         e->getComponent<FrictionComponent>().friction = m_friction;
      }
   }
}


