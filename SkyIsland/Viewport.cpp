#include "Viewport.h"

Viewport::Viewport(Rectf bounds, Camera &camera):m_bounds(bounds), m_camera(camera){}

ICamera& Viewport::getCamera(){return m_camera;}
Rectf Viewport::getBounds(){return m_bounds;}