#include <GLFW/glfw3.h>
#include "SkyApp.h"
#include "Viewport.h"
#include "Camera.h"
#include "Scene.h"
#include "RenderManager.h"

#include "MeshComponent.h"
#include "PositionComponent.h"
#include "RotationComponent.h"

#include "IKeyEvent.h"
#include "KeyHandler.h"

class MoveEntityRight : public IKeyEvent
{
   Entity &m_entity;
public:

   MoveEntityRight(Entity &e):m_entity(e){}

   void run()
   {
      auto &p = m_entity.getComponent<IPositionComponent>();

      p.setPosition(p.getPosition() + Float2(3.0f, 0.0f));
   }

};


class SkyApp : public Application
{
   std::string getWindowTitle()
   {
      return "Skuy Island Gaem";
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
   std::unique_ptr<Camera> camera;
   std::shared_ptr<Viewport> viewport;

   Entity test;

   void onAppStart()
   {
      scene.reset(new Scene(Float2(800, 600)));
      camera.reset(new Camera(Rectf(0, 0, 80, 60), *scene));
      viewport.reset(new Viewport(Rectf(0, 0, 800, 600), *camera));

      m_window->addViewport(viewport);

      std::vector<Vertex> vertices;
      std::vector<int> indices;

      vertices.push_back(Vertex(Float2(0.0, 0.0f), 1.0f, 0.0f, 0.0f));
      vertices.push_back(Vertex(Float2(100.0f, 0.0f), 0.f, 1.f, 0.f));
      vertices.push_back(Vertex(Float2(50.0f, 100.0f), 0.f, 0.f, 1.f));

      indices.push_back(0);
      indices.push_back(1);
      indices.push_back(2);

      test.addComponent<MeshComponent>(new MeshComponent(vertices, indices));
      test.addComponent<IPositionComponent>(new PositionComponent(Float2()));
      //test.addComponent<RotationComponent>(new RotationComponent(45.0f, Float2(50.0f, 50.0f)));

      scene->addEntity(test);

      auto left = std::unique_ptr<IKeyEvent>(new MoveEntityRight(test));
      IOC.resolve<KeyHandler>().registerEvent(Keystroke(GLFW_KEY_RIGHT, GLFW_PRESS, 0), std::move(left));
   }

   void onStep()
   {
      IOC.resolve<RenderManager>().render();

      m_window->pollEvents();
      
   }

};


std::unique_ptr<Application> getSkyApp()
{
   return std::unique_ptr<Application>(new SkyApp());
}