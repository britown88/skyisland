#include "Renderables.h"
#include "IPositionComponent.h"
#include "GraphicComponents.h"
#include "MeshComponent.h"
#include "Transform.h"

#include "TextureManager.h"


class MeshRenderable : public IRenderable
{
   std::unique_ptr<VertexList> m_vertices;
   std::vector<int> m_faces;

   Transform m_transform;

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

         for(int i : mc.faces())
            m_faces.push_back(i);
      }

      m_transform = buildTransformation(entity);
   }

   void render(const IRenderer &renderer) const
   {
      renderer.drawTriangles(*m_vertices, m_faces, m_transform);
   }
};

std::unique_ptr<IRenderable> buildMeshRenderable(Entity &entity)
{
   return std::unique_ptr<IRenderable>(new MeshRenderable(entity));
}

