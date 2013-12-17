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

   std::unique_ptr<FBO> m_frameBuffers[Pass::COUNT];

public:
   Viewport(Float2 position, Float2 size, Float2 center, std::shared_ptr<ICamera> camera);
   std::weak_ptr<IViewport> getParent();
   void setParent(std::weak_ptr<IViewport> parent);
   std::shared_ptr<ICamera> getCamera();
   Rectf getBounds();
   Rectf getWindowBounds();
   Rectf getDrawnBounds();
   void setDrawnBounds(Rectf bounds);

   void update();

   ViewportList &getChildren();
   void addChild(std::shared_ptr<IViewport> vp);

   bool hasMouseCallback(Keystroke k);
   void registerMouseCallback(Keystroke k, MouseEvent *e);
   void runMouseCallback(Keystroke k, Float2 pos);
};