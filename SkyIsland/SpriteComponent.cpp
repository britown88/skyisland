#include "GraphicComponents.h"
#include "IOCContainer.h"
#include "Application.h"

void SpriteComponent::updateTime()
{
   auto app = IOC.resolve<Application>();
   float time = app->dt() * (app->frameTime() / 1000.0f) * dtMultiplier;
   elapsedTime += time;

}