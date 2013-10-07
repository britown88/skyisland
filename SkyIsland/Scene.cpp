#include "Scene.h"

Scene::Scene(Float2 size):m_size(size){}

Float2 Scene::getSize(){return m_size;}
void Scene::addEntity(Entity &entity){m_entities.push_back(&entity);}

EntityList *Scene::getEntities()
{
   return &m_entities;

}
EntityList *Scene::getEntities(const Rectf bounds)
{
   return &m_entities;
}