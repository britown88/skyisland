#pragma once

#include "IViewport.h"
#include <memory>
#include <vector>
#include "Rect.h"

struct UIScene
{
   std::shared_ptr<IScene> scene;
   std::shared_ptr<IViewport> viewport;
   std::shared_ptr<ICamera> camera;
};

class UISystem : public IViewport
{
   typedef std::vector<std::shared_ptr<UIScene> > SceneList;

   Rectf m_bounds;
   UIScene m_masterScene;
   SceneList m_scenes;
   ViewportList m_children;

   void _initMasterScene();

public:
   UISystem(Rectf bounds);

   std::shared_ptr<ICamera> getCamera();
   Rectf getBounds();
   ViewportList &getChildren();
};