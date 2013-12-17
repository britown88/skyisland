#include "Viewport.h"

#include "Application.h"

Viewport::Viewport(Float2 position, Float2 size, Float2 center, std::shared_ptr<ICamera> camera):
   m_pos(position), m_size(size), m_center(center), m_camera(camera)
{
   for(int i = 0; i < (int)Pass::COUNT; ++i)
      m_frameBuffers[i] = std::unique_ptr<FBO>(new FBO(getBounds()));
}
std::weak_ptr<IViewport> Viewport::getParent(){return m_parent;}
std::shared_ptr<ICamera> Viewport::getCamera(){return m_camera;}

Rectf Viewport::getBounds()
{
   auto &winSize = IOC.resolve<Application>()->windowSize();
   Rectf bounds = getWindowBounds();
   return Rectf(
      bounds.left,
      winSize.y - bounds.bottom,
      bounds.width(),
      bounds.height());
}

void Viewport::setParent(std::weak_ptr<IViewport> parent)
{
   m_parent = parent;
}

Rectf Viewport::getWindowBounds()
{
   Rectf newBounds;
   newBounds.left = m_pos.x - m_size.x * m_center.x;
   newBounds.top = m_pos.y - m_size.y * m_center.y;
   newBounds.right = newBounds.left + m_size.x;
   newBounds.bottom = newBounds.top + m_size.y;

   return newBounds;
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