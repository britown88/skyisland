#include "UISystem.h"
#include "Camera.h"
#include "Scene.h"
#include "Viewport.h"

UISystem::UISystem(Rectf bounds):m_bounds(bounds){}

std::shared_ptr<ICamera> UISystem::getCamera(){return m_masterScene.camera;}
Rectf UISystem::getBounds(){return m_bounds;}
ViewportList &UISystem::getChildren(){return m_children;}

void UISystem::_initMasterScene()
{
   //m_masterScene.scene = std::make_shared<IScene>(new Scene(Float2(m_bounds.width(), m_bounds.height())));
   //m_masterScene.camera = std::make_shared<ICamera>(new Camera(Rectf(0, 0, m_bounds.width(), m_bounds.height()), m_masterScene.scene));
}