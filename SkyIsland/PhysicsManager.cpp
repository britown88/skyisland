#include "PhysicsManager.h"

#include "PositionComponent.h"
#include "PhysicsComponents.h"
#include "IOCContainer.h"
#include "Application.h"

#include "Trig.h"
#include <algorithm>

void PhysicsManager::updateOnScreenEntity(Entity &ent)
{
   auto &app = IOC.resolve<Application>();
   if(auto p = ent.getComponent<PositionComponent>())
   {
      if(auto bind = ent.getComponent<PositionBindComponent>())
      {
         if(auto bindEntity = bind->entity.lock())
         if(auto bindPos = bindEntity->getComponent<PositionComponent>())
         {
            p->pos = bindPos->pos + bind->offset;
            if(auto elev = bindEntity->getComponent<ElevationComponent>())
               p->pos.y -= elev->elevation;
         }
            
      }

      if(auto v = ent.getComponent<VelocityComponent>())
      {
         if(auto elev = ent.getComponent<ElevationComponent>())
         {
            elev->elevation += elev->impulse * app->dt();
            
            if(elev->elevation > 0.0f)
            {
               elev->impulse -= elev->gravityStrength * app->dt();
            }
            else
            {
               //elev->impulse = -((elev->impulse * 3) / 4);//bouncy
               //if(elev->impulse < 1.0f)
                  elev->impulse = 0.0f;
               elev->elevation = 0.0f;
            }
         }

         if(auto a = ent.getComponent<AccelerationComponent>())
         {
            float angle = atan2(a->direction.y, a->direction.x);
            Float2 delta = Float2(
               cos(angle) * a->acceleration, 
               -(sin(angle) * a->acceleration));

            v->velocity += delta * app->dt();

            //cap
            float mag = sqrt(v->velocity.x*v->velocity.x + v->velocity.y*v->velocity.y);

            if(fabs(mag) > a->maxVelocity)
            {
               float angle = atan2(v->velocity.y, v->velocity.x);
               v->velocity.x = cos(angle) * a->maxVelocity;
               v->velocity.y = sin(angle) * a->maxVelocity;
            }
         }

         if(auto f = ent.getComponent<FrictionComponent>())
         {
            if(v->velocity.x > 0) v->velocity.x = std::max(0.0f, v->velocity.x - f->friction * (float)app->dt());
            else if(v->velocity.x < 0) v->velocity.x = std::min(0.0f, v->velocity.x + f->friction * (float)app->dt());

            if(v->velocity.y > 0) v->velocity.y = std::max(0.0f, v->velocity.y - f->friction * (float)app->dt());
            else if(v->velocity.y < 0) v->velocity.y = std::min(0.0f, v->velocity.y + f->friction * (float)app->dt());               

         }

         p->pos = p->pos + v->velocity * app->dt();
      }
   }

}

void PhysicsManager::updateOffScreenEntity(Entity &e){updateOnScreenEntity(e);}
