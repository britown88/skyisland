#pragma once

#include "IViewport.h"
#include "Camera.h"
#include "ObjectHash.h"
#include "FBO.h"
#include <unordered_map>

class Viewport : public IViewport
{
   Float2 m_size, m_pos, m_center;
   Rectf m_drawnBounds;
   std::shared_ptr<ICamera> m_camera;

   ViewportList m_children;

   std::unordered_map<Keystroke, MouseEventList, ObjectHash<Keystroke>> m_mouseCallbacks;
   std::weak_ptr<IViewport> m_parent;
   void setParent(std::weak_ptr<IViewport> parent);


public:
   Viewport(Float2 position, Float2 size, Float2 center, std::shared_ptr<ICamera> camera);
   std::weak_ptr<IViewport> getParent();

   std::shared_ptr<ICamera> getCamera();
   Rectf getBounds();
   Rectf getWindowBounds();
   Rectf getDrawnBounds();
   void setDrawnBounds(Rectf bounds);
   std::vector<std::shared_ptr<FBO>> &getFBOs();

   void update();

   ViewportList &getChildren();

   bool hasMouseCallback(Keystroke k);
   void registerMouseCallback(Keystroke k, MouseEvent *e);
   void runMouseCallback(Keystroke k, Float2 pos);
};

