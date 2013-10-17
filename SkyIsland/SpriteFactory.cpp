#include "SpriteFactory.h"
#include "Animations.h"
#include <boost\filesystem.hpp>
#include "IntrusiveLinkedList.h"


bool endsWith(std::string str, std::string ending)
{
   if(str.length() >= ending.length())
      return str.compare(str.length() - ending.length(), ending.length(), ending) == 0;

   return false;   
}

namespace fs = boost::filesystem;

std::pair<fs::directory_iterator, fs::directory_iterator> iterateDirectory(fs::path p)
{
   return std::make_pair(fs::directory_iterator(p), fs::directory_iterator());
}

void addFace(std::string name, std::string filepath, float speed, std::shared_ptr<Sprite> sprite)
{
   auto face = std::unique_ptr<Face>(new Face()); 
   auto p = fs::current_path() / filepath;
   face->name = name;

   int i = 0;
   char buf[256];
   while(true)
   {         
      sprintf(buf, "%02i.png", i++);
      std::string fname(buf);

      auto file = p / fname;
      if(fs::exists(file))
         face->textures.push_back(filepath + "/" + fname);
      else
         break;
   }

   if(i > 1)
   {
      face->animation = std::unique_ptr<BasicAnimation>(new BasicAnimation(i - 1, speed));
      sprite->addFace(name, std::move(face));
   }
}

std::shared_ptr<Sprite> SpriteFactory::buildSprite(std::string filepath, float speed)
{
   //if(m_createdSprites.find(filepath) != m_createdSprites.end())
      //return m_createdSprites[filepath];

   std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>();

   if(endsWith(filepath, ".png"))
   {
      //submitted a single png file
      auto face = std::unique_ptr<Face>(new Face());
      face->animation = std::unique_ptr<BasicAnimation>(new BasicAnimation(1, speed));
      face->name = "";
      face->textures.push_back(filepath);
      sprite->addFace("", std::move(face));
   }
   else
   {
      addFace("", filepath, speed, sprite);           

      for(auto &file : iterateDirectory(fs::current_path() / filepath))
      {
         if(fs::is_directory(file))
         {
            std::string fName = file.path().filename().string();
            addFace(fName, filepath + "/" + fName, speed, sprite); 
         }
      }
   }

   return sprite;

}