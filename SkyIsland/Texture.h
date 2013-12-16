#pragma once

#include "ITexture.h"
#include "StringTable.h"

class Texture : public ITexture
{
   Int2 m_size;
   int m_bitsPerPixel;
   unsigned int m_devilHandle, m_glHandle;
   bool m_isLoaded;
   InternString m_filename;
   std::vector<InternString> m_filters;

public:
   Texture(InternString filePath);
   Texture(InternString filePath, std::vector<std::string> filters);

   Int2 getSize();
   int getBitsPerPixel();
   unsigned int getGLHandle();
   InternString getFilePath();

   void acquire();
   void release();

   bool isLoaded();
};