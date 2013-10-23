#pragma once

#include "Vector.h"
#include <algorithm>

template<typename T>
class Rect2
{
public:
   Rect2() : top((T)0), bottom((T)0), left((T)0), right((T)0) {}
   Rect2(T left_in, T top_in, T right_in, T bot_in) : left(left_in), top(top_in), right(right_in), bottom(bot_in) {}
   T top, bottom, left, right;

   T width(){return right - left;}
   T height(){return bottom - top;}

   Rect2<T> operator*(Rect2<T> &rhs)
   {
      return Rect2<T>(rhs.left*left, rhs.top*top, rhs.right*right, rhs.bottom*bottom);
   }

   bool contains(Vector2<T> pos)
   {
      return pos.x >= left && pos.x < right && pos.y >= top && pos.y < bottom;
   }

   bool contains(Rect2<T> rect)
   {
      if (left > rect.right ||
         top > rect.bottom ||
         rect.left > right ||
         rect.top > bottom) return false;
      return true;
   }

   Rect2<T> intersection(Rect2<T> rect)
   {
      return Rect2<T>(
         std::max(left, rect.left),
         std::max(top, rect.top),
         std::min(right, rect.right),
         std::min(bottom, rect.bottom)
         );
   }

   void offset(Vector2<T> offset)
   {
      top += offset.y;
      bottom += offset.y;
      left += offset.x;
      right += offset.x;
   }   
};

typedef Rect2<int> Recti;
typedef Rect2<float> Rectf;