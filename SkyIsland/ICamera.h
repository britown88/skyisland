#pragma once

#include "IScene.h"

class ICamera
{
public:
   virtual const IScene& getScene()=0;

   virtual Rectf getBounds()=0;
};