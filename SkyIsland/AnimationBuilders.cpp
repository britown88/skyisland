#include "SkeletalAnimationsManager.h"

//basic character anim template
//void buildAnim()
//{
//   auto manager = IOC.resolve<SkeletalAnimationsManager>();
//   auto anim = std::unique_ptr<SkeletalAnimation>(new SkeletalAnimation(1000));
//   anim->setLooping(true);
//
//   anim->addFrame("torso", 500);
//   anim->addFrame("torso", 1000);
//
//   anim->addFrame("torso/leftleg", 500).setLayer(-1);
//   anim->addFrame("torso/leftleg", 1000);
//
//   anim->addFrame("torso/rightleg", 500).setLayer(-1);
//   anim->addFrame("torso/rightleg", 1000);
//
//   anim->addFrame("torso/leftarm", 500).setLayer(-2);
//   anim->addFrame("torso/leftarm", 1000);
//
//   anim->addFrame("torso/rightarm", 500).setLayer(-2);
//   anim->addFrame("torso/rightarm", 1000);
//
//   anim->addFrame("torso/head", 500).setLayer(2);
//   anim->addFrame("torso/head", 1000);
//
//   manager->addAnimation("animname", std::move(anim));
//}


void buildDance()
{
   auto manager = IOC.resolve<SkeletalAnimationsManager>();
   auto dance = std::unique_ptr<SkeletalAnimation>(new SkeletalAnimation(1000));
   dance->setLooping(true);

   dance->addFrame("torso", 250).setRotation(25.0f, "leftleg");
   dance->addFrame("torso", 500).setRotation(0.0f, "leftleg");
   dance->addFrame("torso", 750).setRotation(-25.0f, "rightleg");
   dance->addFrame("torso", 1000).setRotation(0.0f, "rightleg");

   dance->addFrame("torso/leftleg", 250).flipX(true).setLayer(-1).setRotation(-25.0f);
   dance->addFrame("torso/leftleg", 500).flipX(true).setRotation(0.0f);

   dance->addFrame("torso/rightleg", 500).setLayer(-1).setRotation(0.0f);
   dance->addFrame("torso/rightleg", 750).setRotation(25.0f);
   dance->addFrame("torso/rightleg", 1000).setRotation(0.0f);

   dance->addFrame("torso/leftarm", 500).flipX(true).setLayer(-2).setRotation(-45.0f);
   dance->addFrame("torso/leftarm", 1000).flipX(true).setRotation(-135.0f)/*.setOffset(0.0f, -6.0f)*/;

   dance->addFrame("torso/rightarm", 500).setLayer(-2).setRotation(135.0f)/*.setOffset(0.0f, -6.0f)*/;
   dance->addFrame("torso/rightarm", 1000).setRotation(45.0f);

   dance->addFrame("torso/head", 250).setLayer(2).setOffset(0.0f, 6.0f);
   dance->addFrame("torso/head", 500).setRotation(25.0f);
   dance->addFrame("torso/head", 750).setOffset(0.0f, 6.0f);
   dance->addFrame("torso/head", 1000).setRotation(-25.0f);

   manager->addAnimation("dance", std::move(dance));
}

