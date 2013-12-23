#include "SpriteFactory.h"
#include "Animations.h"
#include <boost/filesystem.hpp>
#include "IntrusiveLinkedList.h"
#include "IOCContainer.h"
#include "StringTable.h"
#include <boost/algorithm/string.hpp>

namespace fs = boost::filesystem;

std::pair<fs::directory_iterator, fs::directory_iterator> iterateDirectory(fs::path p)
{
   return std::make_pair(fs::directory_iterator(p), fs::directory_iterator());
}

void addFace(InternString facename, FSNode &faceNode, IAnimationStrategy &animStrat, std::shared_ptr<Sprite> sprite, std::string &filters)
{
   auto face = std::unique_ptr<Face>(new Face());
   auto st = IOC.resolve<StringTable>();

   int i = 0;
   char buf[256];
   while(i < 100)
   {
      sprintf(buf, "%02i.png", i++);
      InternString fname = st->get(std::string(buf));

      if(faceNode.children.find(fname) != faceNode.children.end())
      {
         if(filters.length() > 0)
            face->textures.push_back(st->get(*faceNode[fname].path + ":" + filters));
         else
            face->textures.push_back(faceNode[fname].path);

      }

      else
         break;
   }

   if(i > 1)
   {
      face->animation = animStrat.createAnimation(facename, i - 1);
      sprite->addFace(facename, std::move(face));
   }
}

void iterateAssetDirectory(std::string assetDir, FSNode &node)
{
   auto st = IOC.resolve<StringTable>();

   for(auto &file : iterateDirectory(fs::current_path() / assetDir))
   {
      InternString fName = st->get(file.path().filename().string());
      InternString newDir = st->get(assetDir + "/" + *fName);
      node.children.insert(std::make_pair(fName, FSNode(newDir)));

      if(fs::is_directory(file))
         iterateAssetDirectory(*newDir, node[fName]);
   }
}


void SpriteFactory::buildAssetIndex(std::string assetRoot)
{
   auto st = IOC.resolve<StringTable>();

   m_assetIndex = FSNode(st->get(assetRoot));

   iterateAssetDirectory(assetRoot, m_assetIndex);

}

std::shared_ptr<Sprite> SpriteFactory::buildSprite(InternString filepath, IAnimationStrategy *animStrat)
{
   std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>();
   auto st = IOC.resolve<StringTable>();

   auto filterIndex = filepath->find(':');
   std::string filters = "";

   if(filterIndex != std::string::npos && filterIndex < filepath->length() - 1)
   {
      //using filters
      filters = filepath->substr(filterIndex + 1);
      filepath = st->get(filepath->substr(0, filterIndex).c_str());
   }

   std::vector<std::string> pathParts;
   boost::split(pathParts, *filepath, boost::is_any_of("/"));

   FSNode *node = &m_assetIndex;

   //iterate to the right node
   if(st->get(pathParts[0]) == node->path)
   {
      for(int i = 1; i < pathParts.size(); ++i)
      {
         auto part = st->get(pathParts[i]);
         if(node->children.find(part) != node->children.end())
         {
            node = &node->children[part];
         }
         else
            return sprite;

      }
   }
   else
      return sprite;

   //now we have a base node, iterate over faces
   if(node->children.empty())
   {
      //submitted a childrenless node
      auto face = std::unique_ptr<Face>(new Face());
      face->animation = animStrat->createAnimation(st->get(""), 1);
      face->name = st->get("");
      face->textures.push_back(node->path);
      sprite->addFace(st->get(""), std::move(face));
   }
   else
   {
      addFace(st->get(""), *node, *animStrat, sprite, filters);
      for(auto &child : node->children)
         addFace(child.first, child.second, *animStrat, sprite, filters);
   }

   return sprite;

}
