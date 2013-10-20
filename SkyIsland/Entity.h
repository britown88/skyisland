#pragma once

#include "IComponent.h"
#include "IOCContainer.h"
#include "IntrusiveLinkedList.h"

class Entity
{
   IOCContainer components;

public:
   IntrusiveListHook hook;
   bool updated;

   Entity():updated(false){}

   template<typename T>
   void addComponent(std::shared_ptr<T> comp)
   {
      components.add<T>(std::move(comp));
   }

   template<typename T>
   boost::optional<T&> getComponent()
   {
      return components.resolve<T>();
   }

   template<typename T>
   void removeComponent()
   {
      components.remove<T>();
   }
};

typedef IntrusiveList<Entity, &Entity::hook> EntityList;