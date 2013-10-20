#include "CharacterAI.h"
#include "SeanSort.h"
#include "AIComponent.h"
#include "MoveCharacterTask.h"
#include "Application.h"
#include "WaitTask.h"
#include "CharacterAttackTask.h"
#include "TaskList.h"

CharacterAI::CharacterAI(std::weak_ptr<Entity> entity):m_entity(std::move(entity)){}

std::vector<std::shared_ptr<IAITask>> CharacterAI::generateTaskList()
{
   std::vector<std::shared_ptr<IAITask>> taskList;
   auto app = IOC.resolve<Application>();

   if(auto e = m_entity.lock())
   {
      if(auto wander = e->getComponent<WanderComponent>())
      {
         auto list = std::make_shared<TaskList>(0);
         list->addTask(std::make_shared<MoveCharacterTask>(Float2(app->rand(0, 10000), app->rand(0, 10000)), m_entity));
         list->addTask(std::make_shared<WaitTask>(1.0f));
         list->addTask(std::make_shared<CharacterAttackTask>(m_entity));
         list->addTask(std::make_shared<WaitTask>(1.0f));

         taskList.push_back(std::move(list));
      }
   }

   return std::move(taskList);
}

void CharacterAI::update()
{
   if(auto e = m_entity.lock())
   {
      if(m_runningTask)
      {
         //update running task
         m_runningTask->update();
         if(m_runningTask->isDone())
            m_runningTask.reset();
      }
      else//no running task
      {
         auto list = std::move(generateTaskList());
         if(!list.empty())
         {
            //sort by priority
            list = seanSort(std::move(list), [&](const std::shared_ptr<IAITask> &t1, const std::shared_ptr<IAITask> &t2)->bool
            { 
               return t1->getPriority() > t2->getPriority();
            });

            //start a task
            m_runningTask = list[0];
            m_runningTask->start();
         }         
      }
   }
}