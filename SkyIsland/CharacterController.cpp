#include <GLFW/glfw3.h>

#include "CharacterController.h"

#include "IOCContainer.h"
#include "Application.h"

#include "PhysicsComponents.h"
#include "GraphicComponents.h"


CharacterController::CharacterController()
{
   m_accel = 1.0f;
   m_runAccel = 1.0f;
   m_maxVelocity = 10.0f;
   m_friction = 1.0f;

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
   if(auto e = IOC.resolve<Application>().getTag(EntityTag::PlayerControlled))
   {
      auto &a = e->getComponent<AccelerationComponent>();
      e->getComponent<FrictionComponent>().friction = m_friction / 2.0f;

      e->getComponent<SpriteComponent>().face = "run_up";

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
   if(auto e = IOC.resolve<Application>().getTag(EntityTag::PlayerControlled))
   if(upPressed)
   {
      auto &a = e->getComponent<AccelerationComponent>();
      upPressed = false;
      if(leftPressed)
      {
         a.direction = 180.0f; 
         e->getComponent<SpriteComponent>().face = "run_left";
      }         
      else if(rightPressed)
      {
         a.direction = 0.0f;
         e->getComponent<SpriteComponent>().face = "run_right";
      }         
      else
      {
         a.acceleration = 0.0f;
         e->getComponent<FrictionComponent>().friction = m_friction;

         e->getComponent<SpriteComponent>().face = "stand_up";
      }
         
   }
}

void CharacterController::onLeftPress()
{
   if(auto e = IOC.resolve<Application>().getTag(EntityTag::PlayerControlled))
   {
      auto &a = e->getComponent<AccelerationComponent>();
      e->getComponent<FrictionComponent>().friction = m_friction / 2.0f;

      a.acceleration = m_accel;
      a.direction = 180.0f;
      leftPressed = true;
      rightPressed = false;

      e->getComponent<SpriteComponent>().face = "run_left";
      
      if(upPressed)
         a.direction = 135.0f; 
      else if(downPressed)
         a.direction = 225.0f;   
   }

}

void CharacterController::onLeftRelease()
{
   if(auto e = IOC.resolve<Application>().getTag(EntityTag::PlayerControlled))
   if(leftPressed)
   {
      auto &a = e->getComponent<AccelerationComponent>();
      leftPressed = false;
      if(upPressed)
      {
         a.direction = 90.0f; 
         e->getComponent<SpriteComponent>().face = "run_up";
      }         
      else if(downPressed)
      {
         a.direction = 270.0f;
         e->getComponent<SpriteComponent>().face = "run_down";
      }         
      else
      {
         a.acceleration = 0.0f;
         e->getComponent<FrictionComponent>().friction = m_friction;

         e->getComponent<SpriteComponent>().face = "stand_left";
      }
   }
}

void CharacterController::onDownPress()
{
   if(auto e = IOC.resolve<Application>().getTag(EntityTag::PlayerControlled))
   {
      auto &a = e->getComponent<AccelerationComponent>();
      e->getComponent<FrictionComponent>().friction = m_friction / 2.0f;

      e->getComponent<SpriteComponent>().face = "run_down";


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
   if(auto e = IOC.resolve<Application>().getTag(EntityTag::PlayerControlled))
   if(downPressed)
   {
      auto &a = e->getComponent<AccelerationComponent>();
      downPressed = false;
      if(leftPressed)
      {
         a.direction = 180.0f; 
         e->getComponent<SpriteComponent>().face = "run_left";
      }         
      else if(rightPressed)
      {
         a.direction = 0.0f;
         e->getComponent<SpriteComponent>().face = "run_right";
      }         
      else
      {
         a.acceleration = 0.0f;
         e->getComponent<FrictionComponent>().friction = m_friction;

         e->getComponent<SpriteComponent>().face = "stand_down";
      }
   }
}

void CharacterController::onRightPress()
{
   if(auto e = IOC.resolve<Application>().getTag(EntityTag::PlayerControlled))
   {
      auto &a = e->getComponent<AccelerationComponent>();
      e->getComponent<FrictionComponent>().friction = m_friction / 2.0f;

      e->getComponent<SpriteComponent>().face = "run_right";

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
   if(auto e = IOC.resolve<Application>().getTag(EntityTag::PlayerControlled))
   if(rightPressed)
   {
      auto &a = e->getComponent<AccelerationComponent>();

      rightPressed = false;
      if(upPressed)
      {
         a.direction = 90.0f; 
         e->getComponent<SpriteComponent>().face = "run_up";
      }         
      else if(downPressed)
      {
         a.direction = 270.0f;
         e->getComponent<SpriteComponent>().face = "run_down";
      }         
      else
      {
         a.acceleration = 0.0f;
         e->getComponent<FrictionComponent>().friction = m_friction;
         e->getComponent<SpriteComponent>().face = "stand_right";
      }
   }
}


