#include "Renderables.h"
#include "PositionComponent.h"
#include "GraphicComponents.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "MeshComponent.h"
#include "Transform.h"
#include "Application.h"
#include "ComponentHelpers.h"

#include "TextureManager.h"

class TextRenderable : public IRenderable
{
   std::shared_ptr<TextString> m_string;
   Transform m_transform;
   RenderLayer layer;

public:
   TextRenderable(Entity &entity)
   {
      if(auto tc = entity.getComponent<TextComponent>())
      {
         m_transform = buildTransformation(entity);
         m_string = std::make_shared<TextString>(tc->drawPos, tc->str, tc->color, tc->font);
      }

      layer = CompHelpers::getRenderLayer(entity);
      

   }
   void render(const IRenderer &renderer) const
   {
      renderer.drawText(layer, m_string, m_transform);
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

public:
   MeshRenderable(Entity &entity)
   {
      layer = CompHelpers::getRenderLayer(entity);

      if(auto pc = entity.getComponent<PositionComponent>())
      {
         if(auto mc = entity.getComponent<MeshComponent>())
         {
            m_vertices = mc->vertices;
            m_faces = mc->faces;
         }
      }

      m_transform = buildTransformation(entity);

      if(auto tc = entity.getComponent<TextureComponent>())
      {
         m_texture = tc->texture;

         if(auto spr = entity.getComponent<SpriteComponent>())
         {
            m_texture = spr->sprite->getTexture(spr->face, spr->elapsedTime);
         }
      }         
      else
      {
         m_texture = IOC.resolve<StringTable>()->get("");
      }
         
   }

   void render(const IRenderer &renderer) const
   {
      if(m_texture->size() > 0)
         renderer.drawTexture(layer, m_texture, std::move(m_vertices), std::move(m_faces), m_transform);
      else
         renderer.drawTriangles(layer, std::move(m_vertices), std::move(m_faces), m_transform);
   }
};

std::unique_ptr<IRenderable> buildMeshRenderable(Entity &entity)
{
   return std::unique_ptr<IRenderable>(new MeshRenderable(entity));
}

