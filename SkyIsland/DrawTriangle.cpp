#include "DrawTriangle.h"

#include <GLFW/glfw3.h>

DrawTriangle::DrawTriangle(std::vector<Vertex> vertices, std::vector<int> faces, Transform transform):
   m_vertices(std::move(vertices)), m_faces(std::move(faces)), m_transform(transform)
{
}

void DrawTriangle::draw()
{
   glPushMatrix();

      applyGLTransformation(m_transform);

      glBegin(GL_TRIANGLES);
         for(int face : m_faces)
         {
            auto &v = m_vertices[face];
            glColor3f(v.color.r, v.color.g, v.color.b);
            glVertex3f(v.position.x, v.position.y, 0.0f);
         }
      glEnd();
   glPopMatrix();
}