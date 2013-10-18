#include "CharacterAnimationManager.h"
#include "CharacterComponent.h"

void CharacterAnimationManager::updateOnScreenEntity(Entity &e)
{
   if(auto cc = e.getComponent<CharacterComponent>())
      cc->controller->updateAnimation();
}

void CharacterAnimationManager::updateOffScreenEntity(Entity &e){}