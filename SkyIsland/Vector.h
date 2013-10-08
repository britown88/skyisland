#pragma once


template <typename T>
class Vector2
{
public:
   Vector2() : x((T)0), y((T)0) {}
   Vector2(T x_in, T y_in) : x(x_in), y(y_in) {}
   T x,y;

   Vector2<T> operator+(const Vector2<T> &rhs)
   {
      return Vector2<T>(x+rhs.x, y+rhs.y);
   }
};

typedef Vector2<float> Float2;
typedef Vector2<int> Int2;

