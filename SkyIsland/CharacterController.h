#pragma once

#include "Entity.h"
#include <memory>

class CharacterController
{
   std::weak_ptr<Entity> m_entity;

   bool m_running;
   bool upPressed, downPressed, leftPressed, rightPressed;

   float m_accel, m_runAccel, m_maxVelocity, m_friction;

   void onUpPress();
   void onUpRelease();
   void onLeftPress();
   void onLeftRelease();
   void onDownPress();
   void onDownRelease();
   void onRightPress();
   void onRightRelease();   

public:
   CharacterController(std::weak_ptr<Entity> entity);
   ~CharacterController();
};