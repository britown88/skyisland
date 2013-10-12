#include "Viewport.h"

#include "Application.h"

Viewport::Viewport(Rectf bounds, std::shared_ptr<ICamera> camera):m_bounds(bounds), m_camera(camera){}
std::weak_ptr<IViewport> Viewport::getParent(){return m_parent;}
std::shared_ptr<ICamera> Viewport::getCamera(){return m_camera;}
Rectf Viewport::getBounds(){return m_bounds;}

void Viewport::setParent(std::weak_ptr<IViewport> parent)
{
   m_parent = parent;
}

Rectf Viewport::getWindowBounds()
{
   auto &winSize = IOC.resolve<Application>().windowSize();
   return Rectf(
      m_bounds.left,
      winSize.y - m_bounds.top - m_bounds.bottom,
      m_bounds.left + m_bounds.right,
      winSize.y - m_bounds.top);
}
Rectf Viewport::getDrawnBounds(){return m_drawnBounds;}
void Viewport::setDrawnBounds(Rectf bounds){m_drawnBounds = bounds;}

void Viewport::update() {}

void Viewport::addChild(std::shared_ptr<IViewport> vp)
{
   m_children.push_back(vp.get());
   vp->setParent(getptr());
}

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