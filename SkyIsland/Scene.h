#pragma once

#include "IScene.h"
#include <unordered_set>
#include <unordered_map>


struct ScenePartition
{
   ScenePartition():updateDelay(0), lastUpdatedTimestamp(0.0), visible(false){}
   std::unordered_map<std::shared_ptr<Entity>, std::shared_ptr<Entity>> entities;
   int updateDelay;
   double lastUpdatedTimestamp;
   bool visible;
};

class Scene : public IScene
{
   Float2 m_size, m_partSize;
   int m_pCount;

   std::vector<ScenePartition> m_partitions;
   std::vector<std::shared_ptr<IEntityManager> > m_entityManagers;

   void addEntity(std::shared_ptr<Entity> entity);
   void removeEntity(std::shared_ptr<Entity> entity);

public:
   Scene(Float2 size, int sqrtPartitionCount);

   Float2 getSize();


   //add an entitymanager that will get called when the scene is updated
   void registerEntityManager(std::shared_ptr<IEntityManager> em);

   //set the visibility rects within the scene for the next update
   void setVisibleRects(std::vector<Rectf> rects);

   //update scene entities
   void update();

   std::vector<std::shared_ptr<Entity>> getEntities();
   std::vector<std::shared_ptr<Entity>> getEntities(Rectf bounds);
};
