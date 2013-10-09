#pragma once

#include "ICamera.h"

class BasicCameraMove : public ICameraMoveStrategy
{
public:
   Float2 moveCamera(Float2 pos, Float2 target);
};

class MovingCameraMove : public ICameraMoveStrategy
{
   Float2 m_velocity;
   float m_speed;
   double m_lastUpdated;
public:
   MovingCameraMove(float speed);

   Float2 moveCamera(Float2 pos, Float2 target);
};