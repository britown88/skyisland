#pragma once

#include "ITexture.h"

class Texture : public ITexture
{
   Int2 m_size;
   int m_bitsPerPixel;
   unsigned int m_glHandle;
   bool m_isLoaded;
   std::string m_filename;

public:
   Texture(std::string filePath);

   Int2 getSize();
   int getBitsPerPixel();
   unsigned int getGLHandle();
   std::string getFilePath();

   void acquire();
   void release();

   bool isLoaded();
};