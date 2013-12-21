#include "SkeletalAnimationsManager.h"

void buildDance()
{
   auto manager = IOC.resolve<SkeletalAnimationsManager>();
   auto dance = std::unique_ptr<SkeletalAnimation>(new SkeletalAnimation(1000));
   dance->setLooping(true);

   dance->addFrame("torso", 250).setRotation(25.0f, "leftleg");
   dance->addFrame("torso", 500).setRotation(0.0f, "leftleg");
   dance->addFrame("torso", 750).setRotation(-25.0f, "rightleg");
   dance->addFrame("torso", 1000).setRotation(0.0f, "rightleg");

   dance->addFrame("torso/leftleg", 250).setLayer(-1).setRotation(-25.0f);
   dance->addFrame("torso/leftleg", 500).setRotation(0.0f);

   dance->addFrame("torso/rightleg", 500).setLayer(-1).setRotation(0.0f);
   dance->addFrame("torso/rightleg", 750).setRotation(25.0f);
   dance->addFrame("torso/rightleg", 1000).setRotation(0.0f);

   dance->addFrame("torso/leftarm", 500).setLayer(-2).setRotation(-45.0f);
   dance->addFrame("torso/leftarm", 1000).setRotation(-135.0f)/*.setOffset(0.0f, -6.0f)*/;
      
   dance->addFrame("torso/rightarm", 500).setLayer(-2).setRotation(135.0f)/*.setOffset(0.0f, -6.0f)*/;
   dance->addFrame("torso/rightarm", 1000).setRotation(45.0f);

   dance->addFrame("torso/head", 250).setLayer(2).setOffset(0.0f, 6.0f);
   dance->addFrame("torso/head", 500).setRotation(25.0f);
   dance->addFrame("torso/head", 750).setOffset(0.0f, 6.0f);
   dance->addFrame("torso/head", 1000).setRotation(-25.0f);

   manager->addAnimation("dance", std::move(dance));
}

void buildIdle()
{
   auto manager = IOC.resolve<SkeletalAnimationsManager>();
   auto anim = std::unique_ptr<SkeletalAnimation>(new SkeletalAnimation(1000));
   anim->setLooping(true);

   float bodyBob = 6.0f, armSway = 10.0f;
   anim->addFrame("torso", 500).setOffset(0.0f, bodyBob);
   anim->addFrame("torso", 1000);

   anim->addFrame("torso/head", 0).setLayer(1);
   anim->addFrame("torso/head", 1);

   anim->addFrame("torso/leftarm", 500).setLayer(-2).setRotation(-armSway);
   anim->addFrame("torso/leftarm", 1000);
   anim->addFrame("torso/rightarm", 500).setLayer(-2).setRotation(armSway);
   anim->addFrame("torso/rightarm", 1000);

   anim->addFrame("torso/rightleg", 500).setLayer(-1).setOffset(0.0f, -bodyBob);
   anim->addFrame("torso/rightleg", 1000);
   anim->addFrame("torso/leftleg", 500).setLayer(-1).setOffset(0.0f, -bodyBob);
   anim->addFrame("torso/leftleg", 1000);



   manager->addAnimation("idle", std::move(anim));
}

void buildWalkDown()
{
   auto manager = IOC.resolve<SkeletalAnimationsManager>();
   auto anim = std::unique_ptr<SkeletalAnimation>(new SkeletalAnimation(1000));
   anim->setLooping(true);

   float bodySway = 5.0f, headBob = 6.0f, bodyBob = 6.0f, legDip = 12.0f, armSwing = 25.0f;

   anim->addFrame("torso", 250).setOffset(0.0f, bodyBob).setRotation(bodySway, "leftleg");
   anim->addFrame("torso", 500).setRotation(0.0f, "leftleg");
   anim->addFrame("torso", 750).setOffset(0.0f, bodyBob).setRotation(-bodySway, "rightleg");
   anim->addFrame("torso", 1000).setRotation(0.0f, "rightleg");

   anim->addFrame("torso/leftleg", 250).setLayer(-1).setOffset(0.0f, -legDip).setRotation(-bodySway);
   anim->addFrame("torso/leftleg", 500);
   anim->addFrame("torso/leftleg", 750).setOffset(0.0f, legDip);
   anim->addFrame("torso/leftleg", 1000);

   anim->addFrame("torso/rightleg", 250).setLayer(-1).setOffset(0.0f, legDip);
   anim->addFrame("torso/rightleg", 500);
   anim->addFrame("torso/rightleg", 750).setOffset(0.0f, -legDip).setRotation(bodySway);
   anim->addFrame("torso/rightleg", 1000);

   anim->addFrame("torso/leftarm", 250).setLayer(1).setRotation(armSwing);
   anim->addFrame("torso/leftarm", 500).setRotation(-armSwing);
   anim->addFrame("torso/leftarm", 750).setLayer(-2).setRotation(armSwing);
   anim->addFrame("torso/leftarm", 1000).setRotation(-armSwing);

   anim->addFrame("torso/rightarm", 250).setLayer(-2).setRotation(-armSwing);
   anim->addFrame("torso/rightarm", 500).setRotation(armSwing);
   anim->addFrame("torso/rightarm", 750).setLayer(1).setRotation(-armSwing);
   anim->addFrame("torso/rightarm", 1000).setRotation(armSwing);

   anim->addFrame("torso/head", 250).setLayer(2).setOffset(0.0f, headBob);
   anim->addFrame("torso/head", 500);
   anim->addFrame("torso/head", 750).setOffset(0.0f, headBob);
   anim->addFrame("torso/head", 1000);

   manager->addAnimation("walkdown", std::move(anim));
}


void buildSkeletalAnimations()
{
   auto manager = IOC.resolve<SkeletalAnimationsManager>();

   buildDance();
   buildWalkDown();
   buildIdle();
   
}