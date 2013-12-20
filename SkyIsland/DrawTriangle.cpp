#include "DrawTriangle.h"

#include <GLFW/glfw3.h>

#include "IOCContainer.h"
#include "TextureManager.h"

DrawTriangle::DrawTriangle(std::shared_ptr<VertexList> vertices, std::shared_ptr<std::vector<int>> faces, Transform transform):
   m_vertices(std::move(vertices)), m_faces(std::move(faces)), m_transform(transform)
{
}

DrawTriangle::DrawTriangle(std::shared_ptr<VertexList> vertices, std::shared_ptr<std::vector<int>> faces, TransformList transform):
   m_vertices(std::move(vertices)), m_faces(std::move(faces)), m_transformList(transform)
{
}

void DrawTriangle::draw()
{
   glPushMatrix();
      if(m_transformList)
         applyGLTransformation(m_transformList);
      else
         applyGLTransformation(m_transform);
      drawGlVertices(*m_vertices, *m_faces);
   glPopMatrix();
}