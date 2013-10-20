#pragma once

#include "IAnimation.h"
#include "StringTable.h"
#include "IOCContainer.h"
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>

struct Face
{
   InternString name;
   std::vector<InternString> textures;
   std::unique_ptr<IAnimation<int>> animation;
};


class Sprite
{
   std::unordered_map<InternString, std::unique_ptr<Face>> m_faces;
public:
   void addFace(InternString name, std::unique_ptr<Face> face)
   {
      m_faces[name] = std::move(face);
   }

   Face *getFace(InternString name)
   {
      return m_faces[name].get();
   }

   InternString getTexture(InternString face, float time)
   {
      if(m_faces.find(face) != m_faces.end())
         return m_faces[face]->textures[m_faces[face]->animation->get(time)];
      else
         return IOC.resolve<StringTable>()->get("");
   }
};