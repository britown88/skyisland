#include "Camera.h"

Camera::Camera(Rectf bounds, std::shared_ptr<IScene> scene):m_bounds(bounds), m_scene(scene)
{
}

std::shared_ptr<IScene> Camera::getScene() {return m_scene;}

Rectf Camera::getBounds(){return m_bounds;}

void Camera::setBounds(Rectf bounds){m_bounds = bounds;}

std::unordered_map<ICamera::Pass, std::shared_ptr<FBO>> &Camera::getFBOs(){return m_frameBuffers;}
void Camera::addFBOPass(ICamera::Pass pass)
{
   m_frameBuffers.insert(std::make_pair(pass, std::make_shared<FBO>(m_bounds)));
}