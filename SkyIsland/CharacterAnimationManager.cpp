#include "CharacterAnimationManager.h"
#include "CharacterComponent.h"
#include "GraphicComponents.h"
#include "IOCContainer.h"
#include "Application.h"

void CharacterAnimationManager::updateOnScreenEntity(Entity &e)
{
   if(auto spr = e.getComponent<SpriteComponent>())
   {
      auto app = IOC.resolve<Application>();
      float time = app->dt() * (app->frameTime() / 1000.0f) * spr->dtMultiplier;
      spr->elapsedTime += time;
   }
   

   if(auto cc = e.getComponent<CharacterComponent>())
      cc->controller->updateAnimation();
}

void CharacterAnimationManager::updateOffScreenEntity(Entity &e){}