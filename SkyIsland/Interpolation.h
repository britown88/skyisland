#pragma once


float LinearInterpolate(const float var1, const float var2, float delta)
{
   return (var2 - var1) * delta;
}