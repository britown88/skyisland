#include "Renderables.h"
#include "IPositionComponent.h"
#include "GraphicComponents.h"
#include "MeshComponent.h"
#include "Transform.h"


class MeshRenderable : public IRenderable
{
   std::vector<Vertex>  m_vertices;
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

         for(auto &v : mc.vertices())
         {
            float newX = v.position.x * size.x - center.x * size.x + pos.x;
            float newY = v.position.y * size.y - center.y * size.y + pos.y;
            m_vertices.push_back(Vertex(Float2(newX, newY), v.texCoords, v.color));
         }
            

         for(int i : mc.faces())
            m_faces.push_back(i);
      }

      m_transform = buildTransformation(entity);
   }

   void render(const IRenderer &renderer) const
   {
      renderer.drawTriangles(m_vertices, m_faces, m_transform);
   }
};

std::unique_ptr<IRenderable> buildMeshRenderable(Entity &entity)
{
   return std::unique_ptr<IRenderable>(new MeshRenderable(entity));
}