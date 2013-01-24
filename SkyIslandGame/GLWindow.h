#pragma once

#include "singleton.h"
#include <GL/glfw.h>

#include <queue>

class GLWindow : public Singleton<GLWindow>
{
	char *windowTitle;
	bool fullscreen;
	int width, height;

	std::queue<int[2]> keyEvents;
	std::queue<int[2]> charEvents;
	std::queue<int[2]> mousePosEvents;
	std::queue<int[2]> mouseButtonEvents;
	std::queue<int> mouseWheelEvents;
public:
	int init(char *windowTitle);
	int open(int width, int height, bool fullscreen);
	int toggleFullscreen();
	void close();
	bool isOpen();
	void swapBuffers();
	
};

namespace GLFW_CALLBACKS
{
	int GLFWCALL windowCloseCallback();
	void GLFWCALL windowSizeCallback(int width, int height);
	void GLFWCALL windowRefreshCallback();
	void GLFWCALL keyCallback(int key, int action);
	void GLFWCALL charCallback(int character, int action);
	void GLFWCALL mouseButtonCallback(int button, int action);
	void GLFWCALL mousePosCallback(int x, int y);
	void GLFWCALL mouseWheelCallback(int pos);
}

