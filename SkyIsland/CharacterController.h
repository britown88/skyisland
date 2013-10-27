#pragma once

#include "Vector.h"
#include "Entity.h"
#include <memory>
#include <stack>
#include "StringTable.h"
#include "GameComponents.h"

class CharacterState
{
public:
   virtual ~CharacterState(){}

   virtual void onEnter(){}
   virtual void onExit(){}

   virtual void move(Float2 vector){}
   virtual void stop(){}
   virtual void updateAnimation(){}
   virtual void attack(){}
   virtual void damage(const AttackComponent &ac){}
   virtual void updateOnScreen(){}
   virtual void updateOffScreen(){}
};

typedef std::unique_ptr<CharacterState> StatePtr;

class CharacterController
{
   std::weak_ptr<Entity> m_entity;
   float m_accel, m_runAccel, m_maxVelocity, m_friction, m_minAnimSpeed, m_maxAnimSpeed;
   Float2 m_facing;

   std::stack<StatePtr> m_states;

   void setState(StatePtr state);
   void replaceState(StatePtr state);//replaces current state on stack
   void revertState();

   StatePtr buildMoveState();
   StatePtr buildAttackState();
   StatePtr buildDamagedState(const AttackComponent &ac);

   bool m_taskDone;

   InternString f_standDown, f_standUp, f_standRight, 
      f_standLeft, f_runUp, f_runDown, f_runLeft, f_runRight,
      f_attackLeft, f_attackRight, f_attackUp, f_attackDown;
public:   

   CharacterController(std::weak_ptr<Entity> entity);
   void move(Float2 vector);
   void stop();
   void updateAnimation();
   void attack();
   void damage(const AttackComponent &ac);
   void updateOnScreen();
   void updateOffScreen();

   bool currentTaskDone();

   friend CharacterState;
};