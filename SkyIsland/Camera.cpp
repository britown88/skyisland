#include "Camera.h"

Camera::Camera(Rectf bounds, const IScene& scene):m_bounds(bounds), m_scene(scene){}

const IScene& Camera::getScene() const{return m_scene;}

const Rectf Camera::getBounds() const{return m_bounds;}