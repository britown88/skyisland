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

#include "DrawTexture.h"
#include <GLFW\glfw3.h>



class SkeletalRenderable : public IRenderable
{
   std::vector<SkeletalNode> nodes;
   std::shared_ptr<TextString> m_string;
   RenderLayer layer;
   ICamera::Pass pass;
   
public:

   SkeletalRenderable(Entity &entity)
   {
      pass = CompHelpers::getRenderPass(entity);
      layer = CompHelpers::getRenderLayer(entity);

      TransformList transforms = std::make_shared<std::vector<TransformPtr>>();
      auto t = std::make_shared<Transform>();
      *t = buildTransformation(entity);
      transforms->push_back(std::move(t));

      if(auto snc = entity.getComponent<SkeletalNodeComponent>())
         for(auto &connection : snc->connections)
         {
            if(auto gb = entity.getComponent<GraphicalBoundsComponent>())
            {
               auto t2 = std::make_shared<Transform>(connection.second.transform);
               t2->offset = t2->offset + (gb->size * connection.second.connectionPos);
               transforms->push_back(std::move(t2));

               addNode(*connection.second.entity, transforms);

               transforms->pop_back();
            }            
         }
            

   }

   void addNode(Entity &entity, TransformList transforms)
   {
      nodes.push_back(SkeletalNode());
      auto &node = nodes.back();

      if(auto pc = entity.getComponent<PositionComponent>())
      {
         if(auto mc = entity.getComponent<MeshComponent>())
         {
            node.m_vertices = mc->vertices;
            node.m_faces = mc->faces;
         }
      }

      if(auto tc = entity.getComponent<TextureComponent>())
      {
         node.m_texture = tc->texture;
         node.blendS = tc->blendS;
         node.blendD = tc->blendD;

         //change texCoords
         if(tc->size.x > 0.0f && tc->size.y > 0.0f)
         {
            if(auto gb = entity.getComponent<GraphicalBoundsComponent>())
            {
               auto texCoords = gb->size / tc->size;
               (*node.m_vertices)[0].get<VertexComponent::TextureCoordinate>()->y = texCoords.y;
               (*node.m_vertices)[1].get<VertexComponent::TextureCoordinate>()->x = texCoords.x;
               (*node.m_vertices)[1].get<VertexComponent::TextureCoordinate>()->y = texCoords.y;
               (*node.m_vertices)[2].get<VertexComponent::TextureCoordinate>()->x = texCoords.x;
            }

         }

         if(auto spr = entity.getComponent<SpriteComponent>())
         {
            node.m_texture = spr->sprite->getTexture(spr->face, spr->elapsedTime);
         }
      }         
      else
      {
         node.m_texture = IOC.resolve<StringTable>()->get("");
      }

      auto t = std::make_shared<Transform>();
      *t = buildTransformation(entity);      

      node.transforms = std::make_shared<std::vector<TransformPtr>>(*transforms);
      node.transforms->push_back(std::move(t));

      if(auto snc = entity.getComponent<SkeletalNodeComponent>())
         for(auto &connection : snc->connections)
         {
            if(auto gb = entity.getComponent<GraphicalBoundsComponent>())
            {
               auto t2 = std::make_shared<Transform>(connection.second.transform);
               t2->offset = t2->offset + (gb->size * connection.second.connectionPos);
               node.transforms->push_back(std::move(t2));

               addNode(*connection.second.entity, node.transforms);

               node.transforms->pop_back();
            }            
         }
         

   }


   void render(const IRenderer &renderer) const
   {
      for(auto &node : nodes)
      {
         if(node.m_texture->size() > 0)
         {
            auto DO = renderer.drawTexture(pass, layer, node.m_texture, std::move(node.m_vertices), std::move(node.m_faces), std::move(node.transforms));
            dynamic_cast<DrawTexture*>(DO.get())->setBlendFunc(node.blendS, node.blendD);
         }        
         //else
            //renderer.drawTriangles(pass, layer, std::move(node.m_vertices), std::move(node.m_faces), m_transform);
      }      
   }
};

std::unique_ptr<IRenderable> buildSkeletalRenderable(Entity &entity)
{
   return std::unique_ptr<IRenderable>(new SkeletalRenderable(entity));
}

class TextRenderable : public IRenderable
{
   std::shared_ptr<TextString> m_string;
   Transform m_transform;
   RenderLayer layer;
   ICamera::Pass pass;

public:
   TextRenderable(Entity &entity)
   {
      pass = CompHelpers::getRenderPass(entity);
      layer = CompHelpers::getRenderLayer(entity);

      if(auto tc = entity.getComponent<TextComponent>())
      {
         m_transform = buildTransformation(entity);
         m_string = std::make_shared<TextString>(tc->drawPos, tc->str, tc->color, tc->font);
      }

   }
   void render(const IRenderer &renderer) const
   {
      renderer.drawText(pass, layer, m_string, m_transform);
   }
};

std::unique_ptr<IRenderable> buildTextRenderable(Entity &entity)
{
   return std::unique_ptr<IRenderable>(new TextRenderable(entity));
}



class MeshRenderable : public IRenderable
{
   std::shared_ptr<VertexList> m_vertices;
   std::shared_ptr<std::vector<int>> m_faces;

   Transform m_transform;
   InternString m_texture;
   RenderLayer layer;
   ICamera::Pass pass;
   unsigned int blendS, blendD;

public:
   MeshRenderable(Entity &entity)
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

         //change texCoords
         if(tc->size.x > 0.0f && tc->size.y > 0.0f)
         {
            if(auto gb = entity.getComponent<GraphicalBoundsComponent>())
            {
               auto texCoords = gb->size / tc->size;
               (*m_vertices)[0].get<VertexComponent::TextureCoordinate>()->y = texCoords.y;
               (*m_vertices)[1].get<VertexComponent::TextureCoordinate>()->x = texCoords.x;
               (*m_vertices)[1].get<VertexComponent::TextureCoordinate>()->y = texCoords.y;
               (*m_vertices)[2].get<VertexComponent::TextureCoordinate>()->x = texCoords.x;
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
         
   }

   void render(const IRenderer &renderer) const
   {
      if(m_texture->size() > 0)
      {
         auto DO = renderer.drawTexture(pass, layer, m_texture, std::move(m_vertices), std::move(m_faces), m_transform);
         dynamic_cast<DrawTexture*>(DO.get())->setBlendFunc(blendS, blendD);
      }        
      else
         renderer.drawTriangles(pass, layer, std::move(m_vertices), std::move(m_faces), m_transform);
   }
};

std::unique_ptr<IRenderable> buildMeshRenderable(Entity &entity)
{
   return std::unique_ptr<IRenderable>(new MeshRenderable(entity));
}

