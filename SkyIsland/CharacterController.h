#pragma once

#include "Vector.h"
#include "Entity.h"
#include <memory>

class CharacterController
{
   std::weak_ptr<Entity> m_entity;
   float m_accel, m_runAccel, m_maxVelocity, m_friction, m_minAnimSpeed, m_maxAnimSpeed;
   Float2 m_facing;
public:
   CharacterController(std::weak_ptr<Entity> entity);
   void move(Float2 vector);
   void stop();
   void updateAnimation();
};