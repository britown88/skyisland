#include "DrawTriangle.h"

#include <GLFW/glfw3.h>

#include "IOCContainer.h"
#include "TextureManager.h"

DrawTriangle::DrawTriangle(VertexList vertices, std::vector<int> faces, Transform transform):
   m_vertices(std::move(vertices)), m_faces(std::move(faces)), m_transform(transform)
{
}

void DrawTriangle::draw()
{
   glPushMatrix();
      applyGLTransformation(m_transform);
      drawGlVertices(m_vertices, m_faces);
   glPopMatrix();
}