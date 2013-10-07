#include <GLFW/glfw3.h>
#include "SkyApp.h"

class SkyApp : public Application
{
   void onStep()
   {
      float ratio;
      int width, height;
      Int2 winSize = m_window->getSize();
      width = winSize.x;
      height = winSize.y;
      ratio = width / (float) height;
      glViewport(0, 0, width, height);
      glClear(GL_COLOR_BUFFER_BIT);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glPushMatrix();
      glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
      glBegin(GL_TRIANGLES);
      glColor3f(1.f, 0.f, 0.f);
      glVertex3f(-0.6f, -0.4f, 0.f);
      glColor3f(0.f, 1.f, 0.f);
      glVertex3f(0.6f, -0.4f, 0.f);
      glColor3f(0.f, 0.f, 1.f);
      glVertex3f(0.f, 0.6f, 0.f);
      glEnd();
      glPopMatrix();
      m_window->swapBuffers();
      m_window->pollEvents();
      
   }

};


std::unique_ptr<Application> getSkyApp()
{
   return std::unique_ptr<Application>(new SkyApp());
}