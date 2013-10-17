#pragma once

#include "IScene.h"
#include <unordered_set>
#include <unordered_map>

struct PartitionedEntity;

struct ScenePartition
{
   ScenePartition():updateDelay(0), lastUpdatedTimestamp(0.0), visible(false){}
   std::unordered_map<std::shared_ptr<Entity>, PartitionedEntity> entities;
   int updateDelay;
   double lastUpdatedTimestamp;
   bool visible;
};

struct PartitionedEntity
{
   PartitionedEntity(){}
   PartitionedEntity(std::shared_ptr<Entity> entity, Rectf oldBounds):
      entity(entity), oldBounds(oldBounds){}
   Rectf oldBounds;
   std::shared_ptr<Entity> entity;
};

class Scene : public IScene
{
   Float2 m_size, m_partSize;
   int m_pCount;

   std::vector<ScenePartition> m_partitions;
   std::vector<std::shared_ptr<IEntityManager> > m_entityManagers;

public:
   Scene(Float2 size, int sqrtPartitionCount);

   Float2 getSize();
   void addEntity(std::shared_ptr<Entity> entity);

   //add an entitymanager that will get called when the scene is updated
   void registerEntityManager(std::shared_ptr<IEntityManager> em);

   //set the visibility rects within the scene for the next update
   void setVisibleRects(std::vector<Rectf> rects);

   //update scene entities
   void update();

   std::vector<std::shared_ptr<Entity>> getEntities();
   std::vector<std::shared_ptr<Entity>> getEntities(const Rectf bounds);
};