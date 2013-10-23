#include <GLFW/glfw3.h>
#include "KeyHandler.h"

void KeyHandler::registerEvent(Keystroke key, KeyEvent *e)
{
   m_events[key].push_back(e);
}

void KeyHandler::runEvent(Keystroke key)
{
   if(m_events.find(key) != m_events.end())
      for(auto &e : m_events[key])
         e.fn();

   Keystroke stepKey = Keystroke(key.key, INPUT_STEP, key.mods);
   if(m_events.find(stepKey) != m_events.end())
   {
      if(key.action == GLFW_PRESS)
         m_stepEvents[stepKey] = &m_events[stepKey];

      if(key.action == GLFW_RELEASE)
         m_stepEvents.erase(stepKey);
   }
}

void KeyHandler::updateKeySteps()
{
   for(auto &eList : m_stepEvents)
      for(auto &e : *eList.second)
         e.fn();
}