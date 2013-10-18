#pragma once

#include "Entity.h"
#include <memory>
#include <vector>

#include "KeyHandler.h"

class CharacterInputHandler
{
   std::vector<KeyEvent> m_events;

   bool m_running;
   bool upPressed, downPressed, leftPressed, rightPressed;

   float m_accel, m_runAccel, m_maxVelocity, m_friction;

   void registerKeyEvent(Keystroke k, KeyEvent e);

   void sendControllerMovement();

public:
   CharacterInputHandler();
};