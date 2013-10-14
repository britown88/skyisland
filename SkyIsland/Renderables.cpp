#include "Renderables.h"
#include "IPositionComponent.h"
#include "GraphicComponents.h"
#include "TextureComponent.h"
#include "MeshComponent.h"
#include "Transform.h"
#include "Application.h"

#include "TextureManager.h"


class MeshRenderable : public IRenderable
{
   std::unique_ptr<VertexList> m_vertices;
   std::vector<int> m_faces;

   Transform m_transform;
   std::string m_texture;

public:

   MeshRenderable(Entity &entity)
   {
      if(entity.hasComponent<IPositionComponent>())
      {
         auto &mc = entity.getComponent<MeshComponent>();
         auto &pc = entity.getComponent<IPositionComponent>();
         Float2 pos = pc.getPosition();
         Float2 size = Float2(1.0f, 1.0f);
         Float2 center = Float2();

         if(entity.hasComponent<GraphicalBoundsComponent>())
         {
            auto &gb = entity.getComponent<GraphicalBoundsComponent>();
            size = gb.size;
            center = gb.center;
         }

         m_vertices.reset(new VertexList(mc.vertices()));

         for(auto iter = m_vertices->iterate(); iter.hasMore(); iter.moveNext())
         {
            auto &vpos = *iter.get<VertexComponent::Position>();
            
            vpos.x = vpos.x * size.x - center.x * size.x + pos.x;
            vpos.y = vpos.y * size.y - center.y * size.y + pos.y;
         }

         m_faces = mc.faces();
      }

      m_transform = buildTransformation(entity);

      if(entity.hasComponent<TextureComponent>())
      {
         m_texture = entity.getComponent<TextureComponent>().texture;

         if(entity.hasComponent<SpriteComponent>())
         {
            auto &spr = entity.getComponent<SpriteComponent>();
            m_texture = spr.sprite->getTexture(spr.face, IOC.resolve<Application>().getTime() - spr.startTime);
         }
      }         
      else
         m_texture = "";
   }

   void render(const IRenderer &renderer) const
   {
      if(m_texture.size() > 0)
         renderer.drawTexture(m_texture, std::move(*m_vertices), std::move(m_faces), m_transform);
      else
         renderer.drawTriangles(std::move(*m_vertices), std::move(m_faces), m_transform);
   }
};

std::unique_ptr<IRenderable> buildMeshRenderable(Entity &entity)
{
   return std::unique_ptr<IRenderable>(new MeshRenderable(entity));
}

