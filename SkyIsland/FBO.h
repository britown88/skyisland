#pragma once

class FBO
{
   unsigned int m_fboHandle, m_texHandle;
public:
   FBO();
   ~FBO();

   void bind();
   void render();
};