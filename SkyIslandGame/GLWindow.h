#pragma once

#include "singleton.h"
#include <GL/glfw.h>


class GLWindow : public Singleton<GLWindow>
{
	char *windowTitle;
	bool fullscreen;
	int width, height;

public:
	int init(char *windowTitle);
	int open(int width, int height, bool fullscreen);
	int toggleFullscreen();
	void close();
	bool isOpen();
	void swapBuffers();

	
	
};

namespace GLFWCallbacks
{
	void GLFWCALL keyCallback(int key, int action);
	int GLFWCALL windowCloseCallback();
	void GLFWCALL windowSizeCallback(int width, int height);
	void GLFWCALL windowRefreshCallback();
	void GLFWCALL charCallback(int character, int action);
	void GLFWCALL mouseButtonCallback(int button, int action);
	void GLFWCALL mousePosCallback(int x, int y);
	void GLFWCALL mouseWheelCallback(int pos);
}
