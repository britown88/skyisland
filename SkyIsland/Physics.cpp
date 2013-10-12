#include "Physics.h"

#include "IPositionComponent.h"
#include "PhysicsComponents.h"
#include "IOCContainer.h"
#include "Application.h"

#include "Trig.h"
#include <algorithm>

void Physics::updateWorldPhsyics(IScene &world, Rectf viewBounds)
{
   auto &app = IOC.resolve<Application>();

   for(auto &ent : world.getEntities())
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

               v.velocity += delta * app.dt();

               //cap
               float mag = sqrt(v.velocity.x*v.velocity.x + v.velocity.y*v.velocity.y);

               if(fabs(mag) > a.maxVelocity)
               {
                  float angle = atan2(v.velocity.y, v.velocity.x);
                  v.velocity.x = cos(angle) * a.maxVelocity;
                  v.velocity.y = sin(angle) * a.maxVelocity;
               }
            }

            if(ent.hasComponent<FrictionComponent>())
            {
               auto &f = ent.getComponent<FrictionComponent>();

               if(v.velocity.x > 0) v.velocity.x = std::max(0.0f, v.velocity.x - f.friction * (float)app.dt());
               else if(v.velocity.x < 0) v.velocity.x = std::min(0.0f, v.velocity.x + f.friction * (float)app.dt());

               if(v.velocity.y > 0) v.velocity.y = std::max(0.0f, v.velocity.y - f.friction * (float)app.dt());
               else if(v.velocity.y < 0) v.velocity.y = std::min(0.0f, v.velocity.y + f.friction * (float)app.dt());               

            }

            p.setPosition(p.getPosition() + v.velocity * app.dt());
         }
      }
   }

}