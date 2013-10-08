#pragma once

#include "IDrawObject.h"

#include <vector>
#include "Vertex.h"
#include "Transform.h"

class DrawTriangle : public IDrawObject
{
   std::vector<Vertex>  m_vertices;
   std::vector<int> m_faces;

   Transform m_transform;

public:
   DrawTriangle(std::vector<Vertex> vertices, std::vector<int> faces, Transform transform=Transform());

   void draw();

};