#pragma once

#include "IntrusiveLinkedList.h"
#include "Event.h"
#include "Vector.h"
#include "Keystroke.h"
#include <memory>

class IViewport;

typedef Event<void(Float2)> MouseEvent;

typedef IntrusiveList<MouseEvent, &MouseEvent::hook> MouseEventList;

class MouseHandler
{
   bool _runCallback(Keystroke key, IViewport &vp, Float2 mPos);

public:
   static const int ID = 3325994233;
   void runEvent(Keystroke key);
   Float2 mousePos();
};