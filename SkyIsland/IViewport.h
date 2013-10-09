#pragma once

#include "ICamera.h"
#include "Rect.h"

class IViewport
{   
public:
   virtual ~IViewport(){}

   virtual ICamera& getCamera()=0;
   virtual Rectf getBounds()=0;


};