#pragma once

#include "IntrusiveLinkedList.h"
#include <memory>

template <typename FnType>
class Event 
{   
public:
   std::function<FnType> fn;
   IntrusiveListHook hook;
   Event(){}
   Event(std::function<FnType> fn):fn(fn) {}
   Event(Event &&ref):fn(std::move(ref.fn)), hook(std::move(ref.hook)){}
   
};