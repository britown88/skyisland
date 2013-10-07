#pragma once

#include "IRenderable.h"
#include <vector>
#include "Vertex.h"

class SkyTriangle : public IRenderable
{
public:
   void render(Float2 drawPos, const IRenderer &renderer) const
   {
      std::vector<Vertex> vertices;
      std::vector<int> indices;

      vertices.push_back(Vertex(Float2(-0.6f, -0.4f), 1.0f, 0.0f, 0.0f));
      vertices.push_back(Vertex(Float2(0.6f, -0.4f), 0.f, 1.f, 0.f));
      vertices.push_back(Vertex(Float2(0.f, 0.6f), 0.f, 0.f, 1.f));

      indices.push_back(0);
      indices.push_back(1);
      indices.push_back(2);

      renderer.drawTriangles(vertices, indices);
   }
};