#include "Viewport.h"

Viewport::Viewport(Rectf bounds, std::shared_ptr<ICamera> camera):m_bounds(bounds), m_camera(camera){}

std::shared_ptr<ICamera> Viewport::getCamera(){return m_camera;}
Rectf Viewport::getBounds(){return m_bounds;}

ViewportList &Viewport::getChildren(){return m_children;}