void buildFaceFrames()
{
   auto manager = IOC.resolve<SkeletalAnimationsManager>();

   auto anim = std::unique_ptr<SkeletalAnimation>(new SkeletalAnimation(1000));
   anim->setLooping(false);
   
   anim->addFrame("torso", 0);
   anim->addFrame("torso", 1).setSpriteFace("front");
   anim->addFrame("torso/head", 0);
   anim->addFrame("torso/head", 1).setSpriteFace("front").setLayer(1);
   anim->addFrame("torso/leftarm", 0);
   anim->addFrame("torso/leftarm", 1).flipX(true).setLayer(-2);
   anim->addFrame("torso/rightarm", 0);
   anim->addFrame("torso/rightarm", 1).setLayer(-2);
   anim->addFrame("torso/rightleg", 0);
   anim->addFrame("torso/rightleg", 1).setLayer(-1);
   anim->addFrame("torso/leftleg", 0);
   anim->addFrame("torso/leftleg", 1).flipX(true).setLayer(-1);
   manager->addAnimation("facedown", std::move(anim));

   float legRepos = 30.0f;
   float armRepos = 66.0f;
   anim = std::unique_ptr<SkeletalAnimation>(new SkeletalAnimation(1000));
   anim->setLooping(false);
   
   anim->addFrame("torso", 0).setSpriteFace("back");
   anim->addFrame("torso", 1);   
   anim->addFrame("torso/head", 0);
   anim->addFrame("torso/head", 1).setSpriteFace("back").setLayer(1);
   anim->addFrame("torso/leftarm", 0).setOffset(-armRepos, 0.0f);
   anim->addFrame("torso/leftarm", 1).setLayer(-2);
   anim->addFrame("torso/rightarm", 0).setOffset(armRepos, 0.0f);
   anim->addFrame("torso/rightarm", 1).flipX(true).setLayer(-2);
   anim->addFrame("torso/leftleg", 0).setOffset(-legRepos, 0.0f);
   anim->addFrame("torso/leftleg", 1).setLayer(-1);
   anim->addFrame("torso/rightleg", 0).setOffset(legRepos, 0.0f);  
   anim->addFrame("torso/rightleg", 1).flipX(true).setLayer(-1);
   manager->addAnimation("faceup", std::move(anim));

   float armCenter = 16.0f;
   float backLegOffset = 6.0f;
   float frontLegOffset = 12.0f;
   anim = std::unique_ptr<SkeletalAnimation>(new SkeletalAnimation(1000));
   anim->setLooping(false);   
   anim->addFrame("torso", 0);
   anim->addFrame("torso", 1).setSpriteFace("side");
   anim->addFrame("torso/head", 0);
   anim->addFrame("torso/head", 1).setSpriteFace("side").setLayer(2);
   anim->addFrame("torso/leftarm", 0).setOffset(-armCenter, 0.0f);
   anim->addFrame("torso/leftarm", 1).flipX(true).setLayer(-3);
   anim->addFrame("torso/rightarm", 0).setOffset(armCenter, 0.0f);
   anim->addFrame("torso/rightarm", 1).setLayer(1);
   anim->addFrame("torso/leftleg", 0).setOffset(-backLegOffset, 0.0f);
   anim->addFrame("torso/leftleg", 1).flipX(true).setLayer(-2);
   anim->addFrame("torso/rightleg", 0).setOffset(frontLegOffset, 0.0f);
   anim->addFrame("torso/rightleg", 1).flipX(true).setLayer(-1);
   manager->addAnimation("faceright", std::move(anim));


   anim = std::unique_ptr<SkeletalAnimation>(new SkeletalAnimation(1000));
   anim->setLooping(false);   
   anim->addFrame("torso", 0);
   anim->addFrame("torso", 1).setSpriteFace("side").flipX(true);
   anim->addFrame("torso/head", 0);
   anim->addFrame("torso/head", 1).setSpriteFace("side").flipX(true).setLayer(2);
   anim->addFrame("torso/leftarm", 0).setOffset(-armCenter, 0.0f);
   anim->addFrame("torso/leftarm", 1).flipX(true).setLayer(1);
   anim->addFrame("torso/rightarm", 0).setOffset(armCenter, 0.0f);
   anim->addFrame("torso/rightarm", 1).setLayer(-3);
   anim->addFrame("torso/leftleg", 0).setOffset(-frontLegOffset, 0.0f);
   anim->addFrame("torso/leftleg", 1).setLayer(-1);
   anim->addFrame("torso/rightleg", 0).setOffset(backLegOffset, 0.0f);
   anim->addFrame("torso/rightleg", 1).setLayer(-2);
   manager->addAnimation("faceleft", std::move(anim));


}

