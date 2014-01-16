#include "CharacterEntities.h"

#include "ComponentHelpers.h"
#include "StringTable.h"
#include "GraphicComponents.h"
#include "PhysicsComponents.h"
#include "IOCContainer.h"
#include "PositionComponent.h"
#include "TextureComponent.h"
#include "CharacterComponent.h"
#include "AIComponent.h"
#include "Application.h"
#include "CharacterAnimationStrategy.h"
#include "SpriteFactory.h"
#include "GameComponents.h"
#include "TextComponent.h"
#include "RotationComponent.h"
#include "SkeletalNodeComponent.h"
#include <GLFW/glfw3.h>

namespace CharacterEntities
{
   std::shared_ptr<Entity> buildCharacter()
   {
      auto e = std::make_shared<Entity>();
      auto app = IOC.resolve<Application>();
      auto st = IOC.resolve<StringTable>();

      //beautiful numbers
      float pixelMult = 6.0f;
      float torsoSize = 9.0f, headSize = 11.0f, rArmSize = 6.0f, lArmSize = 6.0f, rLegSize = 6.0f, lLegSize = 6.0f;
      Float2 headConn(4.5f / torsoSize, 3.0f / torsoSize);Float2 headCenter(5.5f / headSize, 11.0f / headSize);
      Float2 rArmConn(0.0f / torsoSize, 4.0f / torsoSize);Float2 rArmCenter(4.0f / rArmSize, 2.0f / rArmSize);
      Float2 lArmConn(9.0f / torsoSize, 4.0f / torsoSize);Float2 lArmCenter(2.0f / lArmSize, 2.0f / lArmSize);
      Float2 rLegConn(2.0f / torsoSize, 8.0f / torsoSize);Float2 rLegCenter(3.0f / rLegSize, 3.0f / rLegSize);
      Float2 lLegConn(7.0f / torsoSize, 8.0f / torsoSize);Float2 lLegCenter(3.0f / lLegSize, 3.0f / lLegSize);

      float charSize = 25.0f;
      Float2 charCenter = Float2(0.5f, 0.5f);
      float skeletonYOffset = 2.5f / charSize;

      e->addComponent<GraphicalBoundsComponent>(std::make_shared<GraphicalBoundsComponent>(Float2(pixelMult * charSize, pixelMult * charSize), charCenter));
      e->addComponent<PositionComponent>(std::make_shared<PositionComponent>(Float2()));
      e->addComponent<VelocityComponent>(std::make_shared<VelocityComponent>(Float2()));
      e->addComponent<FrictionComponent>(std::make_shared<FrictionComponent>(0.0f));
      e->addComponent<AccelerationComponent>(std::make_shared<AccelerationComponent>(Float2(), 0.0f, 10.0f));
      e->addComponent<ElevationComponent>(std::make_shared<ElevationComponent>(1.0f));
      e->addComponent<CharacterComponent>(std::make_shared<CharacterComponent>(e));
      e->addComponent<AIComponent>(std::make_shared<AIComponent>(e));
      e->addComponent<WanderComponent>(std::make_shared<WanderComponent>());

      auto skeleton = std::make_shared<Entity>();
      skeleton->addComponent<GraphicalBoundsComponent>(std::make_shared<GraphicalBoundsComponent>(
         Float2(pixelMult * charSize, pixelMult * charSize), charCenter));//offset for centering

      skeleton->addComponent<PositionComponent>(std::make_shared<PositionComponent>(Float2()));

      auto nc = std::make_shared<SkeletalNodeComponent>();
      auto torsoNode = nc->addConnection(st->get("torso"), Float2(0.5f, 0.5f + skeletonYOffset));//centers....2.5pixels
      skeleton->addComponent<SkeletalNodeComponent>(std::move(nc));

      auto torso = buildSpriteBodyPart(Float2(torsoSize*pixelMult, torsoSize*pixelMult), Float2(0.5f, 0.5f));
      torsoNode->entity = torso;

      nc = std::make_shared<SkeletalNodeComponent>();
      auto headNode = nc->addConnection(st->get("head"), headConn);
      auto rArmNode = nc->addConnection(st->get("rightarm"), rArmConn);
      auto lArmNode = nc->addConnection(st->get("leftarm"), lArmConn);
      auto rLegNode = nc->addConnection(st->get("rightleg"), rLegConn);
      auto lLegNode = nc->addConnection(st->get("leftleg"), lLegConn);
      torso->addComponent<SkeletalNodeComponent>(nc);

      headNode->entity = buildSpriteBodyPart(Float2(headSize*pixelMult, headSize*pixelMult), headCenter);
      rArmNode->entity = buildBasicBodyPart("assets/body/arm.png", Float2(rArmSize*pixelMult, rArmSize*pixelMult), rArmCenter);
      lArmNode->entity = buildBasicBodyPart("assets/body/arm.png", Float2(lArmSize*pixelMult, lArmSize*pixelMult), lArmCenter);
      rLegNode->entity = buildBasicBodyPart("assets/body/leg.png", Float2(rLegSize*pixelMult, rLegSize*pixelMult), rLegCenter);
      lLegNode->entity = buildBasicBodyPart("assets/body/leg.png", Float2(lLegSize*pixelMult, lLegSize*pixelMult), lLegCenter);


      auto blinkStrat = BlinkAnimationStrategy(2.0f, 0.1f);
      auto spr = IOC.resolve<SpriteFactory>()->buildSprite(st->get("assets/body/head"), &blinkStrat);
      headNode->entity->addComponent<SpriteComponent>(std::make_shared<SpriteComponent>(std::move(spr), st->get("front")));
      headNode->entity->getComponent<SpriteComponent>()->elapsedTime += app->rand(0, 100) / 100.0f;

      auto animStrat = CharacterAnimationStrategy();
      spr = IOC.resolve<SpriteFactory>()->buildSprite(st->get("assets/body/torso"), &animStrat);
      torso->addComponent<SpriteComponent>(std::make_shared<SpriteComponent>(std::move(spr), st->get("front")));

      e->addComponent<SkeletonComponent>(std::make_shared<SkeletonComponent>(skeleton));
      return e;
   }

