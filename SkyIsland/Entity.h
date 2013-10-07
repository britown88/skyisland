#pragma once

#include "IComponent.h"
#include "IOCContainer.h"
#include "IntrusiveLinkedList.h"

class Entity
{
   IOCContainer components;

public:
   IntrusiveListHook hook;

   template<typename T>
   void addComponent(T *comp)
   {
      components.add<T>(comp);
   }

   template<typename T>
   T &getComponent()
   {
      return components.resolve<T>();
   }

   template<typename T>
   bool hasComponent()
   {
      return components.exists<T>();
   }

   template<typename T>
   void removeComponent()
   {
      components.remove<T>();
   }
};

typedef IntrusiveList<Entity, &Entity::hook> EntityList;