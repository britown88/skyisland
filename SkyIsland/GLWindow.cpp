#include <GLFW/glfw3.h>
#include "GLWindow.h"
#include "KeyHandler.h"

void GLWindow::registerCallbacks()
{
   glfwSetKeyCallback(m_window, keyCallback);
}

GLWindow::GLWindow(Int2 winSize, std::string windowName)
{
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

void GLWindow::addViewport(std::shared_ptr<IViewport> vPort)
{
   m_viewports.push_back(std::move(vPort));
}
const GLWindow::ViewportList &GLWindow::getViewports()
{
   return m_viewports;
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

void GLWindow::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
   IOC.resolve<KeyHandler>().runEvent(Keystroke(key, action, mode));
}