#include "AIManager.h"
#include "AIComponent.h"

void AIManager::updateOnScreenEntity(Entity &e)
{
   if(auto ai = e.getComponent<AIComponent>())
      ai->ai->update();
}

void AIManager::updateOffScreenEntity(Entity &e)
{
   updateOnScreenEntity(e);
}