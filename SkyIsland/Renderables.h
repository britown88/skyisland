#pragma once

#include "IRenderable.h"
#include "Entity.h"
#include <memory>

std::unique_ptr<IRenderable> buildMeshRenderable(Entity &entity, TransformList transforms);
std::unique_ptr<IRenderable> buildTextRenderable(Entity &entity, TransformList transforms);
std::unique_ptr<IRenderable> buildSkeletalRenderable(Entity &entity, TransformList transforms);


struct SkeletalNode
{
   TransformList transforms;
   std::weak_ptr<Entity> entity;
   
};
