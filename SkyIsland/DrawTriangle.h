#pragma once

#include "IDrawObject.h"

#include <vector>
#include "Vertex.h"

class DrawTriangle : public IDrawObject
{
   std::vector<Vertex>  m_vertices;
   std::vector<int> m_faces;

public:
   DrawTriangle(const std::vector<Vertex> & vertices, const std::vector<int> &faces);

   void draw();

};