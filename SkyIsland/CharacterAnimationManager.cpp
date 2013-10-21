#include "CharacterAnimationManager.h"
#include "CharacterComponent.h"
#include "GraphicComponents.h"
#include "IOCContainer.h"
#include "Application.h"

void CharacterAnimationManager::updateOnScreenEntity(Entity &e)
{
   if(auto spr = e.getComponent<SpriteComponent>())
      spr->updateTime();

   if(auto cc = e.getComponent<CharacterComponent>())
      cc->controller->updateAnimation();
}

void CharacterAnimationManager::updateOffScreenEntity(Entity &e){}