void buildIdleDown()
{
   auto manager = IOC.resolve<SkeletalAnimationsManager>();
   auto anim = std::unique_ptr<SkeletalAnimation>(new SkeletalAnimation(1000));
   anim->setLooping(true);

   float bodyBob = 6.0f, armSway = 10.0f;
   anim->addFrame("torso", 500).setSpriteFace("front").setOffset(0.0f, bodyBob);
   anim->addFrame("torso", 1000);

   anim->addFrame("torso/head", 500).setSpriteFace("front").setLayer(1);
   anim->addFrame("torso/head", 1000);

   anim->addFrame("torso/leftarm", 500).flipX(true).setLayer(-2).setRotation(-armSway);
   anim->addFrame("torso/leftarm", 1000).flipX(true);
   anim->addFrame("torso/rightarm", 500).setLayer(-2).setRotation(armSway);
   anim->addFrame("torso/rightarm", 1000);

   anim->addFrame("torso/rightleg", 500).setLayer(-1).setOffset(0.0f, -bodyBob);
   anim->addFrame("torso/rightleg", 1000);
   anim->addFrame("torso/leftleg", 500).flipX(true).setLayer(-1).setOffset(0.0f, -bodyBob);
   anim->addFrame("torso/leftleg", 1000).flipX(true);

   manager->addAnimation("idledown", std::move(anim));
}

void buildIdleUp()
{
   auto manager = IOC.resolve<SkeletalAnimationsManager>();
   auto anim = std::unique_ptr<SkeletalAnimation>(new SkeletalAnimation(1000));
   anim->setLooping(true);

   float legRepos = 30.0f;
   float armRepos = 66.0f;
   float bodyBob = 6.0f, armSway = 10.0f;
   anim->addFrame("torso", 500).setSpriteFace("back").setOffset(0.0f, bodyBob);
   anim->addFrame("torso", 1000);

   anim->addFrame("torso/head", 500).setSpriteFace("back").setLayer(1);
   anim->addFrame("torso/head", 1000);

   anim->addFrame("torso/leftarm", 500).setLayer(-2).setOffset(-armRepos, 0.0f).setRotation(armSway);
   anim->addFrame("torso/leftarm", 1000).setOffset(-armRepos, 0.0f);
   anim->addFrame("torso/rightarm", 500).flipX(true).setLayer(-2).setOffset(armRepos, 0.0f).setRotation(-armSway);
   anim->addFrame("torso/rightarm", 1000).flipX(true).setOffset(armRepos, 0.0f);

   anim->addFrame("torso/leftleg", 500).setLayer(-1).setOffset(-legRepos, -bodyBob);
   anim->addFrame("torso/leftleg", 1000).setOffset(-legRepos, 0.0f);
   anim->addFrame("torso/rightleg", 500).flipX(true).setLayer(-1).setOffset(legRepos, -bodyBob);
   anim->addFrame("torso/rightleg", 1000).flipX(true).setOffset(legRepos, 0.0f);   

   manager->addAnimation("idleup", std::move(anim));
}

void buildIdleRight()
{
   auto manager = IOC.resolve<SkeletalAnimationsManager>();
   auto anim = std::unique_ptr<SkeletalAnimation>(new SkeletalAnimation(1000));
   anim->setLooping(true);

   float bodyBob = 6.0f, armSway = 10.0f;
   float armCenter = 16.0f;
   float backLegOffset = 6.0f;
   float frontLegOffset = 12.0f;
   float legDown = 3.0f;
   float headBob = 6.0f;

   anim->addFrame("torso", 500).setSpriteFace("side").setOffset(0.0f, bodyBob);
   anim->addFrame("torso", 1000);

   anim->addFrame("torso/head", 500).setSpriteFace("side").setLayer(2).setOffset(0.0f, headBob);
   anim->addFrame("torso/head", 1000).setOffset(0.0f, headBob);

   anim->addFrame("torso/leftarm", 500).flipX(true).setLayer(-3).setOffset(-armCenter, 0.0f).setRotation(-armSway);
   anim->addFrame("torso/leftarm", 1000).flipX(true).setOffset(-armCenter, 0.0f);
   anim->addFrame("torso/rightarm", 500).setLayer(1).setOffset(armCenter, 0.0f).setRotation(armSway);
   anim->addFrame("torso/rightarm", 1000).setOffset(armCenter, 0.0f);

   anim->addFrame("torso/leftleg", 500).flipX(true).setLayer(-2).setOffset(-backLegOffset, -bodyBob);
   anim->addFrame("torso/leftleg", 1000).flipX(true).setOffset(-backLegOffset, 0.0f);
   anim->addFrame("torso/rightleg", 500).flipX(true).setLayer(-1).setOffset(frontLegOffset, -bodyBob + legDown);
   anim->addFrame("torso/rightleg", 1000).flipX(true).setOffset(frontLegOffset, legDown);

   manager->addAnimation("idleright", std::move(anim));
}

