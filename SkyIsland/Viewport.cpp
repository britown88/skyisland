#include "Viewport.h"

#include "Application.h"

Viewport::Viewport(Rectf bounds, std::shared_ptr<ICamera> camera):m_bounds(bounds), m_camera(camera){}

std::shared_ptr<ICamera> Viewport::getCamera(){return m_camera;}
Rectf Viewport::getBounds(){return m_bounds;}

Rectf Viewport::getWindowBounds()
{
   auto &winSize = IOC.resolve<Application>().windowSize();
   return Rectf(
      m_bounds.left,
      winSize.y - m_bounds.top - m_bounds.bottom,
      m_bounds.left + m_bounds.right,
      winSize.y - m_bounds.top);
}

void Viewport::update() {}

ViewportList &Viewport::getChildren(){return m_children;}

bool Viewport::hasMouseCallback(Keystroke k)
{
   return m_mouseCallbacks.find(k) != m_mouseCallbacks.end();
}

void Viewport::registerMouseCallback(Keystroke k, MouseEvent *e)
{
   m_mouseCallbacks[k].push_back(e);
}

void Viewport::runMouseCallback(Keystroke k, Float2 pos)
{
   if(hasMouseCallback(k))
      for(auto &e : m_mouseCallbacks[k])
         e.fn(pos);
}