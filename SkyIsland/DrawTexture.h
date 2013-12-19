#pragma once

#include "IDrawObject.h"

#include <vector>
#include <memory>
#include "Vertex.h"
#include "Transform.h"
#include "StringTable.h"

class DrawTexture : public IDrawObject
{
   std::shared_ptr<VertexList> m_vertices;
   std::shared_ptr<std::vector<int>> m_faces;

   unsigned int m_gltexture;
   Transform m_transform;
   TransformList m_transformList;

   InternString m_texture;

   unsigned int m_blendS, m_blendD;

public:
   DrawTexture(){}
   DrawTexture(InternString texture, std::shared_ptr<VertexList> vertices, std::shared_ptr<std::vector<int>> faces, Transform transform=Transform());
   DrawTexture(InternString texture, std::shared_ptr<VertexList> vertices, std::shared_ptr<std::vector<int>> faces, TransformList transform);
   DrawTexture(unsigned int texture, std::shared_ptr<VertexList> vertices, std::shared_ptr<std::vector<int>> faces, Transform transform=Transform());

   void setBlendFunc(unsigned int sFactor, unsigned int dFactor);

   void draw();

};