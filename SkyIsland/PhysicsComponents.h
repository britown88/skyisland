#pragma once

#include "IComponent.h"

#include "Vector.h"

class VelocityComponent : public IComponent
{
public:
   static const unsigned int ID = 2678353989;
   Float2 velocity;
   VelocityComponent(Float2 velocity):velocity(velocity){}
};

class AccelerationComponent : public IComponent
{
public:
   static const unsigned int ID = 2926389175;
   Float2 direction;
   float acceleration;
   float maxVelocity;

   AccelerationComponent(Float2 dir, float accel, float maxVelocity):direction(dir), acceleration(accel), maxVelocity(maxVelocity){}
};

class FrictionComponent : public IComponent
{
public:
   static const unsigned int ID = 3508263007;
   float friction;
   FrictionComponent(float friction):friction(friction){}
};

class ElevationComponent : public IComponent
{
public:
   static const unsigned int ID = 658737599;
   float impulse;
   float elevation;
   float gravityStrength;
   ElevationComponent(float gravityStrength):
      gravityStrength(gravityStrength), impulse(0.0f), elevation(0.0f){}
};

//used to bind an entities position to taht of another
class PositionBindComponent : public IComponent
{
public:
   static const unsigned int ID = 3545194511;
   std::weak_ptr<Entity> entity;
   Float2 offset;
   PositionBindComponent(std::weak_ptr<Entity> entity, Float2 offset):
      entity(entity), offset(offset){}
};

class CollisionAreaComponent : public IComponent
{
public:
   static const unsigned int ID = 2877756257;

   Rectf area;
   CollisionAreaComponent(Rectf area):area(area){}
};
