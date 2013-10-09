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

   //Int2 getWindowSize()
   //{
   //   return Int2(1920, 1080);
   //}

   //GLFWmonitor *getWindowMonitor()
   //{
   //   return glfwGetPrimaryMonitor();
   //}

   std::unique_ptr<Scene> scene;
   std::shared_ptr<Camera> camera, camera2;

   std::unique_ptr<CharacterController> cc;

   std::shared_ptr<Viewport> viewport, viewport2;

   std::shared_ptr<Entity> test;

   std::unique_ptr<CameraController> camControl;

   void onAppStart()
   {
      scene.reset(new Scene(Float2(800, 600)));
      camera.reset(new Camera(Rectf(0, 0, 1600, 1200), *scene));
      camera2.reset(new Camera(Rectf(0, 0, 160, 120), *scene));
      viewport.reset(new Viewport(Rectf(0, 0, 800, 600), *camera));
      viewport2.reset(new Viewport(Rectf(0, 0, 160, 120), *camera2));

      m_window->addViewport(viewport);
      m_window->addViewport(viewport2);

      std::vector<Vertex> vertices;
      std::vector<int> indices;

      vertices.push_back(Vertex(Float2(0.0, 0.0f), 1.0f, 0.0f, 0.0f));
      vertices.push_back(Vertex(Float2(100.0f, 0.0f), 1.0f, 0.0f, 0.0f));
      vertices.push_back(Vertex(Float2(100.0f, 100.0f), 1.0f, 1.0f, 1.0f));
      vertices.push_back(Vertex(Float2(0.0f, 100.0f), 1.0f, 1.0f, 1.0f));

      indices.push_back(0);indices.push_back(1);indices.push_back(3);
      indices.push_back(1);indices.push_back(3);indices.push_back(2);


      test = std::make_shared<Entity>();
      test->addComponent<MeshComponent>(new MeshComponent(vertices, indices));
      test->addComponent<GraphicalBoundsComponent>(new GraphicalBoundsComponent(Float2(100.0f, 100.0f)));
      test->addComponent<IPositionComponent>(new PositionComponent(Float2()));
      test->addComponent<VelocityComponent>(new VelocityComponent(Float2(0.0f, 0.0f)));
      test->addComponent<FrictionComponent>(new FrictionComponent(0.0f));
      test->addComponent<AccelerationComponent>(new AccelerationComponent(0.0f, 0.0f, 10.0f));
      //test.addComponent<RotationComponent>(new RotationComponent(90.0f, Float2(50.0f, 50.0f)));

      scene->addEntity(*test);

      cc = std::unique_ptr<CharacterController>(new CharacterController(test));

      camControl.reset(new CameraController(
         camera2, 
         std::unique_ptr<ICameraMoveStrategy>(new BasicCameraMove())));

      camControl->setCameraCenter(Float2(0.5f, 0.5f));
      camControl->followEntity(test);


      //IOC.resolve<KeyHandler>().registerEvent(Keystroke(GLFW_KEY_RIGHT, GLFW_PRESS, 0), [&](){this->onStep();});

      //auto left = std::unique_ptr<IKeyEvent>(new MoveEntityRight(test));
      //IOC.resolve<KeyHandler>().registerEvent(Keystroke(GLFW_KEY_RIGHT, GLFW_PRESS, 0), std::move(left));
   }

   void onStep()
   {
      auto vps = m_window->getViewports();
      auto &rm = IOC.resolve<RenderManager>();

      for(auto vp : vps)
         Physics::updateWorldPhsyics((IScene&)vp->getCamera().getScene(), vp->getCamera().getBounds());
      
      camControl->updateCamera();

      for(auto vp : vps)
         rm.renderViewport(*vp);


      rm.finalizeRender();
      m_window->swapBuffers();

      
      m_window->pollEvents();
      
   }

};


std::unique_ptr<Application> getSkyApp()
{
   return std::unique_ptr<Application>(new SkyApp());
}