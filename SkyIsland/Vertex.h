#pragma once

#include "Vector.h"
#include "Color.h"

struct Vertex
{
   Vertex(Float2 _pos, Colorf c):position(_pos), color(c){}
   Float2 position;
   Colorf color;
};