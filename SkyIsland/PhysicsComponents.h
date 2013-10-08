#pragma once

#include "IComponent.h"

#include "Vector.h"

class VelocityComponent : public IComponent
{
public:
   Float2 velocity;
   VelocityComponent(Float2 velocity):velocity(velocity){}
};

class AccelerationComponent : public IComponent
{
public:
   float direction;
   float acceleration;
   float maxVelocity;

   AccelerationComponent(float dir, float accel, float maxVelocity):direction(dir), acceleration(accel), maxVelocity(maxVelocity){}
};

class FrictionComponent : public IComponent
{
public:
   float friction;
   FrictionComponent(float friction):friction(friction){}
};