void buildIdleLeft()
{
   auto manager = IOC.resolve<SkeletalAnimationsManager>();
   auto anim = std::unique_ptr<SkeletalAnimation>(new SkeletalAnimation(1000));
   anim->setLooping(true);

   float bodyBob = 6.0f, armSway = 10.0f;
   float armCenter = 16.0f;
   float backLegOffset = 6.0f;
   float frontLegOffset = 12.0f;
   float legDown = 3.0f;
   float headBob = 6.0f;

   anim->addFrame("torso", 500).setSpriteFace("side").flipX(true).setOffset(0.0f, bodyBob);
   anim->addFrame("torso", 1000).flipX(true);

   anim->addFrame("torso/head", 500).setSpriteFace("side").flipX(true).setLayer(2).setOffset(0.0f, headBob);
   anim->addFrame("torso/head", 1000).flipX(true).setOffset(0.0f, headBob);

   anim->addFrame("torso/leftarm", 500).flipX(true).setLayer(1).setOffset(-armCenter, 0.0f).setRotation(-armSway);
   anim->addFrame("torso/leftarm", 1000).flipX(true).setOffset(-armCenter, 0.0f);
   anim->addFrame("torso/rightarm", 500).setLayer(-3).setOffset(armCenter, 0.0f).setRotation(armSway);
   anim->addFrame("torso/rightarm", 1000).setOffset(armCenter, 0.0f);

   anim->addFrame("torso/leftleg", 500).setLayer(-1).setOffset(-frontLegOffset, -bodyBob + legDown);
   anim->addFrame("torso/leftleg", 1000).setOffset(-frontLegOffset, legDown);
   anim->addFrame("torso/rightleg", 500).setLayer(-2).setOffset(backLegOffset, -bodyBob);
   anim->addFrame("torso/rightleg", 1000).setOffset(backLegOffset, 0.0f);

   manager->addAnimation("idleleft", std::move(anim));
}

