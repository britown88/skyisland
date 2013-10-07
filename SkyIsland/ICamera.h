#pragma once

#include "IScene.h"

class ICamera
{
public:
   virtual ~ICamera(){}
   virtual const IScene& getScene() const=0;

   virtual const Rectf getBounds() const=0;
};