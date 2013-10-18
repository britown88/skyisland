#pragma once

#include "IAnimation.h"
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>

struct Face
{
   std::string name;
   std::vector<std::string> textures;
   std::unique_ptr<IAnimation<int>> animation;
};


class Sprite
{
   std::unordered_map<std::string, std::unique_ptr<Face>> m_faces;
public:
   void addFace(std::string name, std::unique_ptr<Face> face)
   {
      m_faces[name] = std::move(face);
   }

   Face *getFace(std::string name)
   {
      return m_faces[name].get();
   }

   std::string getTexture(std::string face, float time)
   {
      if(m_faces.find(face) != m_faces.end())
         return m_faces[face]->textures[m_faces[face]->animation->get(time)];
      else
         return "";
   }
};