   std::shared_ptr<Entity> buildBasicBodyPart(char *texture, Float2 size, Float2 center)
   {
      auto e = std::make_shared<Entity>();
      auto st = IOC.resolve<StringTable>();

      CompHelpers::addRectangleMeshComponent(*e, Rectf(0, 0, 1, 1), Colorf(1.0f, 1.0f, 1.0f));
      e->addComponent<TextureComponent>(std::make_shared<TextureComponent>(st->get(texture)));
      e->addComponent<GraphicalBoundsComponent>(std::make_shared<GraphicalBoundsComponent>(size, center));
      e->addComponent<PositionComponent>(std::make_shared<PositionComponent>(Float2()));

      return e;
   }

   std::shared_ptr<Entity> buildSpriteBodyPart(Float2 size, Float2 center)
   {
      auto e = std::make_shared<Entity>();

      auto st = IOC.resolve<StringTable>();

      CompHelpers::addRectangleMeshComponent(*e, Rectf(0, 0, 1, 1), Colorf(1.0f, 1.0f, 1.0f));
      e->addComponent<TextureComponent>(std::make_shared<TextureComponent>(st->get("")));
      e->addComponent<GraphicalBoundsComponent>(std::make_shared<GraphicalBoundsComponent>(size, center));
      e->addComponent<PositionComponent>(std::make_shared<PositionComponent>(Float2()));




      return e;
   }

