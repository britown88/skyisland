#pragma once

#include "IComponent.h"
#include "CharacterAI.h"
#include <memory>

class AIComponent : public IComponent
{
public:
   static const unsigned int ID = 2093905988;

   AIComponent(std::weak_ptr<Entity> e):ai(std::unique_ptr<CharacterAI>(new CharacterAI(std::move(e)))){}

   std::unique_ptr<CharacterAI> ai;

};

class WanderComponent : public IComponent
{
public:
   static const unsigned int ID = 2428105083;
   WanderComponent(){}
};
