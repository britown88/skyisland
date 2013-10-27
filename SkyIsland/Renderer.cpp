#include "Renderer.h"
#include <algorithm>
#include "IOCContainer.h"
#include "Application.h"
#include "DrawTexture.h"
#include "DrawText.h"

Renderer::Renderer():m_drawQueue(SceneList(new std::vector<DScenePtr>()))
{   
}

void Renderer::drawTriangles(std::shared_ptr<VertexList> vertices, std::shared_ptr<std::vector<int>> faces, Transform transform) const
{
   m_drawQueue->back()->addObject(std::unique_ptr<IDrawObject>(new DrawTriangle(std::move(vertices), std::move(faces), transform)));
}

void Renderer::drawTexture(InternString texture, std::shared_ptr<VertexList> vertices, std::shared_ptr<std::vector<int>> faces, Transform transform) const
{
   m_drawQueue->back()->addObject(std::unique_ptr<IDrawObject>(new DrawTexture(texture, std::move(vertices), std::move(faces), transform)));
}

void Renderer::drawText(std::shared_ptr<TextString> text, Transform transform) const
{
   m_drawQueue->back()->addObject(std::unique_ptr<IDrawObject>(new DrawText(text, transform)));
}

Renderer::SceneList Renderer::drawQueue()
{
   auto ret = std::move(m_drawQueue);

   m_drawQueue.reset(new std::vector<DScenePtr>());
   return ret;
}


bool Renderer::newScene(IViewport &vp, ICamera &cam)
{
   auto &winSize = IOC.resolve<Application>()->windowSize();

   if(auto &parent = vp.getParent().lock())
   {
      auto db = parent->getDrawnBounds();
      auto vb = vp.getWindowBounds();

      //panel intersects or is within parent
      if(db.contains(vb))
      {
         Rectf i = db.intersection(vb);
         Rectf correctedBounds = Rectf(i.left, winSize.y - i.bottom, i.width(), i.height());
         vp.setDrawnBounds(i);

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
   vp.setDrawnBounds(vp.getWindowBounds());
   m_drawQueue->push_back(Renderer::DScenePtr(new DrawScene(vp, cam)));

   return true;
}