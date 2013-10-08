#pragma once

struct GLFWwindow;
struct GLFWmonitor;

#include <string>
#include "Vector.h"
#include <vector>
#include <IViewport.h>
#include <memory>

class GLWindow
{
   typedef std::vector<std::shared_ptr<IViewport> > ViewportList;

   GLFWwindow* m_window;
   Int2 m_windowSize;   
   bool m_fullscreen;

   void registerCallbacks();

   ViewportList m_viewports;

   static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);

public:
   

   GLWindow(Int2 winSize, std::string windowName);
   GLWindow(Int2 winSize, std::string windowName, GLFWmonitor *monitor);
   ~GLWindow();

   void addViewport(std::shared_ptr<IViewport> vPort);
   const ViewportList &getViewports();

   void toggleFullscreen();

   void pollEvents();
   void swapBuffers();
   int shouldClose();

   Int2 getSize();

};