#pragma once

#include "IViewport.h"
#include "Camera.h"
#include "ObjectHash.h"
#include <unordered_map>

class Viewport : public IViewport
{
   Rectf m_bounds;
   std::shared_ptr<ICamera> m_camera;

   ViewportList m_children;

   std::unordered_map<Keystroke, MouseEventList, ObjectHash<Keystroke>> m_mouseCallbacks;
   std::weak_ptr<IViewport> m_parent;

public:
   Viewport(Rectf bounds, std::shared_ptr<ICamera> camera);
   std::weak_ptr<IViewport> getParent();
   std::shared_ptr<ICamera> getCamera();
   Rectf getBounds();
   Rectf getWindowBounds();

   void update();

   ViewportList &getChildren();

   bool hasMouseCallback(Keystroke k);
   void registerMouseCallback(Keystroke k, MouseEvent *e);
   void runMouseCallback(Keystroke k, Float2 pos);
};