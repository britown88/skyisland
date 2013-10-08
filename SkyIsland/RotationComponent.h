#pragma once

#include "IComponent.h"
#include "Vector.h"

class RotationComponent : public IComponent
{
   float m_angle;
   Float2 m_point;
public:
   RotationComponent(float angle, Float2 point):
      m_angle(angle), m_point(point){}

   Float2 getPoint(){return m_point;}
   float getAngle(){return m_angle;}

   void setPoint(Float2 point){m_point = point;}
   void setAngle(float angle){m_angle = angle;}
};
