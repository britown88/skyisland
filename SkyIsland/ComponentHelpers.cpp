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
   auto vertices = createVertexList().with(VertexComponent::Position).with(VertexComponent::Color).build();
   std::vector<int> indices;

   vertices.addVertex()
      .with<VertexComponent::Position>(Float2(rect.left, rect.top))
      .with<VertexComponent::Color>(c1);

   vertices.addVertex()
      .with<VertexComponent::Position>(Float2(rect.right, rect.top))
      .with<VertexComponent::Color>(c2);

   vertices.addVertex()
      .with<VertexComponent::Position>(Float2(rect.right, rect.bottom))
      .with<VertexComponent::Color>(c3);

   vertices.addVertex()
      .with<VertexComponent::Position>(Float2(rect.left, rect.bottom))
      .with<VertexComponent::Color>(c4);

   indices.push_back(0);indices.push_back(1);indices.push_back(3);
   indices.push_back(1);indices.push_back(3);indices.push_back(2);

   e.addComponent<MeshComponent>(std::make_shared<MeshComponent>(vertices, indices));
}
}