#pragma once

#include "Entity.h"
#include "IAITask.h"
#include <vector>

class CharacterAI
{
   std::weak_ptr<Entity> m_entity;

   std::shared_ptr<IAITask> m_runningTask;

   std::vector<std::shared_ptr<IAITask>> generateTaskList();

public:
   CharacterAI(std::weak_ptr<Entity> entity);

   void update();

};