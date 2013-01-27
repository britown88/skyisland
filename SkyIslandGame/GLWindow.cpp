#include "GLWindow.h"
#include <functional>
#include <vector>

#include "singleton.h"

typedef std::function< void GLFWCALL(int, int)> GLFWKeyCallback;

class CallbackForwarder : public Singleton<CallbackForwarder>
{
	std::vector<GLFWKeyCallback> callbacks;
public:
	void forward(int arg1, int arg2)
	{
		for (auto & callback : callbacks)
			callback(arg1, arg2);

	}
	void registerCallback(GLFWKeyCallback callback)
	{
		callbacks.push_back(callback);
	}
};

void forwardCallbacks(int arg1, int arg2)
{
	CallbackForwarder::instance().forward(arg1, arg2); 
}

void registerCallback(GLFWKeyCallback callback)
{
	CallbackForwarder::instance().registerCallback(callback);
}


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

		registerCallback([&](int a, int b){this->keyCallback(a, b);});
		glfwSetKeyCallback(&forwardCallbacks);



		/*glfwSetCharCallback(this->charCallback);
		
		glfwSetMouseButtonCallback(this->mouseButtonCallback);
		glfwSetMousePosCallback(this->mousePosCallback);
		glfwSetMouseWheelCallback(this->mouseWheelCallback);

		glfwSetWindowCloseCallback(this->windowCloseCallback);
		glfwSetWindowSizeCallback(this->windowSizeCallback);
		glfwSetWindowRefreshCallback(this->windowRefreshCallback);	
	*/
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

int GLFWCALL GLWindow::windowCloseCallback(){return GL_TRUE;}
void GLFWCALL GLWindow::windowSizeCallback(int width, int height){}
void GLFWCALL GLWindow::windowRefreshCallback(){}
void GLFWCALL GLWindow::keyCallback(int key, int action){}
void GLFWCALL GLWindow::charCallback(int character, int action){}
void GLFWCALL GLWindow::mouseButtonCallback(int button, int action){}
void GLFWCALL GLWindow::mousePosCallback(int x, int y){}
void GLFWCALL GLWindow::mouseWheelCallback(int pos){}

