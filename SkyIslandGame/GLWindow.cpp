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

		//registerCallback([&](int a, int b){this->keyCallback(a, b);});
		glfwSetKeyCallback(GLFWCallbacks::keyCallback);
		glfwSetCharCallback(GLFWCallbacks::charCallback);
		
		glfwSetMouseButtonCallback(GLFWCallbacks::mouseButtonCallback);
		glfwSetMousePosCallback(GLFWCallbacks::mousePosCallback);
		glfwSetMouseWheelCallback(GLFWCallbacks::mouseWheelCallback);

		glfwSetWindowCloseCallback(GLFWCallbacks::windowCloseCallback);
		glfwSetWindowSizeCallback(GLFWCallbacks::windowSizeCallback);
		glfwSetWindowRefreshCallback(GLFWCallbacks::windowRefreshCallback);	
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

int GLFWCALL GLFWCallbacks::windowCloseCallback(){return GL_TRUE;}
void GLFWCALL GLFWCallbacks::windowSizeCallback(int width, int height){}
void GLFWCALL GLFWCallbacks::windowRefreshCallback(){}
void GLFWCALL GLFWCallbacks::keyCallback(int key, int action){}
void GLFWCALL GLFWCallbacks::charCallback(int character, int action){}
void GLFWCALL GLFWCallbacks::mouseButtonCallback(int button, int action){}
void GLFWCALL GLFWCallbacks::mousePosCallback(int x, int y){}
void GLFWCALL GLFWCallbacks::mouseWheelCallback(int pos){}

