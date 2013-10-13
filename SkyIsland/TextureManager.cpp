#include "TextureManager.h"
#include "Texture.h"

TextureManager::TextureManager(unsigned int textureMemory):
   m_textureMemory(textureMemory), m_usedMemory(0)
{
}

unsigned int TextureManager::getTexture(std::string filename)
{
   if(m_textures.find(filename) == m_textures.end())
      m_textures[filename] = std::make_shared<Texture>(filename);

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