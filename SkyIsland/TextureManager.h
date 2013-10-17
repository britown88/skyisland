#pragma once

#include "ITexture.h"
#include <unordered_map>
#include <string>
#include <memory>


class TextureManager
{
   TextureList m_loadedTextures;
   std::unordered_map<std::string, std::shared_ptr<ITexture>> m_textures;
   unsigned int m_textureMemory, m_usedMemory;//the limit of how much memory can be used for textures
public:
   static const int ID = 2706596565;
   TextureManager(unsigned int textureMemory);

   unsigned int getTexture(std::string filename);
};