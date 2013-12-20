#pragma once

#include <string>
#include <vector>
#include "StringTable.h"
#include "Entity.h"
#include "PositionComponent.h"
#include "RotationComponent.h"
#include "SkeletalNodeComponent.h"

#include "Transform.h"

struct SkeletalFrame
{
   SkeletalFrame(int frame, Transform transform):
      frame(frame), transform(transform), layer(0), layerSet(false){}
   const int frame;
   Transform transform;
   int layer;
   bool layerSet;//only change if layer wa sset

   SkeletalFrame &setRotation(float rotation){transform.rotationAngle = rotation; return *this;}
   SkeletalFrame &setOffset(float x, float y){transform.offset = Float2(x, y); return *this;}
   SkeletalFrame &setLayer(int l){layer = l; layerSet = true; return *this;}

};

struct SkeletalFrameObject
{
   std::string fullName;
   std::vector<InternString> name;
   std::vector<SkeletalFrame> frames;

   SkeletalFrameObject(std::string fullName, std::vector<InternString> name):
      fullName(std::move(fullName)), name(std::move(name)){}

};

class SkeletalAnimation
{
   std::vector<SkeletalFrameObject> m_frameObjs;
   float m_framesPerSecond;
   bool m_loop;
   int m_frameCount;

public:
   SkeletalAnimation(float framesPerSecond);

   void setLooping(bool loop){m_loop = loop;}

   void updateEntity(float timeElapsed, Entity &entity);

   SkeletalFrame &addFrame(std::string partName, int frame);

};