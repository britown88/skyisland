#pragma once

#include "Entity.h"

namespace CharacterEntities
{
   std::shared_ptr<Entity> buildCharacter();
   std::shared_ptr<Entity> buildBasicBodyPart(char *texture, Float2 size, Float2 center);
   void buildCharacterChildren(std::shared_ptr<Entity> e);
   std::shared_ptr<Entity> buildSwordAttack(std::weak_ptr<Entity> attacker);
   std::shared_ptr<Entity> buildDamageMarker(std::weak_ptr<Entity> target);
}