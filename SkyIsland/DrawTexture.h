#pragma once

#include "IDrawObject.h"

#include <vector>
#include <memory>
#include "Vertex.h"
#include "Transform.h"

class DrawTexture : public IDrawObject
{
   std::shared_ptr<VertexList> m_vertices;
   std::shared_ptr<std::vector<int>> m_faces;

   Transform m_transform;

   std::string m_texture;

public:
   DrawTexture(std::string texture, std::shared_ptr<VertexList> vertices, std::shared_ptr<std::vector<int>> faces, Transform transform=Transform());

   void draw();

};