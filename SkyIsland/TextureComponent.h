#pragma once

#include "IComponent.h"
#include "Vertex.h"
#include <vector>
#include <string>

class TextureComponent : public IComponent
{
   std::vector<Vertex> m_vertices;
   std::vector<int> m_faces;
   

public:
   std::string texturePath;

   TextureComponent(std::vector<Vertex> vertices, std::vector<int> faces, std::string texturePath):
      m_vertices(std::move(vertices)), m_faces(std::move(faces)), texturePath(texturePath){}

   std::vector<Vertex> &vertices(){return m_vertices;}
   std::vector<int> &faces(){return m_faces;}

};