#pragma once

#include "Keystroke.h"
#include "IKeyEvent.h"
#include <unordered_map>
#include <memory>
#include <functional>
#include "Event.h"

#include "ObjectHash.h"

typedef Event<void()> KeyEvent;
typedef IntrusiveList<KeyEvent, &KeyEvent::hook> KeyEventList;

class KeyHandler
{
   std::unordered_map<Keystroke, KeyEventList, ObjectHash<Keystroke>> m_events;
public:
   static const int ID = 588605129;
   void registerEvent(Keystroke key, KeyEvent *e);

   void runEvent(Keystroke key);

};