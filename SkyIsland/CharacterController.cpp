#include <GLFW/glfw3.h>
#include "CharacterController.h"

#include "IOCContainer.h"
#include "KeyHandler.h"
#include "PhysicsComponents.h"


CharacterController::CharacterController(Entity &entity):
   m_entity(entity)
{
   m_accel = 0.05f;
   m_runAccel = 1.0f;
   m_maxVelocity = 10.0f;
   m_friction = 0.25f;

   upPressed = false;
   downPressed = false;
   leftPressed = false;
   rightPressed = false;

   IOC.resolve<KeyHandler>().registerEvent(Keystroke(GLFW_KEY_RIGHT, GLFW_PRESS, 0), [&](){this->onRightPress();});
   IOC.resolve<KeyHandler>().registerEvent(Keystroke(GLFW_KEY_RIGHT, GLFW_RELEASE, 0), [&](){this->onRightRelease();});   
   IOC.resolve<KeyHandler>().registerEvent(Keystroke(GLFW_KEY_LEFT, GLFW_PRESS, 0), [&](){this->onLeftPress();});
   IOC.resolve<KeyHandler>().registerEvent(Keystroke(GLFW_KEY_LEFT, GLFW_RELEASE, 0), [&](){this->onLeftRelease();});
   IOC.resolve<KeyHandler>().registerEvent(Keystroke(GLFW_KEY_UP, GLFW_PRESS, 0), [&](){this->onUpPress();});
   IOC.resolve<KeyHandler>().registerEvent(Keystroke(GLFW_KEY_UP, GLFW_RELEASE, 0), [&](){this->onUpRelease();});
   IOC.resolve<KeyHandler>().registerEvent(Keystroke(GLFW_KEY_DOWN, GLFW_PRESS, 0), [&](){this->onDownPress();});
   IOC.resolve<KeyHandler>().registerEvent(Keystroke(GLFW_KEY_DOWN, GLFW_RELEASE, 0), [&](){this->onDownRelease();});

}

CharacterController::~CharacterController()
{
   IOC.resolve<KeyHandler>().unregisterEvent(Keystroke(GLFW_KEY_RIGHT, GLFW_PRESS, 0));
   IOC.resolve<KeyHandler>().unregisterEvent(Keystroke(GLFW_KEY_RIGHT, GLFW_RELEASE, 0));   
   IOC.resolve<KeyHandler>().unregisterEvent(Keystroke(GLFW_KEY_LEFT, GLFW_PRESS, 0));
   IOC.resolve<KeyHandler>().unregisterEvent(Keystroke(GLFW_KEY_LEFT, GLFW_RELEASE, 0));
   IOC.resolve<KeyHandler>().unregisterEvent(Keystroke(GLFW_KEY_UP, GLFW_PRESS, 0));
   IOC.resolve<KeyHandler>().unregisterEvent(Keystroke(GLFW_KEY_UP, GLFW_RELEASE, 0));
   IOC.resolve<KeyHandler>().unregisterEvent(Keystroke(GLFW_KEY_DOWN, GLFW_PRESS, 0));
   IOC.resolve<KeyHandler>().unregisterEvent(Keystroke(GLFW_KEY_DOWN, GLFW_RELEASE, 0));

}

void CharacterController::onUpPress()
{
   auto &a = m_entity.getComponent<AccelerationComponent>();

   a.acceleration = m_accel;
   a.direction = 90.0f;
   upPressed = true;
   downPressed = false;
      
   if(leftPressed)
      a.direction = 135.0f; 
   else if(rightPressed)
      a.direction = 45.0f;   
}

void CharacterController::onUpRelease()
{
   auto &a = m_entity.getComponent<AccelerationComponent>();
   if(upPressed)
   {
      upPressed = false;
      if(leftPressed)
         a.direction = 180.0f; 
      else if(rightPressed)
         a.direction = 0.0f;
      else
         a.acceleration = 0.0f;
   }
}

void CharacterController::onLeftPress()
{
   auto &a = m_entity.getComponent<AccelerationComponent>();

   a.acceleration = m_accel;
   a.direction = 180.0f;
   leftPressed = true;
   rightPressed = false;
      
   if(upPressed)
      a.direction = 135.0f; 
   else if(downPressed)
      a.direction = 225.0f;   
}

void CharacterController::onLeftRelease()
{
   auto &a = m_entity.getComponent<AccelerationComponent>();
   if(leftPressed)
   {
      leftPressed = false;
      if(upPressed)
         a.direction = 90.0f; 
      else if(downPressed)
         a.direction = 270.0f;
      else
         a.acceleration = 0.0f;
   }
}

void CharacterController::onDownPress()
{
   auto &a = m_entity.getComponent<AccelerationComponent>();

   a.acceleration = m_accel;
   a.direction = 270.0f;
   downPressed = true;
   upPressed = false;
      
   if(leftPressed)
      a.direction = 225.0f; 
   else if(rightPressed)
      a.direction = 315.0f;   
}

void CharacterController::onDownRelease()
{
   auto &a = m_entity.getComponent<AccelerationComponent>();
   if(downPressed)
   {
      downPressed = false;
      if(leftPressed)
         a.direction = 180.0f; 
      else if(rightPressed)
         a.direction = 0.0f;
      else
         a.acceleration = 0.0f;
   }
}

void CharacterController::onRightPress()
{
   auto &a = m_entity.getComponent<AccelerationComponent>();

   a.acceleration = m_accel;
   a.direction = 0.0f;
   rightPressed = true;
   leftPressed = false;
      
   if(upPressed)
      a.direction = 45.0f; 
   else if(downPressed)
      a.direction = 315.0f;   
}

void CharacterController::onRightRelease()
{
   auto &a = m_entity.getComponent<AccelerationComponent>();
   if(rightPressed)
   {
      rightPressed = false;
      if(upPressed)
         a.direction = 90.0f; 
      else if(downPressed)
         a.direction = 270.0f;
      else
         a.acceleration = 0.0f;
   }
}


