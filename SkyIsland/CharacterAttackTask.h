#pragma once

#include "IAITask.h"
#include "Vector.h"
#include "PositionComponent.h"
#include "CharacterComponent.h"
#include "GraphicComponents.h"
#include "PhysicsComponents.h"
#include "Entity.h"
#include <memory>

class CharacterAttackTask : public IAITask
{
   std::weak_ptr<Entity> m_entity;
public:
   CharacterAttackTask(std::weak_ptr<Entity> entity):
      m_entity(std::move(entity)){}

   void start()
   {
      if(auto e = m_entity.lock())
      if(auto cc = e->getComponent<CharacterComponent>())
      {
         cc->controller->attack();
            
      }
   }
   void update()
   {
      
   }
   void halt(){}
   bool isDone()
   {
      if(auto e = m_entity.lock())
      if(auto cc = e->getComponent<CharacterComponent>())
      {
         return cc->controller->currentTaskDone();            
      }
      return true;
   }
   int getPriority(){ return 0; }
};