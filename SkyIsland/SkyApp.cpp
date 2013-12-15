#include <GLFW/glfw3.h>
#include "SkyApp.h"
#include "Viewport.h"
#include "Camera.h"
#include "Scene.h"
#include "RenderManager.h"
#include "SpriteFactory.h"
#include "Color.h"

#include "MeshComponent.h"
#include "PositionComponent.h"
#include "RotationComponent.h"
#include "PhysicsComponents.h"
#include "GraphicComponents.h"
#include "TextureComponent.h"
#include "CharacterComponent.h"
#include "PhysicsManager.h"
#include "CharacterAnimationManager.h"
#include "CharacterManager.h"
#include "AIManager.h"
#include "AIComponent.h"
#include "AttackManager.h"
#include "DamageMarkerManager.h"

#include "IKeyEvent.h"
#include "KeyHandler.h"
#include "MouseHandler.h"

#include "CharacterController.h"
#include "CharacterInputHandler.h"
#include "CameraController.h"
#include "CameraStrategies.h"

#include "ComponentHelpers.h"
#include "CharacterAnimationStrategy.h"
#include "CharacterEntities.h"

#include <unordered_map>

class SkyApp : public Application
{
   std::string getWindowTitle()
   {
      return "Arq: Legend of Shumpf Guy";
   }

   Int2 getDefaultWindowSize()
   {
      return Int2(1440, 810);
   }

   //GLFWmonitor *getWindowMonitor()
   //{
   //   return glfwGetPrimaryMonitor();
   //}

   std::shared_ptr<Scene> scene, UIScene;
   std::shared_ptr<Camera> camera, camera2, UICamera;
   std::unique_ptr<CharacterInputHandler> cc;
   std::shared_ptr<Viewport> viewport, viewport2, UIViewport;
   std::unique_ptr<CameraController> camControl, camControl2;
   std::vector<std::shared_ptr<Entity>> eList;
   std::shared_ptr<Entity> UIEntity, target;

   int eIndex;

   KeyEvent tabEvent, spaceEvent;
   MouseEvent clickEvent, click2;

   std::shared_ptr<Entity> buildUIEntity()
   {
      auto e = std::make_shared<Entity>();

      CompHelpers::addRectangleMeshComponent(*e, Rectf(0, 0, 100, 100), Colorf(1.0f, 1.0f, 1.0f));
      e->addComponent<PositionComponent>(std::make_shared<PositionComponent>(Float2()));
      e->addToScene(UIScene);

      return e;
   }

   void nextEntity()
   {
      //add the AI back in
      if(eIndex >= 0)
      {
         eList[eIndex]->addComponent<AIComponent>(std::make_shared<AIComponent>(eList[eIndex]));
         eList[eIndex]->getComponent<RenderChildrenComponent>()->children.erase(target->getComponent<RenderParentComponent>()->parentIter);

      }
         

      ++eIndex;
      if(eIndex >= eList.size())
         eIndex = 0;

      //remove the AI and stop moving
      eList[eIndex]->removeComponent<AIComponent>();
      eList[eIndex]->getComponent<CharacterComponent>()->controller->stop();
      eList[eIndex]->getComponent<RenderChildrenComponent>()->addChild(eList[eIndex], target, RenderChildrenComponent::Layer::Background);

      target->getComponent<PositionBindComponent>()->entity = eList[eIndex];
      target->getComponent<RenderParentComponent>()->parent = eList[eIndex];



      //cc.reset();
      //cc = std::unique_ptr<CharacterController>(new CharacterController(eList[eIndex]));
      camControl->followEntity(eList[eIndex]);
      camControl2->followEntity(eList[eIndex]);

      setTag(EntityTag::PlayerControlled, eList[eIndex]);
   }

