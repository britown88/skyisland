#include "Renderer.h"
#include <algorithm>
#include "IOCContainer.h"
#include "Application.h"

Renderer::Renderer():m_drawQueue(SceneList(new std::vector<DScenePtr>()))
{   
}

void Renderer::drawTriangles(const std::vector<Vertex> & vertices, const std::vector<int> &faces, Transform transform) const
{
   m_drawQueue->back()->addObject(std::unique_ptr<IDrawObject>(new DrawTriangle(vertices, faces, transform)));
}

Renderer::SceneList Renderer::drawQueue()
{
   auto ret = std::move(m_drawQueue);

   m_drawQueue.reset(new std::vector<DScenePtr>());
   return ret;
}


bool Renderer::newScene(IViewport &vp, ICamera &cam)
{
   auto &winSize = IOC.resolve<Application>().windowSize();

   if(auto &parent = vp.getParent().lock())
   {
      auto db_ = parent->getDrawnBounds();
      auto vb_ = vp.getBounds();

      //convert to sensible coordinate system
      Rectf db = Rectf(db_.left, winSize.y - db_.top - db_.bottom, db_.left + db_.right, winSize.y - db_.top);
      Rectf vb = Rectf(vb_.left, winSize.y - vb_.top - vb_.bottom, vb_.left + vb_.right, winSize.y - vb_.top);

      //panel intersects or is within parent
      if(db.contains(vb))
      {
         Rectf i = db.intersection(vb);
         Rectf correctedBounds = Rectf(i.left, winSize.y - i.bottom, i.width(), i.height());
         vp.setDrawnBounds(correctedBounds);

         if(i.width() == vb.width() && i.height() == vb.height())
         {
            //vp lies entirely within parent bounds, drw normally            
            m_drawQueue->push_back(Renderer::DScenePtr(new DrawScene(vp, cam)));
            return true;
         }
         else
         {
            //vp intersects with parents, set scissor rect
            m_drawQueue->push_back(Renderer::DScenePtr(new DrawScene(vp, cam, correctedBounds)));
            return true;
         }

      }
      else
      //vp is entirely outside parent
         return false;
   }

   //vp has no parent, so draw
   vp.setDrawnBounds(vp.getBounds());
   m_drawQueue->push_back(Renderer::DScenePtr(new DrawScene(vp, cam)));

   return true;
}