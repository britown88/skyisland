#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "GLWindow.h"
#include "KeyHandler.h"
#include "MouseHandler.h"

#include "IL/il.h"
#include "IL/ilu.h"
#include "IL/ilut.h"
#include "GnUtilities.h"



void GLWindow::registerCallbacks()
{
   glfwSetKeyCallback(m_window, keyCallback);
   glfwSetMouseButtonCallback(m_window, mouseCallback);

   glewInit();

   ilInit();
   iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);

   //glfwSwapInterval(0);
}

GLWindow::GLWindow(Int2 winSize, std::string windowName)
{
   glfwWindowHint( GLFW_VISIBLE, GL_FALSE );
   m_threadWin = glfwCreateWindow( 1, 1, "Thread Window", NULL, NULL );

   glfwWindowHint( GLFW_VISIBLE, GL_TRUE );
   glfwWindowHint(GLFW_RESIZABLE, 0);
   m_window = glfwCreateWindow(winSize.x, winSize.y, windowName.c_str(), NULL, m_threadWin);

   if(!m_window)
      throw ArqException("Window failed to create");

   glfwGetFramebufferSize(m_window, &m_windowSize.x, &m_windowSize.y);
   glfwMakeContextCurrent(m_threadWin);

   m_fullscreen = false;
   registerCallbacks();
}

void GLWindow::makeContextCurrent()
{
   glfwMakeContextCurrent(m_window);
}

GLWindow::GLWindow(Int2 winSize, std::string windowName, GLFWmonitor *monitor)
{
   glfwWindowHint( GLFW_VISIBLE, GL_FALSE );
   m_threadWin = glfwCreateWindow( 1, 1, "Thread Window", NULL, NULL );

   glfwWindowHint( GLFW_VISIBLE, GL_TRUE );
   m_window = glfwCreateWindow(winSize.x, winSize.y, windowName.c_str(), monitor, m_threadWin);

   if(!m_window)
      throw ArqException("Window failed to create");

   glfwGetFramebufferSize(m_window, &m_windowSize.x, &m_windowSize.y);
   glfwMakeContextCurrent(m_threadWin);

   m_fullscreen = true;
   registerCallbacks();
}

GLWindow::~GLWindow()
{
   glfwDestroyWindow(m_threadWin);
   glfwDestroyWindow(m_window);
   glfwTerminate();
   ilShutDown();
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

Float2 GLWindow::getMousePosition()
{
   double x, y;
   glfwGetCursorPos(m_window, &x, &y);

   return Float2(x, y);
}

void GLWindow::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
   IOC.resolve<KeyHandler>()->runEvent(Keystroke(key, action, mode));
}

void GLWindow::mouseCallback(GLFWwindow *window, int button, int action, int mode)
{
   IOC.resolve<MouseHandler>()->runEvent(Keystroke(button, action, mode));
}
