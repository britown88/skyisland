#include "SpriteFactory.h"

std::shared_ptr<Sprite> SpriteFactory::buildSprite(std::string filepath, float speed)
{
   if(m_createdSprites.find(filepath) != m_createdSprites.end())
      return m_createdSprites[filepath];

   std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>();

   //directory bullshit
}