#include "MouseHandler.h"

#include "IOCContainer.h"
#include "GLWindow.h"

bool MouseHandler::_runCallback(Keystroke key, IViewport &vp, Float2 mPos)
{
   //first check children starting with last first
   auto &vpChildren = vp.getChildren();
   
   for(auto &child : reversed_view(vpChildren))
   {
      if(!child.getChildren().empty() && _runCallback(key, child, mPos))
         return true;

      auto wb = child.getWindowBounds();
      if(child.hasMouseCallback(key) && wb.contains(mPos))
      {
         child.runMouseCallback(key, mPos - Float2(wb.left, wb.top));
         return true;
      }      
   }

   auto wb = vp.getWindowBounds();
   if(vp.hasMouseCallback(key) && wb.contains(mPos))
   {
      vp.runMouseCallback(key, mPos - Float2(wb.left, wb.top));
      return true;
   } 

   return false;
}


void MouseHandler::runEvent(Keystroke key)
{
   auto &win = IOC.resolve<GLWindow>();
   Float2 mpos = win.getMousePosition();

   for(auto & vp : win.getViewports())
      if(_runCallback(key, *vp, mpos))
         break;
}

Float2 MouseHandler::mousePos()
{
   return IOC.resolve<GLWindow>().getMousePosition();
}