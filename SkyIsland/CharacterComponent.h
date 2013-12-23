#pragma once

#include "IComponent.h"
#include "CharacterController.h"
#include <memory>

class CharacterComponent : public IComponent
{
public:
   static const unsigned int ID = 1933247510;

   CharacterComponent(std::weak_ptr<Entity> e):controller(std::unique_ptr<CharacterController>(new CharacterController(std::move(e)))){}

   std::unique_ptr<CharacterController> controller;

};
