#include "Viewport.h"

Viewport::Viewport(Rectf bounds, const Camera &camera):m_bounds(bounds), m_camera(camera){}

const ICamera& Viewport::getCamera(){return m_camera;}
Rectf Viewport::getBounds(){return m_bounds;}