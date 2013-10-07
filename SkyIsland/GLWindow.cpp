#include <GLFW/glfw3.h>
#include "GLWindow.h"

void GLWindow::registerCallbacks()
{
}

GLWindow::GLWindow(Int2 winSize, std::string windowName)
{
   if(!glfwInit())
      throw std::exception("GLFW Failed to initialize");

   glfwWindowHint(GLFW_RESIZABLE, 0);
   m_window = glfwCreateWindow(winSize.x, winSize.y, windowName.c_str(), NULL, NULL);

   if(!m_window)
      throw std::exception("Window failed to create");

   glfwGetFramebufferSize(m_window, &m_windowSize.x, &m_windowSize.y);
   glfwMakeContextCurrent(m_window);

   m_fullscreen = false;
   registerCallbacks();
}

GLWindow::GLWindow(Int2 winSize, std::string windowName, GLFWmonitor *monitor)
{
   if(!glfwInit())
      throw std::exception("GLFW Failed to initialize");

   m_window = glfwCreateWindow(winSize.x, winSize.y, windowName.c_str(), monitor, NULL);

   if(!m_window)
      throw std::exception("Window failed to create");

   glfwGetFramebufferSize(m_window, &m_windowSize.x, &m_windowSize.y);
   glfwMakeContextCurrent(m_window);

   m_fullscreen = true;
   registerCallbacks();
}

GLWindow::~GLWindow()
{
   glfwDestroyWindow(m_window);
   glfwTerminate();
}

void GLWindow::pollEvents()
{
   glfwPollEvents();
}

void GLWindow::swapBuffers()
{
   glfwSwapBuffers(m_window);
}

int GLWindow::shouldClose()
{
   return glfwWindowShouldClose(m_window);
}

void GLWindow::toggleFullscreen()
{

}

Int2 GLWindow::getSize()
{
   return m_windowSize;
}