#pragma once

class GLFWwindow;
class GLFWmonitor;

#include <string>
#include "Vector.h"

class GLWindow
{
   GLFWwindow* m_window;
   Int2 m_windowSize;   
   bool m_fullscreen;

   void registerCallbacks();

public:
   GLWindow(Int2 winSize, std::string windowName);
   GLWindow(Int2 winSize, std::string windowName, GLFWmonitor *monitor);
   ~GLWindow();

   void toggleFullscreen();

   void pollEvents();
   void swapBuffers();
   int shouldClose();

   Int2 getSize();

};