void buildWalkRight()
{
   auto manager = IOC.resolve<SkeletalAnimationsManager>();
   auto anim = std::unique_ptr<SkeletalAnimation>(new SkeletalAnimation(1000));
   anim->setLooping(true);

   float armCenter = 22.0f;
   float legCenter = 15.0f;
   float armRot = 45.0f;
   float legRot = 45.0f;
   float legSwayF = 12.0f, legSwayN = 12.0f;
   float legBob = 6.0f;
   float bodyBob = 12.0f;
   float headBob = 3.0f;

   //pay no attention to the magic number
   anim->addFrame("torso", 250).setSpriteFace("side").setOffset(0.0f, bodyBob);
   anim->addFrame("torso", 500);
   anim->addFrame("torso", 750).setOffset(0.0f, bodyBob);;
   anim->addFrame("torso", 1000);

   //backleg
   anim->addFrame("torso/leftleg", 250).setLayer(-2).flipX(true).setOffset(-legCenter + legSwayN, legBob - bodyBob);//down forward
   anim->addFrame("torso/leftleg", 500).flipX(true).setOffset(-legCenter, legBob);//up
   anim->addFrame("torso/leftleg", 750).flipX(true).setOffset(-legCenter - legSwayF, legBob - bodyBob);//down back
   anim->addFrame("torso/leftleg", 1000).flipX(true).setOffset(-legCenter, -12.0f).setRotation(legRot);//up

   //frontleg
   anim->addFrame("torso/rightleg", 250).setLayer(-1).flipX(true).setOffset(legCenter - legSwayN, legBob - bodyBob);//down back
   anim->addFrame("torso/rightleg", 500).flipX(true).setOffset(legCenter, -12.0f).setRotation(legRot);//up
   anim->addFrame("torso/rightleg", 750).flipX(true).setOffset(legCenter + legSwayF, legBob - bodyBob);//down forward
   anim->addFrame("torso/rightleg", 1000).flipX(true).setOffset(legCenter, legBob);//up

   anim->addFrame("torso/leftarm", 250).flipX(true).setLayer(-3).setOffset(-armCenter, 0.0f).setRotation(armRot);
   anim->addFrame("torso/leftarm", 500).flipX(true).setOffset(-armCenter, 0.0f);
   anim->addFrame("torso/leftarm", 750).flipX(true).setOffset(-armCenter, 0.0f).setRotation(-armRot);
   anim->addFrame("torso/leftarm", 1000).flipX(true).setOffset(-armCenter, 0.0f);

   anim->addFrame("torso/rightarm", 250).setLayer(1).setOffset(armCenter, 0.0f).setRotation(-armRot);
   anim->addFrame("torso/rightarm", 500).setOffset(armCenter, 0.0f);
   anim->addFrame("torso/rightarm", 750).setOffset(armCenter, 0.0f).setRotation(armRot);
   anim->addFrame("torso/rightarm", 1000).setOffset(armCenter, 0.0f);

   anim->addFrame("torso/head", 250).setOffset(0.0f, headBob).setSpriteFace("side").setLayer(2);
   anim->addFrame("torso/head", 500);
   anim->addFrame("torso/head", 750).setOffset(0.0f, headBob);
   anim->addFrame("torso/head", 1000);

   manager->addAnimation("walkright", std::move(anim));
}

void buildWalkLeft()
{
   auto manager = IOC.resolve<SkeletalAnimationsManager>();
   auto anim = std::unique_ptr<SkeletalAnimation>(new SkeletalAnimation(1000));
   anim->setLooping(true);

   float armCenter = 22.0f;
   float legCenter = 15.0f;
   float armRot = 45.0f;
   float legRot = 45.0f;
   float legSwayF = 12.0f, legSwayN = 12.0f;
   float legBob = 6.0f;
   float bodyBob = 12.0f;
   float headBob = 3.0f;

   //pay no attention to the magic number
   anim->addFrame("torso", 250).setSpriteFace("side").flipX(true).setOffset(0.0f, bodyBob);
   anim->addFrame("torso", 500).flipX(true);
   anim->addFrame("torso", 750).flipX(true).setOffset(0.0f, bodyBob);
   anim->addFrame("torso", 1000).flipX(true);

   //frontleg
   anim->addFrame("torso/leftleg", 250).setLayer(-1).setOffset(-legCenter - legSwayN, legBob - bodyBob);//down forward
   anim->addFrame("torso/leftleg", 500).setOffset(-legCenter, legBob);//up
   anim->addFrame("torso/leftleg", 750).setOffset(-legCenter + legSwayF, legBob - bodyBob);//down back
   anim->addFrame("torso/leftleg", 1000).setOffset(-legCenter, -12.0f).setRotation(-legRot);//up

   //backleg
   anim->addFrame("torso/rightleg", 250).setLayer(-2).setOffset(legCenter + legSwayN, legBob - bodyBob);//down back
   anim->addFrame("torso/rightleg", 500).setOffset(legCenter, -12.0f).setRotation(-legRot);//up
   anim->addFrame("torso/rightleg", 750).setOffset(legCenter - legSwayF, legBob - bodyBob);//down forward
   anim->addFrame("torso/rightleg", 1000).setOffset(legCenter, legBob);//up

   anim->addFrame("torso/leftarm", 250).flipX(true).setLayer(1).setOffset(-armCenter, 0.0f).setRotation(-armRot);
   anim->addFrame("torso/leftarm", 500).flipX(true).setOffset(-armCenter, 0.0f);
   anim->addFrame("torso/leftarm", 750).flipX(true).setOffset(-armCenter, 0.0f).setRotation(armRot);
   anim->addFrame("torso/leftarm", 1000).flipX(true).setOffset(-armCenter, 0.0f);

   anim->addFrame("torso/rightarm", 250).setLayer(-3).setOffset(armCenter, 0.0f).setRotation(armRot);
   anim->addFrame("torso/rightarm", 500).setOffset(armCenter, 0.0f);
   anim->addFrame("torso/rightarm", 750).setOffset(armCenter, 0.0f).setRotation(-armRot);
   anim->addFrame("torso/rightarm", 1000).setOffset(armCenter, 0.0f);

   anim->addFrame("torso/head", 250).flipX(true).setOffset(0.0f, headBob).setSpriteFace("side").setLayer(2);
   anim->addFrame("torso/head", 500).flipX(true);
   anim->addFrame("torso/head", 750).flipX(true).setOffset(0.0f, headBob);
   anim->addFrame("torso/head", 1000).flipX(true);

   manager->addAnimation("walkleft", std::move(anim));
}

