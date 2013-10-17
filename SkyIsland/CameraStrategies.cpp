#include "CameraStrategies.h"

#include "IOCContainer.h"
#include "Application.h"

Float2 BasicCameraMove::moveCamera(Float2 pos, Float2 target)
{
   return target;
}

MovingCameraMove::MovingCameraMove(float speed):m_speed(speed)
{
}

Float2 MovingCameraMove::moveCamera(Float2 pos, Float2 target)
{
   auto app = IOC.resolve<Application>();

   Float2 v = target - pos;
   float dist = sqrtf(v.x*v.x + v.y*v.y);

   if(dist == 0.00f)
      return pos;

   Float2 nv = Float2(v.x / dist, v.y / dist);

   pos.x += nv.x * m_speed * app->dt();
   pos.y += nv.y * m_speed * app->dt();

   if((nv.x > 0 && pos.x > target.x) || (nv.x < 0 && pos.x < target.x)) pos.x = target.x;
   if((nv.y > 0 && pos.y > target.y) || (nv.y < 0 && pos.y < target.y)) pos.y = target.y;

   
   return pos;
}