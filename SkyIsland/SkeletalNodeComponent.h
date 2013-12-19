#pragma once
#include "IComponent.h"

#include "Transform.h"
#include "StringTable.h"
#include "Entity.h"
#include <unordered_map>
#include <memory>

struct SNodeConnection
{
   SNodeConnection():connectionPos(Float2()), locked(false){}
   SNodeConnection(Float2 conPos):connectionPos(conPos), locked(false){}
   bool locked;
   Float2 connectionPos;//point (0-1) on parent
   std::shared_ptr<Entity> entity;
};

class SkeletalNodeComponent : public IComponent
{
public:
   const static int ID = 1964797685;
   std::unordered_map<InternString, SNodeConnection> connections;
   std::shared_ptr<Entity> parent;
   Float2 offset;
};