#include "FBODebugger.h"
#include "GLFW/glfw3.h"

FBODebugger::FBODebugger():m_pass(ICamera::Pass::COUNT)
{
   renderFBOs = true;

   registerKeyEvent(Keystroke(GLFW_KEY_F1, INPUT_STEP, 0), KeyEvent([&]()
   {this->m_pass = ICamera::Pass::Lighting;}));

   registerKeyEvent(Keystroke(GLFW_KEY_F1, GLFW_RELEASE, 0), KeyEvent([&]()
   {this->m_pass = ICamera::Pass::COUNT;}));

   registerKeyEvent(Keystroke(GLFW_KEY_F2, INPUT_STEP, 0), KeyEvent([&]()
   {this->renderFBOs = false;}));

   registerKeyEvent(Keystroke(GLFW_KEY_F2, GLFW_RELEASE, 0), KeyEvent([&]()
   {this->renderFBOs = true;}));
}

ICamera::Pass FBODebugger::getPass(){return m_pass;}

void FBODebugger::registerKeyEvent(Keystroke k, KeyEvent e)
{
   m_events.push_back(std::move(e));
   IOC.resolve<KeyHandler>()->registerEvent(k, &m_events[m_events.size()-1]);
}
