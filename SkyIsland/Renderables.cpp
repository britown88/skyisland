#include "Renderables.h"
#include "PositionComponent.h"
#include "GraphicComponents.h"
#include "TextureComponent.h"
#include "MeshComponent.h"
#include "Transform.h"
#include "Application.h"

#include "TextureManager.h"


class MeshRenderable : public IRenderable
{
   std::shared_ptr<VertexList> m_vertices;
   std::shared_ptr<std::vector<int>> m_faces;

   Transform m_transform;
   std::string m_texture;

public:
   MeshRenderable(Entity &entity)
   {
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
         m_texture = "";
   }

   void render(const IRenderer &renderer) const
   {
      if(m_texture.size() > 0)
         renderer.drawTexture(m_texture, std::move(m_vertices), std::move(m_faces), m_transform);
      else
         renderer.drawTriangles(std::move(m_vertices), std::move(m_faces), m_transform);
   }
};

std::unique_ptr<IRenderable> buildMeshRenderable(Entity &entity)
{
   return std::unique_ptr<IRenderable>(new MeshRenderable(entity));
}

