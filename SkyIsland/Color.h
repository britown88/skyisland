#pragma once

template<typename T>
class Color
{
public:
   T a, r, g, b;
   Color(T a, T r, T g, T b):a(a), r(r), g(g), b(b){}
   Color(T r, T g, T b):a((T)1), r(r), g(g), b(b){}
   Color():a((T)1), r((T)0), g((T)0), b((T)0){}
};

typedef Color<float> Colorf;