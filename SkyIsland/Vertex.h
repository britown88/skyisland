#pragma once

#include "Vector.h"

struct Vertex
{
   Vertex(Float2 _pos, float _r, float _g, float _b):position(_pos), r(_r), g(_g), b(_b){}
   Float2 position;
   float r, g, b;
};