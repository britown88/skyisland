#include <GLFW/glfw3.h>

#include "CharacterInputHandler.h"
#include "CharacterComponent.h"

#include "IOCContainer.h"
#include "Application.h"

#include "PhysicsComponents.h"
#include "GraphicComponents.h"


CharacterInputHandler::CharacterInputHandler()
{
   upPressed = false;
   downPressed = false;
   leftPressed = false;
   rightPressed = false;
   
   registerKeyEvent(Keystroke(GLFW_KEY_D, INPUT_STEP, 0), KeyEvent([&]()
      {this->rightPressed = true; this->sendControllerMovement();}));
   
   registerKeyEvent(Keystroke(GLFW_KEY_D, GLFW_RELEASE, 0), KeyEvent([&]()
      {this->rightPressed = false; this->sendControllerMovement();}));   
   
   registerKeyEvent(Keystroke(GLFW_KEY_A, INPUT_STEP, 0), KeyEvent([&]()
      {this->leftPressed = true; this->sendControllerMovement();}));
   
   registerKeyEvent(Keystroke(GLFW_KEY_A, GLFW_RELEASE, 0), KeyEvent([&]()
      {this->leftPressed = false; this->sendControllerMovement();}));
   
   registerKeyEvent(Keystroke(GLFW_KEY_W, INPUT_STEP, 0), KeyEvent([&]()
      {this->upPressed = true; this->sendControllerMovement();}));
   
   registerKeyEvent(Keystroke(GLFW_KEY_W, GLFW_RELEASE, 0), KeyEvent([&]()
      {this->upPressed = false; this->sendControllerMovement();}));
   
   registerKeyEvent(Keystroke(GLFW_KEY_S, INPUT_STEP, 0), KeyEvent([&]()
      {this->downPressed = true; this->sendControllerMovement();}));
   
   registerKeyEvent(Keystroke(GLFW_KEY_S, GLFW_RELEASE, 0), KeyEvent([&]()
      {this->downPressed = false; this->sendControllerMovement();}));

   registerKeyEvent(Keystroke(GLFW_KEY_SPACE, INPUT_STEP, 0), KeyEvent([&]()
      {this->downPressed = false; this->sendControllerAttack();}));
}

void CharacterInputHandler::registerKeyEvent(Keystroke k, KeyEvent e)
{
   m_events.push_back(std::move(e));
   IOC.resolve<KeyHandler>()->registerEvent(k, &m_events[m_events.size()-1]);
}

void CharacterInputHandler::sendControllerAttack()
{
   if(auto e = IOC.resolve<Application>()->getTag(EntityTag::PlayerControlled))
   if(auto cp = e->getComponent<CharacterComponent>())
   {
      auto &cc = *cp->controller;
      //cc.attack();
   }
}

void CharacterInputHandler::sendControllerMovement()
{
   if(auto e = IOC.resolve<Application>()->getTag(EntityTag::PlayerControlled))
   if(auto cp = e->getComponent<CharacterComponent>())
   {
      Float2 dir;
      dir.x = leftPressed ? -1.0f : rightPressed ? 1.0f : 0.0f;
      dir.y = downPressed ? -1.0f : upPressed ? 1.0f : 0.0f;

      auto &cc = *cp->controller;

      cc.move(dir);

      if(!leftPressed && !rightPressed && !downPressed && !upPressed)
         cc.stop();
   }    
}