void buildWalkDown()
{
   auto manager = IOC.resolve<SkeletalAnimationsManager>();
   auto anim = std::unique_ptr<SkeletalAnimation>(new SkeletalAnimation(1000));
   anim->setLooping(true);

   float bodySway = 5.0f, headBob = 6.0f, bodyBob = 6.0f, legDip = 6.0f, armSwing = 15.0f;

   anim->addFrame("torso", 250).setSpriteFace("front").setOffset(0.0f, bodyBob).setRotation(bodySway, "leftleg");
   anim->addFrame("torso", 500).setRotation(0.0f, "leftleg");
   anim->addFrame("torso", 750).setOffset(0.0f, bodyBob).setRotation(-bodySway, "rightleg");
   anim->addFrame("torso", 1000).setRotation(0.0f, "rightleg");

   anim->addFrame("torso/leftleg", 250).flipX(true).setLayer(-1).setOffset(0.0f, -legDip).setRotation(-bodySway);
   anim->addFrame("torso/leftleg", 500).flipX(true);
   anim->addFrame("torso/leftleg", 750).flipX(true).setOffset(0.0f, legDip);
   anim->addFrame("torso/leftleg", 1000).flipX(true);

   anim->addFrame("torso/rightleg", 250).setLayer(-1).setOffset(0.0f, legDip);
   anim->addFrame("torso/rightleg", 500);
   anim->addFrame("torso/rightleg", 750).setOffset(0.0f, -legDip).setRotation(bodySway);
   anim->addFrame("torso/rightleg", 1000);

   anim->addFrame("torso/leftarm", 250).flipX(true).setLayer(1).setRotation(armSwing);
   anim->addFrame("torso/leftarm", 500).flipX(true).setRotation(-armSwing);
   anim->addFrame("torso/leftarm", 750).flipX(true).setLayer(-2).setRotation(armSwing);
   anim->addFrame("torso/leftarm", 1000).flipX(true).setRotation(-armSwing);

   anim->addFrame("torso/rightarm", 250).setLayer(-2).setRotation(-armSwing);
   anim->addFrame("torso/rightarm", 500).setRotation(armSwing);
   anim->addFrame("torso/rightarm", 750).setLayer(1).setRotation(-armSwing);
   anim->addFrame("torso/rightarm", 1000).setRotation(armSwing);

   anim->addFrame("torso/head", 250).setSpriteFace("front").setLayer(2).setOffset(0.0f, headBob);
   anim->addFrame("torso/head", 500);
   anim->addFrame("torso/head", 750).setOffset(0.0f, headBob);
   anim->addFrame("torso/head", 1000);

   manager->addAnimation("walkdown", std::move(anim));
}

