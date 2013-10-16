#pragma once

#include "Entity.h"
#include <memory>
#include <vector>

#include "KeyHandler.h"

class CharacterController
{
   std::vector<KeyEvent> m_events;

   bool m_running;
   bool upPressed, downPressed, leftPressed, rightPressed;

   float m_accel, m_runAccel, m_maxVelocity, m_friction;

   void registerKeyEvent(Keystroke k, KeyEvent e);

   void onUpPress();
   void onUpRelease();
   void onLeftPress();
   void onLeftRelease();
   void onDownPress();
   void onDownRelease();
   void onRightPress();
   void onRightRelease();   

public:
   CharacterController();
};