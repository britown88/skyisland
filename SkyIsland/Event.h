#pragma once

#include "IntrusiveLinkedList.h"
#include <memory>
#include <functional>

template <typename FnType>
class Event
{
public:
   std::function<FnType> fn;
   IntrusiveListHook hook;
   Event(){}
   Event(std::function<FnType> fn):fn(std::move(fn)) {}
   Event(Event &&ref):fn(std::move(ref.fn)), hook(std::move(ref.hook)){}
   Event &operator=(Event &&ref){fn = std::move(ref.fn); hook = std::move(ref.hook); return *this;}

};
