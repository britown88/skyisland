#include <GLFW/glfw3.h>
#include "SkyApp.h"
#include "Viewport.h"
#include "Camera.h"
#include "Scene.h"
#include "RenderManager.h"

#include "GraphicsComponent.h"
#include "PositionComponent.h"
#include "SkyTriangle.h"


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
      camera.reset(new Camera(Rectf(0, 0, 800, 600), *scene));
      viewport.reset(new Viewport(Rectf(0, 0, 800, 600), *camera));

      m_window->addViewport(viewport);

      test.addComponent<GraphicsComponent>(new GraphicsComponent(std::shared_ptr<IRenderable>(new SkyTriangle())));
      test.addComponent<PositionComponent>(new PositionComponent(Float2()));

      scene->addEntity(test);

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