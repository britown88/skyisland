#include "KeyHandler.h"

void KeyHandler::registerEvent(Keystroke key, std::unique_ptr<IKeyEvent> e)
{
   m_events[key.hash()] = std::move(e);
}

void KeyHandler::unregisterEvent(Keystroke key)
{
   if(m_events.find(key.hash()) != m_events.end())
      m_events.erase(key.hash());
}

void KeyHandler::runEvent(Keystroke key)
{
   if(m_events.find(key.hash()) != m_events.end())
      m_events[key.hash()]->run();
}