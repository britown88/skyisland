#pragma once

#include "IComponent.h"
#include "IRenderable.h"
#include <memory>

class MeshComponent : public IComponent
{
public:
   static const int ID = 3115623613;

   MeshComponent(VertexList vertices, std::vector<int> faces):
      vertices(std::make_shared<VertexList>(std::move(vertices))), 
      faces(std::make_shared<std::vector<int>>(std::move(faces))){}

   std::shared_ptr<VertexList> vertices;
   std::shared_ptr<std::vector<int>> faces;

};