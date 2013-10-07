#include "DrawTriangle.h"

#include <GLFW/glfw3.h>

DrawTriangle::DrawTriangle(const std::vector<Vertex> & vertices, const std::vector<int> &faces):
   m_vertices(vertices), m_faces(faces)
{
}

void DrawTriangle::draw()
{
   glPushMatrix();
      glBegin(GL_TRIANGLES);
         for(int face : m_faces)
         {
            auto &v = m_vertices[face];
            glColor3f(v.r, v.g, v.b);
            glVertex3f(v.position.x, v.position.y, 0.0f);
         }
      glEnd();
   glPopMatrix();
}