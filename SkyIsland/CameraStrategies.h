#pragma once

#include "ICamera.h"

class BasicCameraMove : public ICameraMoveStrategy
{
public:
   Float2 moveCamera(Float2 pos, Float2 target)
   {
      return target;
   }
};