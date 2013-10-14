#pragma once

#include "IRenderable.h"
#include "Entity.h"
#include <memory>

std::unique_ptr<IRenderable> buildMeshRenderable(Entity &entity);
