#pragma once

#include "IntrusiveLinkedList.h"
#include "Event.h"
#include "Rect.h"
#include "Vector.h"
#include "Keystroke.h"
#include <functional>
#include <map>


class MouseEvent
{
   std::shared_ptr<Rectf> m_bounds;
public:
   std::function<void(Float2)> fn;
   IntrusiveListHook hook;

   MouseEvent(){}
   MouseEvent(std::function<void(Float2)> fn, std::shared_ptr<Rectf> bounds):fn(std::move(fn)), m_bounds(bounds) {}
   MouseEvent(MouseEvent &&ref):fn(std::move(ref.fn)), hook(std::move(ref.hook)), m_bounds(std::move(ref.m_bounds)){}

   bool contains(Float2 pos){return m_bounds->contains(pos);}
};

typedef IntrusiveList<MouseEvent, &MouseEvent::hook> MouseEventList;

class MouseHandler
{
public:
   std::map<size_t, MouseEventList> m_events;
public:
   void registerEvent(Keystroke key, MouseEvent *e);

   void runEvent(Keystroke key);
   Float2 mousePos();
};