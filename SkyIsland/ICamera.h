#pragma once

#include "IScene.h"
#include "FBO.h"
#include <unordered_map>

class ICamera
{
public:
   enum class Pass
   {
      Lighting,
      COUNT
   };

   virtual std::unordered_map<Pass, std::shared_ptr<FBO>> &getFBOs()=0;
   virtual void addFBOPass(Pass passs)=0;

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