void buildWalkUp()
{
   auto manager = IOC.resolve<SkeletalAnimationsManager>();
   auto anim = std::unique_ptr<SkeletalAnimation>(new SkeletalAnimation(1000));
   anim->setLooping(true);

   float legRepos = 30.0f;
   float armRepos = 66.0f;
   float bodySway = 5.0f, headBob = 6.0f, bodyBob = 6.0f, legDip = 6.0f, armSwing = 15.0f;

   anim->addFrame("torso", 250).setSpriteFace("back").setOffset(0.0f, bodyBob).setRotation(bodySway, "leftleg");
   anim->addFrame("torso", 500).setRotation(0.0f, "leftleg");
   anim->addFrame("torso", 750).setOffset(0.0f, bodyBob).setRotation(-bodySway, "rightleg");
   anim->addFrame("torso", 1000).setRotation(0.0f, "rightleg");

   anim->addFrame("torso/leftleg", 250).setLayer(-1).setOffset(-legRepos, -legDip).setRotation(-bodySway);
   anim->addFrame("torso/leftleg", 500).setOffset(-legRepos, 0.0f);
   anim->addFrame("torso/leftleg", 750).setOffset(-legRepos, legDip);
   anim->addFrame("torso/leftleg", 1000).setOffset(-legRepos, 0.0f);

   anim->addFrame("torso/rightleg", 250).flipX(true).setLayer(-1).setOffset(legRepos, legDip);
   anim->addFrame("torso/rightleg", 500).flipX(true).setOffset(legRepos, 0.0f);
   anim->addFrame("torso/rightleg", 750).flipX(true).setOffset(legRepos, -legDip).setRotation(bodySway);
   anim->addFrame("torso/rightleg", 1000).flipX(true).setOffset(legRepos, 0.0f);

   anim->addFrame("torso/leftarm", 250).setLayer(1).setOffset(-armRepos, 0.0f).setRotation(-armSwing, Float2(0.33f, 0.0f));
   anim->addFrame("torso/leftarm", 500).setOffset(-armRepos, 0.0f).setRotation(armSwing, Float2(0.33f, 0.0f));
   anim->addFrame("torso/leftarm", 750).setLayer(-2).setOffset(-armRepos, 0.0f).setRotation(-armSwing, Float2(0.33f, 0.0f));
   anim->addFrame("torso/leftarm", 1000).setOffset(-armRepos, 0.0f).setRotation(armSwing, Float2(0.33f, 0.0f));

   anim->addFrame("torso/rightarm", 250).flipX(true).setOffset(armRepos, 0.0f).setLayer(-2).setRotation(armSwing, Float2(-0.33f, 0.0f));
   anim->addFrame("torso/rightarm", 500).flipX(true).setOffset(armRepos, 0.0f).setRotation(-armSwing, Float2(-0.33f, 0.0f));
   anim->addFrame("torso/rightarm", 750).flipX(true).setOffset(armRepos, 0.0f).setLayer(1).setRotation(armSwing, Float2(-0.33f, 0.0f));
   anim->addFrame("torso/rightarm", 1000).flipX(true).setOffset(armRepos, 0.0f).setRotation(-armSwing, Float2(-0.33f, 0.0f));

   anim->addFrame("torso/head", 250).setSpriteFace("back").setLayer(2).setOffset(0.0f, headBob);
   anim->addFrame("torso/head", 500);
   anim->addFrame("torso/head", 750).setOffset(0.0f, headBob);
   anim->addFrame("torso/head", 1000);

   manager->addAnimation("walkup", std::move(anim));
}



void buildSkeletalAnimations()
{
   auto manager = IOC.resolve<SkeletalAnimationsManager>();

   buildDance();
   buildWalkDown();
   buildWalkUp();
   buildWalkRight();
   buildWalkLeft();
   buildIdleDown();
   buildIdleUp();
   buildIdleRight();
   buildIdleLeft();
   buildFaceFrames();

}
