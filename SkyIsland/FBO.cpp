#include <GL\glew.h>

#include "FBO.h"

FBO::FBO(Rectf bounds):m_bounds(Rectf(bounds))
{   
   glGenFramebuffers(1, &m_fboHandle);

   int pixelCount = m_bounds.width() * m_bounds.height();
   unsigned char *pixels = (unsigned char*)calloc(pixelCount * 4, sizeof(unsigned char));

   glGenTextures(1, &m_texHandle);
   glBindTexture(GL_TEXTURE_2D, m_texHandle);
   glTexImage2D(
      GL_TEXTURE_2D, 0, GL_RGBA, 
      m_bounds.width(), m_bounds.height(), 
      0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

   glBindTexture(GL_TEXTURE_2D, 0);

   free(pixels);
}

FBO::~FBO()
{
   glDeleteTextures(1, &m_texHandle);
   glDeleteFramebuffers(1, &m_fboHandle);
}

void FBO::bind()
{
   glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fboHandle);
   glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texHandle, 0);
}

void FBO::render()
{
   glBindFramebuffer(GL_FRAMEBUFFER, 0); 
}