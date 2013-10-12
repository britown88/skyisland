#pragma once

#include "ICamera.h"
#include "Rect.h"

#include "IntrusiveLinkedList.h"
#include "Keystroke.h"
#include "MouseHandler.h"


class ViewportList;

class IViewport : std::enable_shared_from_this<IViewport>
{   
public:
   IntrusiveListHook hook;
   std::shared_ptr<IViewport> getptr() {return shared_from_this();}
   virtual ~IViewport(){}   

   virtual std::weak_ptr<IViewport> getParent()=0;
   virtual void setParent(std::weak_ptr<IViewport> parent)=0;

   virtual std::shared_ptr<ICamera> getCamera()=0;
   virtual Rectf getBounds()=0;
   virtual Rectf getWindowBounds()=0;
   virtual Rectf getDrawnBounds()=0;
   virtual void setDrawnBounds(Rectf bounds)=0;

   virtual void update()=0;

   virtual ViewportList &getChildren()=0;
   virtual void addChild(std::shared_ptr<IViewport> vp)=0;

   virtual bool hasMouseCallback(Keystroke k)=0;
   virtual void registerMouseCallback(Keystroke k, MouseEvent *e)=0;
   virtual void runMouseCallback(Keystroke k, Float2 pos)=0;

};

typedef IntrusiveList<IViewport, &IViewport::hook> ill_ViewportList;

class ViewportList
{  
public:
   typedef ill_ViewportList::iterator iterator;
   typedef ill_ViewportList::reverse_iterator reverse_iterator;

   ill_ViewportList list;
   iterator begin() { return list.begin();}
   iterator end() {return list.end();}
   reverse_iterator rbegin(){ return list.rbegin();}
   reverse_iterator rend(){ return list.rend();}
   bool empty(){return list.empty();}
   void push_back(IViewport *vp){list.push_back(vp);}
   
};



