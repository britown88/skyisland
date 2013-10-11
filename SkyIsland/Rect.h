#pragma once

#include "Vector.h"

template<typename T>
class Rect2
{
public:
   Rect2() : top((T)0), bottom((T)0), left((T)0), right((T)0) {}
   Rect2(T left_in, T top_in, T right_in, T bot_in) : left(left_in), top(top_in), right(right_in), bottom(bot_in) {}
   T top, bottom, left, right;

   T width(){return right - left;}
   T height(){return bottom - top;}

   bool contains(Vector2<T> pos)
   {
      return pos.x >= left && pos.x < right && pos.y >= top && pos.y < bottom;
   }
};

typedef Rect2<int> Recti;
typedef Rect2<float> Rectf;