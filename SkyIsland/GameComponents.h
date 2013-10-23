#pragma once

#include "IComponent.h"
#include "Vector.h"

class AttackComponent : public IComponent
{
public:
   static const int ID = 3835124759;
   //to contain:  attack type, damage, affects, etc
   //for now just a direction the attack is heading in
   Float2 attackDirection;
   AttackComponent(Float2 attackDirection):attackDirection(attackDirection){}
};