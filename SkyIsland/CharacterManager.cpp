#include "CharacterManager.h"
#include "CharacterComponent.h"
#include "GraphicComponents.h"
#include "IOCContainer.h"
#include "Application.h"

void CharacterManager::updateOnScreenEntity(Entity &e)
{ 

   if(auto cc = e.getComponent<CharacterComponent>())
      cc->controller->updateOnScreen();
}

void CharacterManager::updateOffScreenEntity(Entity &e)
{
   if(auto cc = e.getComponent<CharacterComponent>())
      cc->controller->updateOffScreen();
}