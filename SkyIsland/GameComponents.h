#pragma once

#include "IComponent.h"
#include "Vector.h"
#include "Entity.h"

class AttackComponent : public IComponent
{
public:
   static const unsigned int ID = 3835124759;
   //to contain:  attack type, damage, affects, etc
   //for now just a direction the attack is heading in
   Float2 attackDirection;
   std::weak_ptr<Entity> attacker;
   AttackComponent(std::weak_ptr<Entity> attacker, Float2 attackDirection):
      attacker(std::move(attacker)), attackDirection(attackDirection){}
};

class DamageMarkerComponent : public IComponent
{
public:
   static const unsigned int ID = 2176428309;
   std::weak_ptr<Entity> marker;

   float startTime;
   float length;

   DamageMarkerComponent(std::weak_ptr<Entity> marker):
      marker(marker){}

};
