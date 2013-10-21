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
     
      e->addComponent<AIComponent>(std::make_shared<AIComponent>(e));
      e->addComponent<WanderComponent>(std::make_shared<WanderComponent>());
      
      CharacterAnimationStrategy animStrat;
      auto sprite = IOC.resolve<SpriteFactory>()->buildSprite(st->get("assets/guy"), animStrat);
      e->addComponent<SpriteComponent>(std::make_shared<SpriteComponent>(std::move(sprite), st->get("stand_down")));
      
      return e;
   }

   std::shared_ptr<Entity> buildSwordAttack()
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

      return e;
   }
}

