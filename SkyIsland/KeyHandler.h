#pragma once

#include "Keystroke.h"
#include "IKeyEvent.h"
#include <map>
#include <memory>

class KeyHandler
{
   std::map<size_t, std::unique_ptr<IKeyEvent> > m_events;
public:
   void registerEvent(Keystroke key, std::unique_ptr<IKeyEvent> e);
   void unregisterEvent(Keystroke key);

   void runEvent(Keystroke key);

};