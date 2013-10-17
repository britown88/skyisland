#pragma once

#include "IComponent.h"

#include "Vector.h"

class VelocityComponent : public IComponent
{
public:
   static const int ID = 2678353989;
   Float2 velocity;
   VelocityComponent(Float2 velocity):velocity(velocity){}
};

class AccelerationComponent : public IComponent
{
public:
   static const int ID = 2926389175;
   float direction;
   float acceleration;
   float maxVelocity;

   AccelerationComponent(float dir, float accel, float maxVelocity):direction(dir), acceleration(accel), maxVelocity(maxVelocity){}
};

class FrictionComponent : public IComponent
{
public:
   static const int ID = 3508263007;
   float friction;
   FrictionComponent(float friction):friction(friction){}
};