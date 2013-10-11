#include "MouseHandler.h"

#include "IOCContainer.h"
#include "GLWindow.h"

void MouseHandler::registerEvent(Keystroke key, MouseEvent *e)
{
   m_events[key.hash()].push_back(e);
}

void MouseHandler::runEvent(Keystroke key)
{
   Float2 mp = mousePos();
   if(m_events.find(key.hash()) != m_events.end())
      for(auto &e : m_events[key.hash()])
         if(e.contains(mp))
            e.fn(mp);
}

Float2 MouseHandler::mousePos()
{
   return IOC.resolve<GLWindow>().getMousePosition();
}