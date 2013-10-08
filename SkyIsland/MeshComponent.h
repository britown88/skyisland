#pragma once

#include "IComponent.h"
#include "IRenderable.h"
#include <memory>

class MeshComponent : public IComponent
{
   std::vector<Vertex> m_vertices;
   std::vector<int> m_faces;

public:
   MeshComponent(std::vector<Vertex> vertices, std::vector<int> faces):
      m_vertices(std::move(vertices)), m_faces(std::move(faces)){}

   std::vector<Vertex> &vertices(){return m_vertices;}
   std::vector<int> &faces(){return m_faces;}

};