#pragma once

#include <unordered_map>
#include "IOCContainer.h"
#include "Application.h"
#include "StringTable.h"
#include "SkeletalAnimation.h"
#include <memory>
#include <boost/optional.hpp>
#include "IEntityManager.h"


class SkeletalAnimationsManager
{
   std::unordered_map<InternString, std::unique_ptr<SkeletalAnimation>> m_animations;
public:
   const static int ID = 369131931;

   boost::optional<SkeletalAnimation&> getAnimation(InternString name)
   {
      if(m_animations.find(name) != m_animations.end())
         return *m_animations[name].get();

      return boost::none;
   }

   void addAnimation(std::string name, std::unique_ptr<SkeletalAnimation> anim)
   {
      m_animations.insert(std::make_pair(IOC.resolve<StringTable>()->get(name), std::move(anim)));
   }



};

class SkeletalAnimationsUpdateManager : public IEntityManager
{
   void updateOnScreenEntity(Entity &e)
   {
      if(auto skeleton = e.getComponent<SkeletonComponent>())
      {

         if(auto anim = IOC.resolve<SkeletalAnimationsManager>()->getAnimation(skeleton->playingAnimation))
         {
            auto app = IOC.resolve<Application>();
            auto t = app->dt() * (app->frameTime() / 1000.0f);
            skeleton->elapsedAnimTime += t * skeleton->dtMultiplier;
            anim->updateEntity(skeleton->elapsedAnimTime, *skeleton->entity);
         }
      }
   }
   void updateOffScreenEntity(Entity &e){updateOnScreenEntity(e);}
};

void buildSkeletalAnimations();