   void addClothesItem(std::shared_ptr<Entity> e, const char *sprite)
   {
      auto st = IOC.resolve<StringTable>();
      auto parentSize = e->getComponent<GraphicalBoundsComponent>();
      auto parentChildList = e->getComponent<RenderChildrenComponent>();

      //build hair
      auto item = std::make_shared<Entity>();
      CompHelpers::addRectangleMeshComponent(*item, Rectf(0, 0, 1, 1), Colorf(1.0f, 1.0f, 1.0f));
      item->addComponent<TextureComponent>(std::make_shared<TextureComponent>(st->get("")));
      item->addComponent<GraphicalBoundsComponent>(std::make_shared<GraphicalBoundsComponent>(Float2(parentSize->size), Float2(parentSize->center)));
      item->addComponent<PositionComponent>(std::make_shared<PositionComponent>(Float2()));

      auto animStrat = CharacterAnimationStrategy();
      auto spr = IOC.resolve<SpriteFactory>()->buildSprite(st->get(sprite), &animStrat);
      item->addComponent<SpriteComponent>(std::make_shared<SpriteComponent>(std::move(spr), st->get("stand_down")));

      //bindings
      item->addComponent<BindAnimationComponent>(std::make_shared<BindAnimationComponent>(e));
      item->addComponent<PositionBindComponent>(std::make_shared<PositionBindComponent>(e, Float2()));

      //add children to scene
      item->addToScene(e->getScene());

      //add children to parent
      parentChildList->addChild(e, item, RenderChildrenComponent::Layer::Foreground);
   }

   void buildCharacterChildren(std::shared_ptr<Entity> e)
   {
      auto app = IOC.resolve<Application>();


      char *hairs[3] = {"assets/hair", "assets/hair:redhair", "assets/hair:bluehair"};
      char *clothes[3] = {"", ":redclothes", ":greenclothes"};

      int rand = app->rand(0, 3);
      addClothesItem(e, std::string("assets/pants" + std::string(clothes[rand])).c_str());

      rand = app->rand(0, 4);
      if(rand != 3) addClothesItem(e, std::string("assets/shirt" + std::string(clothes[rand])).c_str());

      rand = app->rand(0, 4);
      if(rand != 3)  addClothesItem(e, hairs[rand]);



   }

   std::shared_ptr<Entity> buildSwordAttack(std::weak_ptr<Entity> attacker)
   {
      auto e = std::make_shared<Entity>();
      auto st = IOC.resolve<StringTable>();

      CompHelpers::addRectangleMeshComponent(*e, Rectf(0, 0, 1, 1), Colorf(1.0f, 1.0f, 1.0f));
      e->addComponent<TextureComponent>(std::make_shared<TextureComponent>(st->get("")));
      e->addComponent<GraphicalBoundsComponent>(std::make_shared<GraphicalBoundsComponent>(Float2(), Float2(0.5f, 0.5f)));
      e->addComponent<PositionComponent>(std::make_shared<PositionComponent>(Float2()));

      CharacterAnimationStrategy animStrat;
      auto sprite = IOC.resolve<SpriteFactory>()->buildSprite(st->get("assets/attacks/sword"), &animStrat);
      e->addComponent<SpriteComponent>(std::make_shared<SpriteComponent>(std::move(sprite), st->get("swing_right")));

      e->addComponent<CollisionAreaComponent>(std::make_shared<CollisionAreaComponent>(Rectf(0.5f, 0.5f, 1.25, 1.25)));
      e->addComponent<AttackComponent>(std::make_shared<AttackComponent>(std::move(attacker), Float2()));

      return e;
   }

   std::shared_ptr<Entity> buildDamageMarker(std::weak_ptr<Entity> target)
   {
      auto e = std::make_shared<Entity>();
      auto st = IOC.resolve<StringTable>();

      if(auto pc = target.lock()->getComponent<PositionComponent>())
      {

         e->addComponent<TextComponent>(std::make_shared<TextComponent>(
         "", Float2(), std::make_shared<TextFont>("assets/fonts/pressstart.ttf", 24), Colorf(1, 1, 1)));
         e->addComponent<PositionComponent>(std::make_shared<PositionComponent>(pc->pos));

         auto dm = std::make_shared<DamageMarkerComponent>(e);
         dm->length = 3.0f;
         dm->startTime = IOC.resolve<Application>()->getTime();
         e->addComponent<DamageMarkerComponent>(std::move(dm));

         e->addComponent<ElevationComponent>(std::make_shared<ElevationComponent>(1.0f));
         e->addComponent(std::make_shared<LayerComponent>(RenderLayer::DamageMarkers));

      }

      return e;
   }
}