   void onAppStart()
   {
      IOC.resolve<SpriteFactory>()->buildAssetIndex("assets");

      m_frameRate = 60.0f;

      UIScene.reset(new Scene(Float2(100, 100), 1));
      UICamera.reset(new Camera(Rectf(0, 0, 100, 100), UIScene));
      UIViewport.reset(new Viewport(Float2(25, 25), Float2(210, 210), Float2(), UICamera));

      scene.reset(new Scene(Float2(10000, 10000), 10));
      scene->registerEntityManager(std::make_shared<PhysicsManager>());
      scene->registerEntityManager(std::make_shared<CharacterAnimationManager>());
      scene->registerEntityManager(std::make_shared<AIManager>());
      scene->registerEntityManager(std::make_shared<CharacterManager>());
      scene->registerEntityManager(std::make_shared<AttackManager>());
      scene->registerEntityManager(std::make_shared<DamageMarkerManager>());

      camera.reset(new Camera(Rectf(0, 0, 1440, 810), scene));      
      viewport.reset(new Viewport(Float2(), Float2(1440, 810), Float2(), camera));      

      camera2.reset(new Camera(Rectf(0, 0, 150, 150), scene));
      viewport2.reset(new Viewport(Float2(30, 30), Float2(200, 200), Float2(), camera2));


      viewport->addChild(UIViewport);
      UIViewport->addChild(viewport2);

      m_window->addViewport(viewport);
      //m_window->addViewport(UIViewport);
      //m_window->addViewport(viewport2);

      for(int i = 0; i < 1000; ++i)
      {
         auto e = CharacterEntities::buildCharacter();
         e->getComponent<PositionComponent>()->pos = Float2(rand(0, 10000), rand(0, 10000));
         e->addToScene(scene);

         //create hair and all that
         CharacterEntities::buildCharacterChildren(e);

         eList.push_back(e);
      }

      UIEntity = buildUIEntity();
         
      //cc = std::unique_ptr<CharacterController>(new CharacterController(eList[0]));

      camControl.reset(new CameraController(camera, 
         std::unique_ptr<ICameraMoveStrategy>(new MovingCameraMove(50.05f))));
      camControl->setCameraCenter(Float2(0.5f, 0.5f));

      camControl2.reset(new CameraController(camera2, 
         std::unique_ptr<ICameraMoveStrategy>(new BasicCameraMove())));
      camControl2->setCameraCenter(Float2(0.5f, 0.5f));

      cc = std::unique_ptr<CharacterInputHandler>(new CharacterInputHandler());

      

      auto st = IOC.resolve<StringTable>();

      target = std::make_shared<Entity>();
      CompHelpers::addRectangleMeshComponent(*target, Rectf(0, 0, 1, 1), Colorf(1.0f, 1.0f, 1.0f));
      target->addComponent<TextureComponent>(std::make_shared<TextureComponent>(st->get("assets/misc/target/00.png")));
      target->addComponent<GraphicalBoundsComponent>(std::make_shared<GraphicalBoundsComponent>(Float2(150, 150), Float2(0.5f, 0.5f)));
      target->addComponent<PositionComponent>(std::make_shared<PositionComponent>(Float2()));
      target->addComponent<PositionBindComponent>(std::make_shared<PositionBindComponent>(eList[0], Float2()));
      target->addComponent<RenderParentComponent>(std::make_shared<RenderParentComponent>(eList[0]));

      target->addToScene(scene);

      eIndex = -1;
      nextEntity();

      tabEvent = std::move(KeyEvent([&](){this->nextEntity();}));
      IOC.resolve<KeyHandler>()->registerEvent(Keystroke(GLFW_KEY_TAB, GLFW_PRESS, 0), &tabEvent);

      spaceEvent = std::move(KeyEvent([&]()
      {
         if(auto elev = this->eList[eIndex]->getComponent<ElevationComponent>())
         {
            if(elev->elevation == 0.0f)
               elev->impulse = 20.0f;
         }
         
      }));
      //IOC.resolve<KeyHandler>()->registerEvent(Keystroke(GLFW_KEY_SPACE, GLFW_PRESS, 0), &spaceEvent);


      clickEvent = std::move(MouseEvent([&](Float2 pos)
      {
         auto cb = camera->getBounds();
         auto posComp = eList[eIndex]->getComponent<PositionComponent>();

         posComp->pos = pos + Float2(cb.left, cb.top);

      }));

      viewport->registerMouseCallback(Keystroke(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0), &clickEvent);
   
      click2 = std::move(MouseEvent([&](Float2 pos)
      {
         auto cb = camera2->getBounds();
         auto vp = viewport2->getWindowBounds();

         auto posComp = eList[eIndex]->getComponent<PositionComponent>();

         posComp->pos = Float2(pos.x * (cb.width() / vp.width()), pos.y * (cb.height() / vp.height())) + Float2(cb.left, cb.top);
      }));

      viewport2->registerMouseCallback(Keystroke(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0), &click2);
   
   }
   
   void updateVisibleScenes()
   {
      std::unordered_map<std::shared_ptr<IScene>, std::vector<IViewport*>> sceneList;

      for(auto &vp : m_window->getViewports())
         getScenesFromVP(vp.get(), sceneList);

      for(auto &pair : sceneList)
      {
         std::vector<Rectf> visRects;
         for(auto &vp : pair.second)
            visRects.push_back(vp->getCamera()->getBounds());

         pair.first->setVisibleRects(std::move(visRects));
         pair.first->update();  
      }
   }

   void getScenesFromVP(IViewport *vp, std::unordered_map<std::shared_ptr<IScene>, std::vector<IViewport*>> &sceneList)
   {
      auto scene = vp->getCamera()->getScene();
      if(sceneList.find(vp->getCamera()->getScene()) == sceneList.end())
         sceneList[scene] = std::vector<IViewport*>();

      sceneList[scene].push_back(vp);
      
      for(auto &child : vp->getChildren())
         getScenesFromVP(&child, sceneList);
   }

   void updateViewportGraphics(IViewport &vp)
   {
      if(IOC.resolve<RenderManager>()->renderViewport(vp))
         for(auto &child : vp.getChildren())
            updateViewportGraphics(child);
   }

   void onStep()
   {
      updateVisibleScenes();
         
      camControl->updateCamera();
      camControl2->updateCamera();

      for(auto &vp : m_window->getViewports())
      {
         vp->update();
         updateViewportGraphics(*vp);
      }        

      IOC.resolve<RenderManager>()->finalizeRender();      
      m_window->pollEvents(); 
      IOC.resolve<KeyHandler>()->updateKeySteps();
   }
};


std::shared_ptr<Application> getSkyApp()
{
   return std::make_shared<SkyApp>();
}