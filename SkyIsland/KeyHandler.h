#pragma once

#include "Keystroke.h"
#include "IKeyEvent.h"
#include <map>
#include <memory>
#include <functional>
#include "Event.h"

typedef Event<void()> KeyEvent;
typedef IntrusiveList<KeyEvent, &KeyEvent::hook> KeyEventList;

class KeyHandler
{
   std::map<size_t, KeyEventList> m_events;
public:
   void registerEvent(Keystroke key, KeyEvent *e);

   void runEvent(Keystroke key);

};