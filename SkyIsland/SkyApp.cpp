#include <GLFW/glfw3.h>
#include "SkyApp.h"
#include "Viewport.h"
#include "Camera.h"
#include "Scene.h"
#include "RenderManager.h"

#include "MeshComponent.h"
#include "PositionComponent.h"
#include "RotationComponent.h"
#include "PhysicsComponents.h"
#include "GraphicComponents.h"
#include "Physics.h"

#include "IKeyEvent.h"
#include "KeyHandler.h"

#include "CharacterController.h"
#include "CameraController.h"
#include "CameraStrategies.h"


class SkyApp : public Application
{
   std::string getWindowTitle()
   {
      return "Square Island Gaem";
   }

   Int2 getWindowSize()
   {
      return Int2(1440, 810);
   }

   //GLFWmonitor *getWindowMonitor()
   //{
   //   return glfwGetPrimaryMonitor();
   //}

   std::shared_ptr<Scene> scene, UIScene;
   std::shared_ptr<Camera> camera, camera2, UICamera;
   std::unique_ptr<CharacterController> cc;
   std::shared_ptr<Viewport> viewport, viewport2, UIViewport;
   std::unique_ptr<CameraController> camControl, camControl2;
   std::vector<std::shared_ptr<Entity>> eList;
   std::shared_ptr<Entity> UIEntity;

   int eIndex;

   std::shared_ptr<Entity> buildBlockEntity(Float2 position, Float2 size)
   {
      auto e = std::make_shared<Entity>();

      std::vector<Vertex> vertices;
      std::vector<int> indices;

      vertices.push_back(Vertex(Float2(0.0, 0.0f), 1.0f, 0.0f, 0.0f));
      vertices.push_back(Vertex(Float2(size.x, 0.0f), 1.0f, 0.0f, 0.0f));
      vertices.push_back(Vertex(Float2(size.x, size.y), 1.0f, 1.0f, 1.0f));
      vertices.push_back(Vertex(Float2(0.0f, size.y), 1.0f, 1.0f, 1.0f));

      indices.push_back(0);indices.push_back(1);indices.push_back(3);
      indices.push_back(1);indices.push_back(3);indices.push_back(2);

      e->addComponent<MeshComponent>(new MeshComponent(vertices, indices));
      e->addComponent<GraphicalBoundsComponent>(new GraphicalBoundsComponent(size));
      e->addComponent<IPositionComponent>(new PositionComponent(position));
      e->addComponent<VelocityComponent>(new VelocityComponent(Float2(0.0f, 0.0f)));
      e->addComponent<FrictionComponent>(new FrictionComponent(0.0f));
      e->addComponent<AccelerationComponent>(new AccelerationComponent(0.0f, 0.0f, 25.0f));
      //test.addComponent<RotationComponent>(new RotationComponent(90.0f, Float2(50.0f, 50.0f)));

      scene->addEntity(*e);

      return e;
   }

   std::shared_ptr<Entity> buildUIEntity()
   {
      auto e = std::make_shared<Entity>();

      std::vector<Vertex> vertices;
      std::vector<int> indices;

      vertices.push_back(Vertex(Float2(0.0, 0.0f), 1.0f, 1.0f, 1.0f));
      vertices.push_back(Vertex(Float2(100.0f, 0.0f), 1.0f, 1.0f, 1.0f));
      vertices.push_back(Vertex(Float2(100.0f, 100.0f), 1.0f, 1.0f, 1.0f));
      vertices.push_back(Vertex(Float2(0.0f, 100.0f), 1.0f, 1.0f, 1.0f));

      indices.push_back(0);indices.push_back(1);indices.push_back(3);
      indices.push_back(1);indices.push_back(3);indices.push_back(2);

      e->addComponent<MeshComponent>(new MeshComponent(vertices, indices));
      e->addComponent<IPositionComponent>(new PositionComponent(Float2()));
      UIScene->addEntity(*e);

      return e;
   }

