#include "Scene.h"
#include "PositionComponent.h"
#include "GraphicComponents.h"

Scene::Scene(Float2 size, int sqrtPartitionCount):
   m_size(size), m_pCount(sqrtPartitionCount)
{
   m_partSize = Float2(m_size.x / m_pCount, m_size.y / m_pCount);

   for(int i = 0; i < m_pCount*m_pCount; ++i)
      m_partitions.push_back(ScenePartition());
}

Float2 Scene::getSize(){return m_size;}
void Scene::addEntity(std::shared_ptr<Entity> entity)
{
   if(entity->hasComponent<PositionComponent>())
   {
      auto &pc = entity->getComponent<PositionComponent>();
      Rectf eBounds = Rectf(pc.pos.x, pc.pos.y, pc.pos.x, pc.pos.y);

      if(entity->hasComponent<GraphicalBoundsComponent>())
      {
         auto &gb = entity->getComponent<GraphicalBoundsComponent>();
         eBounds = Rectf(
            pc.pos.x - (gb.size.x * gb.center.x),
            pc.pos.y - (gb.size.y * gb.center.y),
            pc.pos.x + (gb.size.x * gb.center.x),
            pc.pos.y + (gb.size.y * gb.center.y)
         );
      }

      Rectf cBounds = Rectf(0, 0, m_size.x, m_size.y).intersection(eBounds);  

      for(int y = cBounds.top / m_partSize.y; y <= cBounds.bottom / m_partSize.y && y < m_pCount; ++y)
         for(int x = cBounds.left / m_partSize.x; x <= cBounds.right / m_partSize.x && x < m_pCount; ++x)
            m_partitions[y*m_pCount + x].entities.insert(entity);

   }
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
   for(auto p : m_partitions)
      p.visible = false;

   //set partitions to vis from supplied visRects
   for(auto &r : rects)
   {
      Rectf cBounds = Rectf(0, 0, m_size.x, m_size.y).intersection(r);   

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
   std::unordered_set<std::shared_ptr<Entity>> updatedEntities, movedEntities;

   for(auto p : m_partitions)
   {
      if(p.visible)
      {
         for(auto e : p.entities)
         {
            if(updatedEntities.find(e) == updatedEntities.end())
            {
               for(auto em : m_entityManagers)
                  em->updateOnScreenEntity(*e);

               updatedEntities.insert(e);
               if(e->hasComponent<PositionComponent>())
               {
                  auto &pc = e->getComponent<PositionComponent>();
                  if(pc.oldPos != pc.pos)
                  {
                     pc.oldPos = pc.pos;
                     movedEntities.insert(e);
                  }
               }
            }            
         }  
      }
   }
   
   for(auto e : movedEntities)
   {
      //remove moved entities from partition table
      for(auto &p : m_partitions)
         p.entities.erase(e);

      //reinsert into new locations
      addEntity(e);
   }
}

std::vector<std::shared_ptr<Entity>> Scene::getEntities()
{
   std::vector<std::shared_ptr<Entity>> entities;
   for(auto p : m_partitions)
      for(auto e : p.entities)
         entities.push_back(e);

   return std::move(entities);
}

std::vector<std::shared_ptr<Entity>> Scene::getEntities(const Rectf bounds)
{
   Rectf cBounds = Rectf(0, 0, m_size.x, m_size.y).intersection(bounds);   
   std::vector<std::shared_ptr<Entity>> entities;

   for(int y = cBounds.top / m_partSize.y; y <= cBounds.bottom / m_partSize.y && y < m_pCount; ++y)
      for(int x = cBounds.left / m_partSize.x; x <= cBounds.right / m_partSize.x && x < m_pCount; ++x)
         for(auto ent : m_partitions[y*m_pCount + x].entities)
            entities.push_back(ent);

   return std::move(entities);

}
