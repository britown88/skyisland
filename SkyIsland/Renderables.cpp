#include "Renderables.h"
#include "PositionComponent.h"
#include "GraphicComponents.h"
#include "TextureComponent.h"
#include "SkeletalNodeComponent.h"
#include "TextComponent.h"
#include "MeshComponent.h"
#include "Transform.h"
#include "Application.h"
#include "ComponentHelpers.h"
#include "Vertex.h"

#include "TextureManager.h"
#include "RenderManager.h"

#include "DrawTexture.h"
#include "SeanSort.h"
#include <GLFW\glfw3.h>



class SkeletalRenderable : public IRenderable
{
   std::vector<std::shared_ptr<SkeletalNode>> nodes;
   std::shared_ptr<TextString> m_string;
   RenderLayer layer;
   ICamera::Pass pass;
   bool nothingRendered;
   
public:

   SkeletalRenderable(Entity &entity, TransformList transforms, ComponentDrawLayer drawLayer)
   {
      //exit if we're not going to be rendering anything
      nothingRendered = !hasDrawableConnections(entity, drawLayer);

      if(nothingRendered)
         return;

      pass = CompHelpers::getRenderPass(entity);
      layer = CompHelpers::getRenderLayer(entity);

      if(!transforms)
         transforms = std::make_shared<std::vector<TransformPtr>>();      

      if(auto snc = entity.getComponent<SkeletalNodeComponent>())
      {
         auto t = std::make_shared<Transform>();
         *t = buildTransformation(entity);
         transforms->push_back(std::move(t));

         for(auto &connection : snc->connections)
         {
            if(connection.second->entity)
            if(drawLayer == ComponentDrawLayer::Both ||
               connection.second->layer >= 0 && drawLayer == ComponentDrawLayer::Foreground ||
               connection.second->layer < 0 && drawLayer == ComponentDrawLayer::Background) 
            if(auto gb = entity.getComponent<GraphicalBoundsComponent>())
            {
               auto t2 = std::make_shared<Transform>(connection.second->transform);
               t2->offset = t2->offset + (gb->size * connection.second->connectionPos);
               transforms->push_back(std::move(t2));

               auto node = std::make_shared<SkeletalNode>();
               node->transforms = std::make_shared<std::vector<TransformPtr>>(*transforms);
               node->entity = connection.second->entity;
               node->layer = connection.second->layer;
               nodes.push_back(std::move(node));

               transforms->pop_back();
               
            }            
         } 
      }
         

      //if drawing background
      if(drawLayer == ComponentDrawLayer::Background)
         transforms->pop_back();

      //sort nodes based on layerering
      nodes = seanSort(std::move(nodes), 
         [&](const std::shared_ptr<SkeletalNode> &n1, const std::shared_ptr<SkeletalNode> &n2)->bool
      { 
         if(n1->layer < n2->layer) 
            return true;
         if(n1->layer > n2->layer) 
            return false;
      
         return n1 < n2;
      });
            

   }   

   bool hasDrawableConnections(Entity &entity, ComponentDrawLayer drawLayer)
   {
      if(auto snc = entity.getComponent<SkeletalNodeComponent>())
      {
         for(auto &connection : snc->connections)
         {
            if(connection.second->entity)
            if(drawLayer == ComponentDrawLayer::Both ||
               connection.second->layer >= 0 && drawLayer == ComponentDrawLayer::Foreground ||
               connection.second->layer < 0 && drawLayer == ComponentDrawLayer::Background) 
            if(entity.getComponent<GraphicalBoundsComponent>())
            {
               return true;
            }
         }
      }

      return false;
   }

   //returns whether or not something was rendered
   bool render(const IRenderer &renderer) const
   {
      if(nothingRendered)
         return false;

      auto rManager = IOC.resolve<RenderManager>();
      for(auto &node : nodes)
         if(auto e = node->entity.lock())
            rManager->renderEntity(*e, node->transforms);

      return true;
          
   }
};

std::unique_ptr<IRenderable> buildSkeletalRenderable(Entity &entity, TransformList transforms, ComponentDrawLayer drawLayer)
{
   return std::unique_ptr<IRenderable>(new SkeletalRenderable(entity, transforms, drawLayer));
}


class TextRenderable : public IRenderable
{
   std::shared_ptr<TextString> m_string;
   Transform m_transform;
   TransformList m_tList;
   RenderLayer layer;
   ICamera::Pass pass;

public:
   TextRenderable(Entity &entity, TransformList transforms)
   {
      pass = CompHelpers::getRenderPass(entity);
      layer = CompHelpers::getRenderLayer(entity);

      if(auto tc = entity.getComponent<TextComponent>())
      {
         m_transform = buildTransformation(entity);
         if(transforms)
         {
            //copy list and add to it
            m_tList = std::make_shared<std::vector<TransformPtr>>(*transforms);
            m_tList->push_back(std::make_shared<Transform>(m_transform));
         }
         m_string = std::make_shared<TextString>(tc->drawPos, tc->str, tc->color, tc->font);
      }

   }
   //returns whether or not something was rendered
   bool render(const IRenderer &renderer) const
   {
      if(m_tList)
         renderer.drawText(pass, layer, m_string, m_tList);
      else
         renderer.drawText(pass, layer, m_string, m_transform);
      return true;
   }
};

