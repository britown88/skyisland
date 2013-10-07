#pragma once

#include "IScene.h"


class Scene : public IScene
{
   EntityList m_entities;
   Float2 m_size;

public:
   Scene(Float2 size);

   Float2 getSize();
   void addEntity(Entity &entity);

   EntityList *getEntities();
   EntityList *getEntities(const Rectf bounds);
};