#pragma once

#include "IComponent.h"
#include "IOCContainer.h"
#include "IntrusiveLinkedList.h"
#include "IScene.h"

class Entity : public std::enable_shared_from_this<Entity>
{
   IOCContainer components;
   std::weak_ptr<IScene> m_scene;

public:
   IntrusiveListHook hook;
   bool updated, markedForDeletion;
   Rectf partitionBounds;

   std::shared_ptr<Entity> getptr() {return shared_from_this();}

   Entity():updated(false), markedForDeletion(false){}

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

   std::weak_ptr<IScene> getScene() {return m_scene;}

   void addToScene(std::weak_ptr<IScene> scene)
   {
      m_scene = std::move(scene);
      m_scene.lock()->addEntity(getptr());
   }
};

typedef IntrusiveList<Entity, &Entity::hook> EntityList;