std::unique_ptr<IRenderable> buildTextRenderable(Entity &entity, TransformList transforms)
{
   return std::unique_ptr<IRenderable>(new TextRenderable(entity, transforms));
}



class MeshRenderable : public IRenderable
{
   std::shared_ptr<VertexList> m_vertices;
   std::shared_ptr<std::vector<int>> m_faces;

   Transform m_transform;
   TransformList m_tList;
   InternString m_texture;
   RenderLayer layer;
   ICamera::Pass pass;
   unsigned int blendS, blendD;

public:
   MeshRenderable(Entity &entity, TransformList transforms)
   {
      pass = CompHelpers::getRenderPass(entity);
      layer = CompHelpers::getRenderLayer(entity);

      if(auto pc = entity.getComponent<PositionComponent>())
      {
         if(auto mc = entity.getComponent<MeshComponent>())
         {
            m_vertices = mc->vertices;
            m_faces = mc->faces;
         }
      }

      if(auto tc = entity.getComponent<TextureComponent>())
      {
         m_texture = tc->texture;
         blendS = tc->blendS;
         blendD = tc->blendD;

         //change texCoords, copy vertexlist to new
         if(tc->yFlipped || tc->xFlipped || (tc->size.x > 0.0f && tc->size.y > 0.0f))
            m_vertices = std::make_shared<VertexList>(*m_vertices);

         if(tc->yFlipped)
         {
            (*m_vertices)[0].get<VertexComponent::TextureCoordinate>()->y = 0.0f;
            (*m_vertices)[1].get<VertexComponent::TextureCoordinate>()->y = 0.0f;
            (*m_vertices)[2].get<VertexComponent::TextureCoordinate>()->y = 1.0f;
            (*m_vertices)[3].get<VertexComponent::TextureCoordinate>()->y = 1.0f;
         }

         if(tc->xFlipped)
         {
            (*m_vertices)[0].get<VertexComponent::TextureCoordinate>()->x = 1.0f;
            (*m_vertices)[1].get<VertexComponent::TextureCoordinate>()->x = 0.0f;
            (*m_vertices)[2].get<VertexComponent::TextureCoordinate>()->x = 0.0f;
            (*m_vertices)[3].get<VertexComponent::TextureCoordinate>()->x = 1.0f;
         }

         if(tc->size.x > 0.0f && tc->size.y > 0.0f)
         {
            if(auto gb = entity.getComponent<GraphicalBoundsComponent>())
            {
               auto texCoords = gb->size / tc->size;

               *(*m_vertices)[0].get<VertexComponent::TextureCoordinate>() *= texCoords;
               *(*m_vertices)[1].get<VertexComponent::TextureCoordinate>() *= texCoords;
               *(*m_vertices)[2].get<VertexComponent::TextureCoordinate>() *= texCoords;
               *(*m_vertices)[3].get<VertexComponent::TextureCoordinate>() *= texCoords;

            }
         }

         if(auto spr = entity.getComponent<SpriteComponent>())
         {
            m_texture = spr->sprite->getTexture(spr->face, spr->elapsedTime);
         }
      }         
      else
      {
         m_texture = IOC.resolve<StringTable>()->get("");
      }

      m_transform = buildTransformation(entity);
      if(transforms)
      {
         //copy list and add to it
         m_tList = std::make_shared<std::vector<TransformPtr>>(*transforms);
         m_tList->push_back(std::make_shared<Transform>(m_transform));
      }
         
   }

   //returns whether or not something was rendered
   bool render(const IRenderer &renderer) const
   {
      if(m_texture->size() > 0)
      {
         std::shared_ptr<IDrawObject> DO;
         DO = m_tList ? 
            renderer.drawTexture(pass, layer, m_texture, std::move(m_vertices), std::move(m_faces), m_tList) : 
            renderer.drawTexture(pass, layer, m_texture, std::move(m_vertices), std::move(m_faces), m_transform);
         dynamic_cast<DrawTexture*>(DO.get())->setBlendFunc(blendS, blendD);
      }        
      else
         if(m_tList)
            renderer.drawTriangles(pass, layer, std::move(m_vertices), std::move(m_faces), m_tList);
         else
            renderer.drawTriangles(pass, layer, std::move(m_vertices), std::move(m_faces), m_transform);

      return true;
   }
};

std::unique_ptr<IRenderable> buildMeshRenderable(Entity &entity, TransformList transforms)
{
   return std::unique_ptr<IRenderable>(new MeshRenderable(entity, transforms));
}

