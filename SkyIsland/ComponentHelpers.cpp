#include "ComponentHelpers.h"
#include "MeshComponent.h"

#include <vector>
namespace CompHelpers
{

void addRectangleMeshComponent(Entity &e, Rectf rect, Colorf color)
{
   addRectangleMeshComponent(e, rect, color, color, color, color);
}

void addRectangleMeshComponent(Entity &e, Rectf rect, Colorf c1, Colorf c2, Colorf c3, Colorf c4)
{
   std::vector<Vertex> vertices;
   std::vector<int> indices;

   vertices.push_back(Vertex(Float2(rect.left, rect.top), Float2(0, 1), c1));
   vertices.push_back(Vertex(Float2(rect.right, rect.top), Float2(1, 1), c2));
   vertices.push_back(Vertex(Float2(rect.right, rect.bottom), Float2(1, 0), c3));
   vertices.push_back(Vertex(Float2(rect.left, rect.bottom), Float2(0, 0), c4));

   indices.push_back(0);indices.push_back(1);indices.push_back(3);
   indices.push_back(1);indices.push_back(3);indices.push_back(2);

   e.addComponent<MeshComponent>(std::make_shared<MeshComponent>(vertices, indices));
}

}