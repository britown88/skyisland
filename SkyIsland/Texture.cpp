#include "Texture.h"
#include <GLFW/glfw3.h>
#include "IL/ilut.h"

#include "IOCContainer.h"
#include "StringTable.h"
#include "ColorFilter.h"


Texture::Texture(InternString filePath):
   m_filename(filePath), m_isLoaded(false),
   m_bitsPerPixel(0), m_size(Int2()), m_devilHandle(0), m_glHandle(0)
{
}

Texture::Texture(InternString filePath, std::vector<std::string> filters):
   m_filename(filePath), m_isLoaded(false),
   m_bitsPerPixel(0), m_size(Int2()), m_devilHandle(0), m_glHandle(0)
{
   auto st = IOC.resolve<StringTable>();
   for(auto &str : filters)
      m_filters.push_back(st->get(str.c_str()));
}

Int2 Texture::getSize(){return m_size;}
int Texture::getBitsPerPixel(){return m_bitsPerPixel;}
unsigned int Texture::getGLHandle(){return m_glHandle;}
InternString Texture::getFilePath(){return m_filename;}
bool Texture::isLoaded(){return m_isLoaded;}

void Texture::acquire()
{
   ilGenImages(1, &m_devilHandle);
   ilBindImage(m_devilHandle);
   ilLoadImage((char*)m_filename->c_str());


   //m_glHandle = ilutGLLoadImage((char*)m_filename->c_str());
   m_size.x = ilGetInteger(IL_IMAGE_WIDTH);
   m_size.y = ilGetInteger(IL_IMAGE_WIDTH);
   m_bitsPerPixel = ilGetInteger(IL_IMAGE_BITS_PER_PIXEL);

   if(!m_filters.empty())
   {
      auto imageData = ilGetData();
      auto &managerFilters = IOC.resolve<ColorFilterManager>()->filters;
      for(auto &filterName : m_filters)
      {
         //if filter name is valid
         if(managerFilters.find(filterName) != managerFilters.end())
         {
            auto filter = managerFilters[filterName];
            for(int i = 0; i < m_size.x * m_size.y; ++i)
            {
               Color255 c(imageData[i*4], imageData[i*4+1], imageData[i*4+2], imageData[i*4+3]);
               if(filter.table.find(c) != filter.table.end())
               {
                  auto &c2 = filter.table[c];
                  imageData[i*4] = c2.r;
                  imageData[i*4+1] = c2.g;
                  imageData[i*4+2] = c2.b;
                  imageData[i*4+3] = c2.a;
               }
            }
         }
      }
   }

   m_glHandle = ilutGLBindTexImage();
   m_isLoaded = true;
}

void Texture::release()
{
   ilDeleteImages(1, &m_devilHandle);
   //glDeleteTextures(1, &m_glHandle);
   m_isLoaded = false;
}

