#include "SkeletalNodeComponent.h"
#include "SkeletalAnimationsManager.h"

void SkeletonComponent::changeAnim(InternString animName)
{
   if(playingAnimation != animName)
   {
      elapsedAnimTime = 0.0f;

      //play first frame
      if(auto anim = IOC.resolve<SkeletalAnimationsManager>()->getAnimation(animName))
         anim->updateEntity(elapsedAnimTime, *entity);

   }         

   playingAnimation = animName;

}