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
      if(app->getTime() - dm->startTime >= dm->length)
         e.markedForDeletion = true;
      else
      {
         tc->color.a = 1.0f - ((app->getTime() - dm->startTime) / dm->length);
      }
   }
}

void DamageMarkerManager::updateOffScreenEntity(Entity &e)
{
   updateOnScreenEntity(e);
}