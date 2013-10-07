#include "Vector.h"
#include "IOCContainer.h"

#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

#include "GLWindow.h"
#include "SkyApp.h"


static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}


int main(void)
{
   auto app = getSkyApp();

   app->start();

   while(true)
   {
      app->step();

      if(!app->isRunning())
      {
         app->terminate();   
         break;
      }
             
   }
    
}