#pragma once

#include "Vector.h"
#include <vector>
#include <memory>

class Entity;

struct Transform
{
   Transform():scale(Float2(1.0f, 1.0f)), rotationAngle(0.0f){}
   Transform(Float2 scale, Float2 offset, float rotationAngle, Float2 rotationpoint):
      scale(scale), offset(offset), rotationAngle(rotationAngle), rotationPoint(rotationpoint){}

   Float2 scale, offset, rotationPoint;
   float rotationAngle;

};


typedef std::shared_ptr<Transform> TransformPtr;
typedef std::shared_ptr<std::vector<TransformPtr>> TransformList;

Transform buildTransformation(Entity &entity);
void applyGLTransformation(Transform t);
void applyGLTransformation(TransformList tList);