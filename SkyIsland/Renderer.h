#pragma once

#include "IRenderer.h"
#include "IDrawObject.h"
#include "DrawTriangle.h"

#include <vector>
#include <memory>

class Renderer : public IRenderer
{
   std::unique_ptr<DrawQueue> m_drawQueue;

public:
   Renderer()
   {
      m_drawQueue.reset(new DrawQueue());
   }

   void drawTriangles(const std::vector<Vertex> & vertices, const std::vector<int> &faces, Transform transform = Transform()) const
   {
      m_drawQueue->push_back(std::shared_ptr<IDrawObject>(new DrawTriangle(vertices, faces, transform)));
   }

   std::unique_ptr<DrawQueue> getDrawQueue()
   {
      return std::move(m_drawQueue);
   }

   //clears the drawobject queue
   void clearQueue()
   {
      m_drawQueue.reset(new DrawQueue());
   }
};