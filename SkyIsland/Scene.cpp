#include "Scene.h"
#include "PositionComponent.h"
#include "GraphicComponents.h"
#include "IOCContainer.h"
#include "Application.h"
#include "ComponentHelpers.h"
#include "IEntityManager.h"

Scene::Scene(Float2 size, int sqrtPartitionCount):
   m_size(size), m_pCount(sqrtPartitionCount)
{
   m_partSize = Float2(m_size.x / m_pCount, m_size.y / m_pCount);

   for(int i = 0; i < m_pCount*m_pCount; ++i)
   {
      m_partitions.push_back(ScenePartition());
      m_partitions.back().lastUpdatedTimestamp = (10.0 / (m_pCount*m_pCount)) * i;
   }
      
}



Float2 Scene::getSize(){return m_size;}
void Scene::addEntity(std::shared_ptr<Entity> entity)
{
   Rectf eBounds = CompHelpers::getEntityBounds(*entity);
   entity->partitionBounds = eBounds;

   Rectf cBounds = Rectf(0, 0, m_size.x, m_size.y).intersection(eBounds);  

   for(int y = cBounds.top / m_partSize.y; y <= cBounds.bottom / m_partSize.y && y < m_pCount; ++y)
      for(int x = cBounds.left / m_partSize.x; x <= cBounds.right / m_partSize.x && x < m_pCount; ++x)
         m_partitions[y*m_pCount + x].entities[entity] = entity;
}

void Scene::removeEntity(std::shared_ptr<Entity> entity)
{
   Rectf cBounds = Rectf(0, 0, m_size.x, m_size.y).intersection(entity->partitionBounds);   

   //remove moved entities from partition table
   for(int y = cBounds.top / m_partSize.y; y <= cBounds.bottom / m_partSize.y && y < m_pCount; ++y)
      for(int x = cBounds.left / m_partSize.x; x <= cBounds.right / m_partSize.x && x < m_pCount; ++x)
         m_partitions[y*m_pCount + x].entities.erase(entity);

}

//add an entitymanager that will get called when the scene is updated
void Scene::registerEntityManager(std::shared_ptr<IEntityManager> em)
{
   m_entityManagers.push_back(std::move(em));
}

//set the visibility rects within the scene for the next update
void Scene::setVisibleRects(std::vector<Rectf> rects)
{
   //set all partitions to invis
   for(auto &p : m_partitions)
      p.visible = false;

   Rectf mapBounds = Rectf(0, 0, m_size.x, m_size.y);

   //set partitions to vis from supplied visRects
   for(auto &r : rects)
   {
      Rectf cBounds = mapBounds.intersection(r);   

      for(int y = cBounds.top / m_partSize.y; y <= cBounds.bottom / m_partSize.y && y < m_pCount; ++y)
         for(int x = cBounds.left / m_partSize.x; x <= cBounds.right / m_partSize.x && x < m_pCount; ++x)
            m_partitions[y*m_pCount + x].visible = true;
   }

   //Now set priority values for invis partitions
   //TODO: This
}

//update scene entities
void Scene::update()
{
   std::vector<std::weak_ptr<Entity>> updatedEntities, movedEntities;
   auto app = IOC.resolve<Application>();

   for(auto &p : m_partitions)
   {
      if(p.visible)
      {
         for(auto &pe : p.entities)
         {
            auto e = pe.first;
            if(!e->updated)
            {
               for(auto em : m_entityManagers)
                  em->updateOnScreenEntity(*e);

               updatedEntities.push_back(e);
               e->updated = true;
               if(auto pc = e->getComponent<PositionComponent>())
               {
                  if(pc->oldPos != pc->pos)
                  {
                     pc->oldPos = pc->pos;
                     movedEntities.push_back(pe.second);
                  }
               }
            }            
         }  
      }
      else
      {         
         //not visible
         double dt = app->getTime() - p.lastUpdatedTimestamp;
         if(dt > 1.0);//disabled for now
         {            
            p.lastUpdatedTimestamp += dt;
            for(auto &pe : p.entities)
            {
               auto e = pe.first;
               if(!e->updated)
               {
                  for(auto em : m_entityManagers)
                     em->updateOffScreenEntity(*e);

                  updatedEntities.push_back(e);
                  e->updated = true;
                  if(auto pc = e->getComponent<PositionComponent>())
                  {
                     if(pc->oldPos != pc->pos)
                     {
                        pc->oldPos = pc->pos;
                        movedEntities.push_back(pe.second);
                     }
                  }
               }            
            }
         }         
      }
   }

   for(auto e : updatedEntities)
      if(auto p = e.lock())
         p->updated = false;
   
   for(auto &pe : movedEntities)
   {
      if(auto p = pe.lock())
      {
         //remove from partiiton table
         removeEntity(p);

         //reinsert into new locations
         addEntity(p);
      }
      
   }
}

std::vector<std::shared_ptr<Entity>> Scene::getEntities()
{
   std::vector<std::shared_ptr<Entity>> entities;

   for(auto &p : m_partitions)
      for(auto &pe : p.entities)
         if(!pe.first->updated)
         {
            pe.first->updated = true;
            entities.push_back(pe.first);
         }
   
   for(auto e : entities)
      e->updated = false;

   return std::move(entities);
}

std::vector<std::shared_ptr<Entity>> Scene::getEntities(Rectf &bounds)
{
   Rectf cBounds = Rectf(0, 0, m_size.x, m_size.y).intersection(bounds);   
   std::vector<std::shared_ptr<Entity>> entities;
   std::unordered_set<std::shared_ptr<Entity>> updatedEntities;

   for(int y = cBounds.top / m_partSize.y; y <= cBounds.bottom / m_partSize.y && y < m_pCount; ++y)
      for(int x = cBounds.left / m_partSize.x; x <= cBounds.right / m_partSize.x && x < m_pCount; ++x)
         for(auto &ent : m_partitions[y*m_pCount + x].entities)
            if(updatedEntities.find(ent.first) == updatedEntities.end() &&
               bounds.contains(CompHelpers::getEntityBounds(*ent.first)))
            {
               entities.push_back(ent.first);
               updatedEntities.insert(ent.first);
               //ent.first->updated = true;
            }

   //for(auto e : entities)
      //e->updated = false;

   return std::move(entities);

}