   void nextEntity()
   {
      if(eIndex >= 0)
      {
         auto &m = eList[eIndex]->getComponent<MeshComponent>();
         m.vertices()[0].r = 1.0f; m.vertices()[0].g = 0.0f;
         m.vertices()[1].r = 1.0f; m.vertices()[1].g = 0.0f;

         eList[eIndex]->getComponent<FrictionComponent>().friction = 10.0f;
         eList[eIndex]->getComponent<AccelerationComponent>().acceleration = 0.0f;
      }
      

      ++eIndex;
      if(eIndex >= eList.size())
         eIndex = 0;

      auto &m = eList[eIndex]->getComponent<MeshComponent>();
      m.vertices()[0].r = 0.0f; m.vertices()[0].g = 1.0f;
      m.vertices()[1].r = 0.0f; m.vertices()[1].g = 1.0f;

      cc.reset();
      cc = std::unique_ptr<CharacterController>(new CharacterController(eList[eIndex]));
      camControl->followEntity(eList[eIndex]);
      camControl2->followEntity(eList[eIndex]);
   }

   void onAppStart()
   {
      m_frameRate = 60.0f;

      UIScene.reset(new Scene(Float2(100, 100)));
      UICamera.reset(new Camera(Rectf(0, 0, 100, 100), UIScene));
      UIViewport.reset(new Viewport(Rectf(25, 25, 210, 210), UICamera));

      scene.reset(new Scene(Float2(10000, 10000)));
      camera.reset(new Camera(Rectf(0, 0, 1440, 810), scene));      
      viewport.reset(new Viewport(Rectf(0, 0, 1440, 810), camera));

      camera2.reset(new Camera(Rectf(0, 0, 700, 700), scene));
      viewport2.reset(new Viewport(Rectf(30, 30, 200, 200), camera2));

      m_window->addViewport(viewport);
      m_window->addViewport(UIViewport);
      m_window->addViewport(viewport2);

      for(int i = 0; i < 100; ++i)
      {
         int s = rand(50, 500);
         eList.push_back(buildBlockEntity(Float2(rand(0, 10000), rand(0, 10000)), Float2(s, s)));
      }

      UIEntity = buildUIEntity();

      
         
      //cc = std::unique_ptr<CharacterController>(new CharacterController(eList[0]));

      camControl.reset(new CameraController(camera, 
         std::unique_ptr<ICameraMoveStrategy>(new MovingCameraMove(50.05f))));
      camControl->setCameraCenter(Float2(0.5f, 0.5f));

      camControl2.reset(new CameraController(camera2, 
         std::unique_ptr<ICameraMoveStrategy>(new BasicCameraMove())));
      camControl2->setCameraCenter(Float2(0.5f, 0.5f));

      eIndex = -1;
      nextEntity();



      IOC.resolve<KeyHandler>().registerEvent(Keystroke(GLFW_KEY_TAB, GLFW_PRESS, 0), [&](){this->nextEntity();});

      //auto left = std::unique_ptr<IKeyEvent>(new MoveEntityRight(test));
      //IOC.resolve<KeyHandler>().registerEvent(Keystroke(GLFW_KEY_RIGHT, GLFW_PRESS, 0), std::move(left));
   }

   void updateViewportPhysics(IViewport &vp)
   {
      Physics::updateWorldPhsyics((IScene&)vp.getCamera()->getScene(), vp.getCamera()->getBounds());
      
      for(auto &child : vp.getChildren())
         updateViewportPhysics(child);
   }

   void updateViewportGraphics(IViewport &vp)
   {
      IOC.resolve<RenderManager>().renderViewport(vp);

      for(auto &child : vp.getChildren())
         updateViewportGraphics(child);
   }

   void onStep()
   {
      auto vps = m_window->getViewports();
      auto &rm = IOC.resolve<RenderManager>();

      for(auto &vp : vps)
         updateViewportPhysics(*vp);
         
      camControl->updateCamera();
      camControl2->updateCamera();

      for(auto &vp : vps)
         updateViewportGraphics(*vp);

      rm.finalizeRender();
      m_window->swapBuffers();

      
      m_window->pollEvents();
      
   }

};


std::unique_ptr<Application> getSkyApp()
{
   return std::unique_ptr<Application>(new SkyApp());
}