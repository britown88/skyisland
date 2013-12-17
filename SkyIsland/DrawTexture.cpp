#include "DrawTexture.h"

#include <GLFW/glfw3.h>

#include "IOCContainer.h"
#include "TextureManager.h"

DrawTexture::DrawTexture(InternString texture, std::shared_ptr<VertexList> vertices, std::shared_ptr<std::vector<int>> faces, Transform transform):
   m_texture(std::move(texture)), m_vertices(std::move(vertices)), m_faces(std::move(faces)), m_transform(transform), m_gltexture(0)
{
   m_blendS = GL_SRC_ALPHA;
   m_blendD = GL_ONE_MINUS_SRC_ALPHA;
}


DrawTexture::DrawTexture(unsigned int texture, std::shared_ptr<VertexList> vertices, std::shared_ptr<std::vector<int>> faces, Transform transform):
   m_gltexture(texture), m_vertices(std::move(vertices)), m_faces(std::move(faces)), m_transform(transform)
{
   m_blendS = GL_SRC_ALPHA;
   m_blendD = GL_ONE_MINUS_SRC_ALPHA;
}

void DrawTexture::setBlendFunc(unsigned int sFactor, unsigned int dFactor)
{
   m_blendS = sFactor;
   m_blendD = dFactor;
}

void DrawTexture::draw()
{
   glPushMatrix();

      applyGLTransformation(m_transform);

      GLint tex = m_gltexture;
      if(tex == 0)
         tex = IOC.resolve<TextureManager>()->getTexture(m_texture);

      glBindTexture(GL_TEXTURE_2D, tex);

      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

      glEnable(GL_TEXTURE_2D);
      glEnable(GL_BLEND);
      glBlendFunc(m_blendS, m_blendD);

      drawGlVertices(*m_vertices, *m_faces);

      glDisable(GL_TEXTURE_2D);
      glDisable(GL_BLEND);
   glPopMatrix();
}