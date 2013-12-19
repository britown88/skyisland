#pragma once
#include "IComponent.h"

#include "Transform.h"
#include "StringTable.h"
#include "Entity.h"
#include <unordered_map>
#include <memory>

class SkeletalNodeComponent : public IComponent
{
public:
   const static int ID = 1964797685;
   std::unordered_map<InternString, std::shared_ptr<Entity>> connections;
   std::shared_ptr<Entity> parent;
   Float2 offset;
};