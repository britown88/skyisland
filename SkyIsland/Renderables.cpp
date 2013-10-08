#include "Renderables.h"
#include "IPositionComponent.h"
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

         for(auto &v : mc.vertices())
            m_vertices.push_back(Vertex(v.position + pos, v.r, v.g, v.b));

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