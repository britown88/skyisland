#include "KeyHandler.h"

void KeyHandler::registerEvent(Keystroke key, KeyEvent *e)
{
   m_events[key.hash()].push_back(e);
}

void KeyHandler::runEvent(Keystroke key)
{
   if(m_events.find(key.hash()) != m_events.end())
      for(auto &e : m_events[key.hash()])
         e.fn();
}