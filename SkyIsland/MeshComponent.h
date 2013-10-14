#pragma once

#include "IComponent.h"
#include "IRenderable.h"
#include <memory>

class MeshComponent : public IComponent
{
   VertexList m_vertices;
   std::vector<int> m_faces;

public:
   MeshComponent(VertexList vertices, std::vector<int> faces):
      m_vertices(std::move(vertices)), m_faces(std::move(faces)){}

   VertexList &vertices(){return m_vertices;}
   std::vector<int> &faces(){return m_faces;}

};