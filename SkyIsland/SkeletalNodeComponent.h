#pragma once
#include "IComponent.h"

#include "Transform.h"
#include "StringTable.h"
#include "Entity.h"
#include <unordered_map>
#include <memory>

struct SNodeConnection
{
   SNodeConnection():connectionPos(Float2()), transform(Transform()), startFrameSet(false){}
   SNodeConnection(Float2 conPos):connectionPos(conPos), transform(Transform()), startFrameSet(false){}
   Float2 connectionPos;
   Transform transform, startFrame;
   bool startFrameSet;
   std::shared_ptr<Entity> entity;
};

class SkeletalNodeComponent : public IComponent
{
public:
   const static int ID = 1964797685;
   std::unordered_map<InternString, SNodeConnection> connections;
};

class SkeletonComponent : public IComponent
{
public:
   const static int ID = 1755713335;
   InternString playingAnimation;
   float elapsedAnimTime, dtMultiplier;
   std::shared_ptr<Entity> entity;
   SkeletonComponent(std::shared_ptr<Entity> skeleton):
      entity(std::move(skeleton)), elapsedAnimTime(0.0f), dtMultiplier(1.0f){}
};