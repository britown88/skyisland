#pragma once

#include "ICamera.h"
#include "Rect.h"

#include "IntrusiveLinkedList.h"

class ViewportList;

class IViewport
{   
public:
   IntrusiveListHook hook;
   virtual ~IViewport(){}   

   virtual std::shared_ptr<ICamera> getCamera()=0;
   virtual Rectf getBounds()=0;

   virtual ViewportList &getChildren()=0;

};

typedef IntrusiveList<IViewport, &IViewport::hook> ill_ViewportList;

class ViewportList
{
  typedef ill_ViewportList::iterator iterator;
public:
   ill_ViewportList list;
   iterator begin() { return list.begin();}
   iterator end() {return list.end();}
};



