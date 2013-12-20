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
#include <GLFW\glfw3.h>



class SkeletalRenderable : public IRenderable
{
   std::vector<std::shared_ptr<SkeletalNode>> nodes;
   std::shared_ptr<TextString> m_string;
   RenderLayer layer;
   ICamera::Pass pass;
   
public:

   SkeletalRenderable(Entity &entity, TransformList transforms)
   {
      pass = CompHelpers::getRenderPass(entity);
      layer = CompHelpers::getRenderLayer(entity);

      if(!transforms)
         transforms = std::make_shared<std::vector<TransformPtr>>();

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

               auto node = std::make_shared<SkeletalNode>();
               node->transforms = std::make_shared<std::vector<TransformPtr>>(*transforms);
               node->entity = connection.second.entity;
               nodes.push_back(std::move(node));

               transforms->pop_back();
            }            
         }     
            

   }   


   void render(const IRenderer &renderer) const
   {
      auto rManager = IOC.resolve<RenderManager>();
      for(auto &node : nodes)
         if(auto e = node->entity.lock())
            rManager->renderEntity(*e, node->transforms);
          
   }
};

std::unique_ptr<IRenderable> buildSkeletalRenderable(Entity &entity, TransformList transforms)
{
   return std::unique_ptr<IRenderable>(new SkeletalRenderable(entity, transforms));
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
   void render(const IRenderer &renderer) const
   {
      if(m_tList)
         renderer.drawText(pass, layer, m_string, m_tList);
      else
         renderer.drawText(pass, layer, m_string, m_transform);
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
      if(transforms)
      {
         //copy list and add to it
         m_tList = std::make_shared<std::vector<TransformPtr>>(*transforms);
         m_tList->push_back(std::make_shared<Transform>(m_transform));
      }
         
   }

   void render(const IRenderer &renderer) const
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
   }
};

std::unique_ptr<IRenderable> buildMeshRenderable(Entity &entity, TransformList transforms)
{
   return std::unique_ptr<IRenderable>(new MeshRenderable(entity, transforms));
}

