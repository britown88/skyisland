#pragma once

#include "IScene.h"

class ICamera
{
public:
   virtual ~ICamera(){}
   virtual std::shared_ptr<IScene> getScene()=0;

   virtual Rectf getBounds()=0;
   virtual void setBounds(Rectf bounds)=0;
};

class ICameraMoveStrategy
{
public:
   virtual Float2 moveCamera(Float2 pos, Float2 target)=0;

};