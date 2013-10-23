#include "AttackManager.h"
#include "CharacterComponent.h"
#include "PhysicsComponents.h"
#include "GameComponents.h"
#include "ComponentHelpers.h"
#include "IOCContainer.h"
#include "Application.h"

Rectf getCollisionFromBounds(Rectf &bounds, Rectf &collisionArea)
{
   return Rectf(
         bounds.left + collisionArea.left * bounds.width(),
         bounds.top + collisionArea.top * bounds.height(),
         bounds.left + collisionArea.right * bounds.width(),
         bounds.top + collisionArea.bottom * bounds.height()
         );
}

void AttackManager::updateOnScreenEntity(Entity &e)
{
   //do collision shit here
   if(auto ac = e.getComponent<AttackComponent>())
   if(auto cc = e.getComponent<CollisionAreaComponent>())
   {
      Rectf bounds = getCollisionFromBounds(CompHelpers::getEntityBounds(e), cc->area);
      auto eList = e.getScene().lock()->getEntities(bounds);

      for(auto &collidingEntity : eList)
      {
         if(collidingEntity != ac->attacker.lock())
         if(auto cc2 = collidingEntity->getComponent<CollisionAreaComponent>())
         {
            Rectf bounds2 = getCollisionFromBounds(CompHelpers::getEntityBounds(*collidingEntity), cc2->area);

            if(bounds2.contains(bounds))
            {

               if(auto collidingChar = collidingEntity->getComponent<ElevationComponent>())
               {
                  collidingChar->impulse = 10.0f;
               }
            }
         }
      }
   }
}

void AttackManager::updateOffScreenEntity(Entity &e){updateOnScreenEntity(e);}