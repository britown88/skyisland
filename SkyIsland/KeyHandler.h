#pragma once

#include "Keystroke.h"
#include "IKeyEvent.h"
#include <map>
#include <memory>
#include <functional>

class KeyHandler
{
   std::map<size_t, std::function<void()>> m_events;
public:
   void registerEvent(Keystroke key, std::function<void()> e);
   void unregisterEvent(Keystroke key);

   void runEvent(Keystroke key);

};