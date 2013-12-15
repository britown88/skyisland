#include "DamageMarkerManager.h"
#include "IOCContainer.h"
#include "Application.h"
#include "TextComponent.h"
#include "GameComponents.h"

void DamageMarkerManager::updateOnScreenEntity(Entity &e)
{ 
   if(auto app = IOC.resolve<Application>())
   if(auto dm = e.getComponent<DamageMarkerComponent>())
   if(auto tc = e.getComponent<TextComponent>())
   {
      float elapsedTime = app->getTime() - dm->startTime;
      if(elapsedTime >= dm->length)
          e.markedForDeletion = true;
      else if (dm->length - elapsedTime <= 1.0f)
      {
         tc->color.a = (dm->length - elapsedTime) / 1.0f;
      }
   }
}

void DamageMarkerManager::updateOffScreenEntity(Entity &e)
{
   updateOnScreenEntity(e);
}