#include "SpriteFactory.h"
#include "Animations.h"
#include <boost\filesystem.hpp>
#include "IntrusiveLinkedList.h"
#include "IOCContainer.h"
#include "StringTable.h"


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

void addFace(InternString name, InternString filepath, IAnimationStrategy &animStrat, std::shared_ptr<Sprite> sprite)
{
   auto face = std::unique_ptr<Face>(new Face()); 
   auto p = fs::current_path() / *filepath;
   face->name = name;
   auto st = IOC.resolve<StringTable>();

   int i = 0;
   char buf[256];
   while(true)
   {         
      sprintf(buf, "%02i.png", i++);
      std::string fname(buf);

      auto file = p / fname;
      if(fs::exists(file))
         face->textures.push_back(st->get(*filepath + "/" + fname));
      else
         break;
   }

   if(i > 1)
   {
      face->animation = animStrat.createAnimation(name, i - 1);
      sprite->addFace(name, std::move(face));
   }
}

std::shared_ptr<Sprite> SpriteFactory::buildSprite(InternString filepath, IAnimationStrategy &animStrat)
{
   std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>();
   auto st = IOC.resolve<StringTable>();

   if(endsWith(*filepath, ".png"))
   {
      //submitted a single png file
      auto face = std::unique_ptr<Face>(new Face());
      face->animation = animStrat.createAnimation(st->get(""), 1);
      face->name = st->get("");
      face->textures.push_back(filepath);
      sprite->addFace(st->get(""), std::move(face));
   }
   else
   {
      addFace(st->get(""), filepath, animStrat, sprite);           

      for(auto &file : iterateDirectory(fs::current_path() / *filepath))
      {
         if(fs::is_directory(file))
         {
            InternString fName = st->get(file.path().filename().string());
            addFace(fName, st->get(*filepath + "/" + *fName), animStrat, sprite); 
         }
      }
   }

   return sprite;

}