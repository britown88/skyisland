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
#include "CharacterAnimationStrategy.h"
#include "SpriteFactory.h"
#include "GameComponents.h"
#include "TextComponent.h"

namespace CharacterEntities
{
   std::shared_ptr<Entity> buildCharacter()
   {      
      auto e = std::make_shared<Entity>();
      auto st = IOC.resolve<StringTable>();
      
      CompHelpers::addRectangleMeshComponent(*e, Rectf(0, 0, 1, 1), Colorf(1.0f, 1.0f, 1.0f));

      e->addComponent<TextureComponent>(std::make_shared<TextureComponent>(st->get("")));
      e->addComponent<GraphicalBoundsComponent>(std::make_shared<GraphicalBoundsComponent>(Float2(), Float2(0.5f, 0.5f)));
      e->addComponent<PositionComponent>(std::make_shared<PositionComponent>(Float2()));
      e->addComponent<VelocityComponent>(std::make_shared<VelocityComponent>(Float2(0.0f, 0.0f)));
      e->addComponent<FrictionComponent>(std::make_shared<FrictionComponent>(0.0f));
      e->addComponent<AccelerationComponent>(std::make_shared<AccelerationComponent>(Float2(), 0.0f, 10.0f));
      e->addComponent<ElevationComponent>(std::make_shared<ElevationComponent>(1.0f));
      e->addComponent<CharacterComponent>(std::make_shared<CharacterComponent>(e));

      //std::string str, Float2 drawPos, std::shared_ptr<TextFont> font, Colorf color)
      e->addComponent<TextComponent>(std::make_shared<TextComponent>(
         "What does walking MEAN",
         Float2(),
         std::make_shared<TextFont>("assets/fonts/pressstart.ttf", 12),
         Colorf(1, 1, 1)
         ));
     
      e->addComponent<AIComponent>(std::make_shared<AIComponent>(e));
      e->addComponent<WanderComponent>(std::make_shared<WanderComponent>());
      
      CharacterAnimationStrategy animStrat;
      auto sprite = IOC.resolve<SpriteFactory>()->buildSprite(st->get("assets/guy"), animStrat);
      e->addComponent<SpriteComponent>(std::make_shared<SpriteComponent>(std::move(sprite), st->get("stand_down")));
      
      e->addComponent<CollisionAreaComponent>(std::make_shared<CollisionAreaComponent>(Rectf(0.25f, 0.5, 0.75f, 1)));
      
      return e;
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
      auto sprite = IOC.resolve<SpriteFactory>()->buildSprite(st->get("assets/attacks/sword"), animStrat);
      e->addComponent<SpriteComponent>(std::make_shared<SpriteComponent>(std::move(sprite), st->get("swing_right")));

      e->addComponent<CollisionAreaComponent>(std::make_shared<CollisionAreaComponent>(Rectf(0.5f, 0.5f, 1.25, 1.25)));
      e->addComponent<AttackComponent>(std::make_shared<AttackComponent>(std::move(attacker), Float2()));

      return e;
   }
}

