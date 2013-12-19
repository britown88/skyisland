#pragma once

#include "IRenderable.h"
#include "Entity.h"
#include <memory>

std::unique_ptr<IRenderable> buildMeshRenderable(Entity &entity);
std::unique_ptr<IRenderable> buildTextRenderable(Entity &entity);
std::unique_ptr<IRenderable> buildSkeletalRenderable(Entity &entity);


struct SkeletalNode
{
   std::shared_ptr<VertexList> m_vertices;
   std::shared_ptr<std::vector<int>> m_faces;
   TransformList transforms;

   InternString m_texture;
   unsigned int blendS, blendD;
   
};
