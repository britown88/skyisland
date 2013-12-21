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
      frame(frame), _transform(transform), _layer(0), _layerSet(false), _rotationPart(nullptr),
      _flipX(false), _flipY(false){}
   const int frame;
   Transform _transform;
   int _layer;
   bool _layerSet, _flipX, _flipY;//only change if layer wa sset
   InternString _rotationPart;//set to rotate based on a connection position

   SkeletalFrame &flipX(bool flip){_flipX = flip; return *this;}
   SkeletalFrame &flipY(bool flip){_flipY = flip; return *this;}
   SkeletalFrame &setRotation(float rotation){_transform.rotationAngle = rotation; return *this;}
   SkeletalFrame &setRotation(float rotation, Float2 rotationPoint)
   {
      _transform.rotationPoint = rotationPoint;
      _transform.rotationAngle = rotation; 
      return *this;
   }
   SkeletalFrame &setRotation(float rotation, std::string connection)
   {
      _rotationPart = IOC.resolve<StringTable>()->get(connection.c_str());
      _transform.rotationAngle = rotation; 
      return *this;
   }
   SkeletalFrame &setOffset(float x, float y){_transform.offset = Float2(x, y); return *this;}
   SkeletalFrame &setLayer(int l){_layer = l; _layerSet = true; return *this;}

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