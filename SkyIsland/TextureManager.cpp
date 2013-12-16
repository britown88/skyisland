#include "TextureManager.h"
#include "Texture.h"
#include "IOCContainer.h"
#include "StringTable.h"

#include <boost/algorithm/string.hpp>

TextureManager::TextureManager(unsigned int textureMemory):
   m_textureMemory(textureMemory), m_usedMemory(0)
{
}

unsigned int TextureManager::getTexture(InternString filename)
{
   auto st = IOC.resolve<StringTable>();

   if(m_textures.find(filename) == m_textures.end())
   {
      //textures never been loaded before, first check for a filter
      auto filterIndex = filename->find(':');

      if(filterIndex != std::string::npos && filterIndex < filename->length() - 1)
      {
         //using filters
         InternString filterlessFilename = st->get(filename->substr(0, filterIndex).c_str());
         std::string filters = filename->substr(filterIndex + 1);

         std::vector<std::string> filterList;
         boost::split(filterList, filters, boost::is_any_of(","));

         m_textures.insert(std::make_pair(filename, std::make_shared<Texture>(filterlessFilename, std::move(filterList))));
         
      }
      else
         m_textures.insert(std::make_pair(filename, std::make_shared<Texture>(filename)));

   }
      

   auto tex = m_textures[filename];

   if(tex->isLoaded())
   {
      tex->hook.unlink();
      m_loadedTextures.push_back(tex.get());
   }
   else
   {
      unsigned int size = (tex->getSize().x * tex->getSize().y * tex->getBitsPerPixel()) / 8;
      while(m_usedMemory + size > m_textureMemory)
      {
         auto &front = m_loadedTextures.front();
         m_usedMemory -= (front.getSize().x * front.getSize().y * front.getBitsPerPixel()) / 8;
         front.release();
         front.hook.unlink();
      }

      tex->acquire();
      m_usedMemory += size;
      m_loadedTextures.push_back(tex.get());

   }

   return tex->getGLHandle();
}