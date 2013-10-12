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
}