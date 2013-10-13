#include "DrawTriangle.h"

#include <GLFW/glfw3.h>

#include "IOCContainer.h"
#include "TextureManager.h"

DrawTriangle::DrawTriangle(std::vector<Vertex> vertices, std::vector<int> faces, Transform transform):
   m_vertices(std::move(vertices)), m_faces(std::move(faces)), m_transform(transform)
{
}

void DrawTriangle::draw()
{
   glPushMatrix();

      applyGLTransformation(m_transform);

      GLint handle = IOC.resolve<TextureManager>().getTexture("assets/test.png");

      glBindTexture(GL_TEXTURE_2D, handle);

      glEnable(GL_TEXTURE_2D);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glBegin(GL_TRIANGLES);
         for(int face : m_faces)
         {
            auto &v = m_vertices[face];
            //glColor3f(v.color.r, v.color.g, v.color.b);
            glTexCoord2f(v.texCoords.x, v.texCoords.y);
            glVertex3f(v.position.x, v.position.y, 0.0f);
            
         }
      glEnd();
      glDisable(GL_TEXTURE_2D);
      glDisable(GL_BLEND);
   glPopMatrix();
}