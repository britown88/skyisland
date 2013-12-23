#pragma once

struct GLFWwindow;
struct GLFWmonitor;

#include <string>
#include "Vector.h"
#include <vector>
#include "IViewport.h"
#include <memory>

class GLWindow
{


   typedef std::vector<std::shared_ptr<IViewport> > ViewportList;

   GLFWwindow* m_window, *m_threadWin;
   Int2 m_windowSize;
   bool m_fullscreen;

   void registerCallbacks();

   ViewportList m_viewports;

   static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
   static void mouseCallback(GLFWwindow *window, int button, int action, int mode);

public:
   static const unsigned int ID = 3006192257;

   GLWindow(Int2 winSize, std::string windowName);
   GLWindow(Int2 winSize, std::string windowName, GLFWmonitor *monitor);
   ~GLWindow();

   void addViewport(std::shared_ptr<IViewport> vPort);
   const ViewportList &getViewports();

   void toggleFullscreen();

   void makeContextCurrent();

   void pollEvents();
   void swapBuffers();
   int shouldClose();

   Int2 getSize();
   Float2 getMousePosition();

};
