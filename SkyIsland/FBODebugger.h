#pragma once

#include "ICamera.h"
#include "KeyHandler.h"

class FBODebugger
{
   ICamera::Pass m_pass;
   std::vector<KeyEvent> m_events;
public:
   static const unsigned int ID = 2341710366;

   FBODebugger();
   ICamera::Pass getPass();
   void registerKeyEvent(Keystroke k, KeyEvent e);
   bool renderFBOs;
};
