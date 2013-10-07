#pragma once

#include <vector>
#include "Vertex.h"
#include "IDrawObject.h"

class IRenderer
{
public:
   typedef std::vector<std::shared_ptr<IDrawObject> > DrawQueue;

   virtual ~IRenderer(){}

   virtual void drawTriangles(const std::vector<Vertex> & vertices, const std::vector<int> &faces) const=0;

   //clears the drawobject queue
   virtual void clearQueue()=0;
   virtual std::unique_ptr<DrawQueue> getDrawQueue()=0;

};