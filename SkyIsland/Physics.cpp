#include "Physics.h"

#include "IPositionComponent.h"
#include "PhysicsComponents.h"
#include "IOCContainer.h"
#include "Application.h"

#include "Trig.h"
#include <algorithm>

static double updateTimestamp = 0.0;

void Physics::updateWorldPhsyics(IScene &world, Rectf viewBounds)
{
   double deltaTime = IOC.resolve<Application>().getTime() - updateTimestamp;
   float dt = deltaTime / 0.01666;

   for(auto &ent : *world.getEntities())
   {
      if(ent.hasComponent<IPositionComponent>())
      {
         auto &p = ent.getComponent<IPositionComponent>();

         if(ent.hasComponent<VelocityComponent>())
         {
            auto &v = ent.getComponent<VelocityComponent>();

            if(ent.hasComponent<AccelerationComponent>())
            {
               auto &a = ent.getComponent<AccelerationComponent>();
               Float2 delta = Float2(
                  cos(a.direction * PI / 180.0f) * a.acceleration, 
                  -(sin(a.direction * PI / 180.0f) * a.acceleration));

               //v.velocity = v.velocity + delta;

               if(fabs(v.velocity.x + delta.x) <= a.maxVelocity) v.velocity.x += delta.x * dt;
               if(fabs(v.velocity.y + delta.y) <= a.maxVelocity) v.velocity.y += delta.y * dt;                  

            }

            if(ent.hasComponent<FrictionComponent>())
            {
               auto &f = ent.getComponent<FrictionComponent>();

               if(v.velocity.x > 0) v.velocity.x = std::max(0.0f, v.velocity.x - f.friction * dt);
               else if(v.velocity.x < 0) v.velocity.x = std::min(0.0f, v.velocity.x + f.friction * dt);

               if(v.velocity.y > 0) v.velocity.y = std::max(0.0f, v.velocity.y - f.friction * dt);
               else if(v.velocity.y < 0) v.velocity.y = std::min(0.0f, v.velocity.y + f.friction * dt);               

            }

            p.setPosition(p.getPosition() + v.velocity * dt);
         }
      }
   }

   updateTimestamp = IOC.resolve<Application>().getTime();
}