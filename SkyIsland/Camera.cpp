#include "Camera.h"

Camera::Camera(Rectf bounds, std::shared_ptr<IScene> scene):m_bounds(bounds), m_scene(scene){}

IScene& Camera::getScene() {return *m_scene;}

Rectf Camera::getBounds(){return m_bounds;}

void Camera::setBounds(Rectf bounds){m_bounds = bounds;}