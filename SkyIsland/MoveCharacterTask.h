#pragma once

#include "IAITask.h"
#include "Vector.h"
#include "PositionComponent.h"
#include "CharacterComponent.h"
#include "GraphicComponents.h"
#include "PhysicsComponents.h"
#include "Entity.h"
#include <memory>

class MoveCharacterTask : public IAITask
{
   Float2 m_target;
   std::weak_ptr<Entity> m_entity;
   bool m_isDone;
public:
   MoveCharacterTask(Float2 target, std::weak_ptr<Entity> entity):
      m_target(target), m_entity(std::move(entity)){}

   void start(){m_isDone = false;}
   void update()
   {
      if(auto e = m_entity.lock())
      if(auto pc = e->getComponent<PositionComponent>())
      if(auto cc = e->getComponent<CharacterComponent>())
      if(auto gb = e->getComponent<GraphicalBoundsComponent>())
      if(auto vc = e->getComponent<VelocityComponent>())
      {
         Float2 dir;
         if(pc->pos.x > m_target.x) dir.x = -1.0f;
         if(pc->pos.x < m_target.x) dir.x = 1.0f;
         if(pc->pos.y > m_target.y) dir.y = 1.0f;
         if(pc->pos.y < m_target.y) dir.y = -1.0f;

         cc->controller->move(dir);

         float minDist = std::max(gb->size.x, gb->size.y);
         minDist *= minDist;
         float dist = (pc->pos.x - m_target.x)*(pc->pos.x - m_target.x) +
            (pc->pos.y - m_target.y)*(pc->pos.y - m_target.y);

         if(dist <= minDist)
         {
            cc->controller->stop();

            if(vc->velocity == Float2())
               m_isDone = true;
         }
            
      }
   }
   void halt(){}
   bool isDone(){return m_isDone;}
   int getPriority(){ return 0; }
};