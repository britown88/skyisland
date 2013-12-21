#include "SkeletalAnimationsManager.h"

void buildSkeletalAnimations()
{
   auto manager = IOC.resolve<SkeletalAnimationsManager>();

   auto rotPointTest = std::unique_ptr<SkeletalAnimation>(new SkeletalAnimation(1000));
   rotPointTest->setLooping(true);

   rotPointTest->addFrame("torso", 500).setRotation(45.0f, "leftleg");
   rotPointTest->addFrame("torso", 1000).setRotation(0.0f, "leftleg");
   rotPointTest->addFrame("torso/leftleg", 500).setRotation(-45.0f, Float2(0.5f, 0.0f));
   rotPointTest->addFrame("torso/leftleg", 1000).setRotation(0.0f, Float2(0.5f, 0.0f));
   manager->addAnimation("rotPointTest", std::move(rotPointTest));

   auto dance = std::unique_ptr<SkeletalAnimation>(new SkeletalAnimation(1000));
   dance->setLooping(true);

   dance->addFrame("torso", 250).setRotation(25.0f, "leftleg");
   dance->addFrame("torso", 500).setRotation(0.0f, "leftleg");
   dance->addFrame("torso", 750).setRotation(-25.0f, "rightleg");
   dance->addFrame("torso", 1000).setRotation(0.0f, "rightleg");

   dance->addFrame("torso/leftleg", 250).setRotation(-25.0f);
   dance->addFrame("torso/leftleg", 500).setRotation(0.0f);

   dance->addFrame("torso/rightleg", 500).setRotation(0.0f);
   dance->addFrame("torso/rightleg", 750).setRotation(25.0f);
   dance->addFrame("torso/rightleg", 1000).setRotation(0.0f);

   dance->addFrame("torso/leftarm", 500).setRotation(-45.0f);
   dance->addFrame("torso/leftarm", 1000).setRotation(-135.0f)/*.setOffset(0.0f, -6.0f)*/;
      
   dance->addFrame("torso/rightarm", 500).setRotation(135.0f)/*.setOffset(0.0f, -6.0f)*/;
   dance->addFrame("torso/rightarm", 1000).setRotation(45.0f);

   dance->addFrame("torso/head", 250).setOffset(0.0f, 6.0f);
   dance->addFrame("torso/head", 500).setRotation(25.0f);
   dance->addFrame("torso/head", 750).setOffset(0.0f, 6.0f);
   dance->addFrame("torso/head", 1000).setRotation(-25.0f);

   manager->addAnimation("dance", std::move(dance));

   auto idle = std::unique_ptr<SkeletalAnimation>(new SkeletalAnimation(1000));
   idle->setLooping(true);

   idle->addFrame("torso", 500).setOffset(0.0f, 6.0f);
   idle->addFrame("torso", 1000);
   idle->addFrame("torso/head", 500).setOffset(0.0f, 12.0f);
   idle->addFrame("torso/head", 1000);
   idle->addFrame("torso/leftleg", 500).setOffset(0.0f, -6.0f);
   idle->addFrame("torso/leftleg", 1000);
   idle->addFrame("torso/rightleg", 500).setOffset(0.0f, -6.0f);
   idle->addFrame("torso/rightleg", 1000);

   manager->addAnimation("idle", std::move(idle));
}