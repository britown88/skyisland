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
   auto &app = IOC.resolve<Application>();

   double deltaTime = app.getTime() - updateTimestamp;
   float dt = deltaTime / (app.frameTime() / 1000.0);

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

               if(fabs(v.velocity.x + delta.x * dt) <= a.maxVelocity) 
                  v.velocity.x += delta.x * dt;
               else
                  if(v.velocity.x > 0.0f)
                     v.velocity.x = a.maxVelocity;
                  else
                     v.velocity.x = -a.maxVelocity;
               
               if(fabs(v.velocity.y + delta.y * dt) <= a.maxVelocity) 
                  v.velocity.y += delta.y * dt;   
               else
                  if(v.velocity.y > 0.0f)
                     v.velocity.y = a.maxVelocity;
                  else
                     v.velocity.y = -a.maxVelocity;

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

   updateTimestamp = app.getTime();
}