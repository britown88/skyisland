#pragma once

#include "IAITask.h"
#include <memory>
#include <vector>

class TaskList : public IAITask
{
   int m_priority;
   std::vector<std::shared_ptr<IAITask>> m_taskList;
   int m_taskIndex;
public:
   TaskList(int priority):m_priority(priority){}

   void addTask(std::shared_ptr<IAITask> task)
   {
      m_taskList.push_back(std::move(task));
   }

   void start()
   {
      m_taskIndex = 0;
      if(!m_taskList.empty())
         m_taskList[0]->start();
   }

   void update()
   {
      if(m_taskIndex < m_taskList.size())
      {
         m_taskList[m_taskIndex]->update();
         if(m_taskList[m_taskIndex]->isDone())
         {
            ++m_taskIndex;
            if(m_taskIndex < m_taskList.size())
               m_taskList[m_taskIndex]->start();
         }
            
      }
   }
   void halt(){}
   bool isDone(){return m_taskIndex >= m_taskList.size();}
   int getPriority(){ return m_priority; }
};