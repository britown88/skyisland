#pragma once
#include "IComponent.h"

#include "Transform.h"
#include "StringTable.h"
#include "Entity.h"
#include <unordered_map>
#include <memory>
#include "SkeletalAnimation.h"


struct SNodeConnection
{
   SNodeConnection():connectionPos(Float2()), transform(Transform()), startFrameSet(false), layer(0){}
   SNodeConnection(Float2 conPos):connectionPos(conPos), transform(Transform()), startFrameSet(false), layer(0){}
   Float2 connectionPos;
   Transform transform;
   std::shared_ptr<SkeletalFrame> startFrame;
   bool startFrameSet;
   int layer;
   std::shared_ptr<Entity> entity;
};

class SkeletalNodeComponent : public IComponent
{
public:
   static const unsigned int ID = 1964797685;
   std::unordered_map<InternString, std::shared_ptr<SNodeConnection>> connections;
   std::shared_ptr<SNodeConnection> addConnection(InternString name, Float2 pos)
   {
      connections.insert(std::make_pair(name, std::make_shared<SNodeConnection>(pos)));
      return connections[name];
   }
};

class SkeletonComponent : public IComponent
{
public:
   static const unsigned int ID = 1755713335;
   InternString playingAnimation;
   float elapsedAnimTime, dtMultiplier;
   std::shared_ptr<Entity> entity;
   SkeletonComponent(std::shared_ptr<Entity> skeleton):
      entity(std::move(skeleton)), elapsedAnimTime(0.0f), dtMultiplier(1.0f){}

   void changeAnim(InternString anim)
   {
      if(playingAnimation != anim)
         elapsedAnimTime = 0.0f;

      playingAnimation = anim;

   }
};
