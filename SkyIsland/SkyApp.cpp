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
#include "AIManager.h"
#include "AIComponent.h"

#include "IKeyEvent.h"
#include "KeyHandler.h"
#include "MouseHandler.h"

#include "CharacterController.h"
#include "CharacterInputHandler.h"
#include "CameraController.h"
#include "CameraStrategies.h"

#include "ComponentHelpers.h"
#include "CharacterAnimationStrategy.h"

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
   std::shared_ptr<Entity> UIEntity;

   int eIndex;

   KeyEvent tabEvent, spaceEvent;
   MouseEvent clickEvent, click2;

   std::shared_ptr<Entity> buildBlockEntity(Float2 position, Float2 size)
   {
      auto e = std::make_shared<Entity>();
      auto st = IOC.resolve<StringTable>();
      
      CompHelpers::addRectangleMeshComponent(*e, Rectf(0, 0, 1, 1), Colorf(1.0f, 1.0f, 1.0f));

      e->addComponent<TextureComponent>(std::make_shared<TextureComponent>(st->get("")));
      e->addComponent<GraphicalBoundsComponent>(std::make_shared<GraphicalBoundsComponent>(size, Float2(0.5f, 0.5f)));
      e->addComponent<PositionComponent>(std::make_shared<PositionComponent>(position));
      e->addComponent<VelocityComponent>(std::make_shared<VelocityComponent>(Float2(0.0f, 0.0f)));
      e->addComponent<FrictionComponent>(std::make_shared<FrictionComponent>(0.0f));
      e->addComponent<AccelerationComponent>(std::make_shared<AccelerationComponent>(Float2(), 0.0f, 10.0f));
      e->addComponent<ElevationComponent>(std::make_shared<ElevationComponent>(1.0f));
      e->addComponent<CharacterComponent>(std::make_shared<CharacterComponent>(e));
     
      e->addComponent<AIComponent>(std::make_shared<AIComponent>(e));
      e->addComponent<WanderComponent>(std::make_shared<WanderComponent>());
      //test.addComponent<RotationComponent>(std::make_shared<RotationComponent>(90.0f, Float2(50.0f, 50.0f)));

      

      CharacterAnimationStrategy animStrat;
      auto sprite = IOC.resolve<SpriteFactory>()->buildSprite(st->get("assets/guy"), animStrat);

      e->addComponent<SpriteComponent>(std::make_shared<SpriteComponent>(std::move(sprite), st->get("stand_down")));
      
      scene->addEntity(e);

      return e;
   }

   std::shared_ptr<Entity> buildUIEntity()
   {
      auto e = std::make_shared<Entity>();

      CompHelpers::addRectangleMeshComponent(*e, Rectf(0, 0, 100, 100), Colorf(1.0f, 1.0f, 1.0f));
      e->addComponent<PositionComponent>(std::make_shared<PositionComponent>(Float2()));
      UIScene->addEntity(e);

      return e;
   }

   void nextEntity()
   {
      //add the AI back in
      if(eIndex >= 0)
         eList[eIndex]->addComponent<AIComponent>(std::make_shared<AIComponent>(eList[eIndex]));

      ++eIndex;
      if(eIndex >= eList.size())
         eIndex = 0;

      //remove the AI and stop moving
      eList[eIndex]->removeComponent<AIComponent>();
      eList[eIndex]->getComponent<CharacterComponent>()->controller->stop();



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


      camera.reset(new Camera(Rectf(0, 0, 1440, 810), scene));      
      viewport.reset(new Viewport(Float2(), Float2(1440, 810), Float2(), camera));      

      camera2.reset(new Camera(Rectf(0, 0, 700, 700), scene));
      viewport2.reset(new Viewport(Float2(30, 30), Float2(200, 200), Float2(), camera2));

      viewport->addChild(UIViewport);
      UIViewport->addChild(viewport2);

      m_window->addViewport(viewport);
      //m_window->addViewport(UIViewport);
      //m_window->addViewport(viewport2);

      for(int i = 0; i < 500; ++i)
      {
         int s = rand(50, 500);
         eList.push_back(buildBlockEntity(Float2(rand(0, 10000), rand(0, 10000)), Float2(150, 150)));
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
   }
};


std::shared_ptr<Application> getSkyApp()
{
   return std::make_shared<SkyApp>();
}