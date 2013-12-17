#include <GL\glew.h>

#include "FBO.h"

FBO::FBO()
{
   glGenFramebuffers(1, &m_fboHandle);
}

FBO::~FBO()
{
   glDeleteFramebuffers(1, &m_fboHandle);
}

void FBO::bind()
{
   glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fboHandle);
   glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_fboHandle, 0);
}

void FBO::render()
{
   glBindFramebuffer(GL_FRAMEBUFFER, 0); 
}