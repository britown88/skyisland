#include "GLWindow.h"


int GLWindow::init(char *windowTitle)
{
	this->windowTitle = windowTitle;
	return glfwInit();
}

int GLWindow::open(int width, int height, bool fullscreen)
{
	this->fullscreen = fullscreen;
	this->width = width;
	this->height = height;

	//hints msut be set prior to open
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);

	//attempt to open
	int returnVal = glfwOpenWindow(width, height, 5, 6, 5,
		0, 0, 0, fullscreen? GLFW_FULLSCREEN : GLFW_WINDOW);

	//register callbacks and set window title
	if(returnVal == GL_TRUE)
	{
		glfwSetWindowTitle(windowTitle);		

		glfwSetCharCallback(GLFW_CALLBACKS::charCallback);
		glfwSetKeyCallback(GLFW_CALLBACKS::keyCallback);
		glfwSetMouseButtonCallback(GLFW_CALLBACKS::mouseButtonCallback);
		glfwSetMousePosCallback(GLFW_CALLBACKS::mousePosCallback);
		glfwSetMouseWheelCallback(GLFW_CALLBACKS::mouseWheelCallback);

		glfwSetWindowCloseCallback(GLFW_CALLBACKS::windowCloseCallback);
		glfwSetWindowSizeCallback(GLFW_CALLBACKS::windowSizeCallback);
		glfwSetWindowRefreshCallback(GLFW_CALLBACKS::windowRefreshCallback);	
	
	}

	return returnVal;
}
bool GLWindow::isOpen(){return glfwGetWindowParam(GLFW_OPENED) == GL_TRUE;}
void GLWindow::swapBuffers() {glfwSwapBuffers();}

int GLWindow::toggleFullscreen()
{
	glfwCloseWindow();
	return open(width, height, !fullscreen);
}

void GLWindow::close()
{
	glfwTerminate();
}

//callbacks
namespace GLFW_CALLBACKS
{
	int GLFWCALL windowCloseCallback(){return GL_TRUE;}
	void GLFWCALL windowSizeCallback(int width, int height){}
	void GLFWCALL windowRefreshCallback(){}
	void GLFWCALL keyCallback(int key, int action){}
	void GLFWCALL charCallback(int character, int action){}
	void GLFWCALL mouseButtonCallback(int button, int action){}
	void GLFWCALL mousePosCallback(int x, int y){}
	void GLFWCALL mouseWheelCallback(int pos){}
}
