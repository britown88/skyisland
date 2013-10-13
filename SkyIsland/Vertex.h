#pragma once

#include "Vector.h"
#include "Color.h"

struct Vertex
{
   Vertex(Float2 _pos, Colorf c):position(_pos), color(c), texCoords(Float2()){}
   Vertex(Float2 _pos, Float2 _tex, Colorf c):position(_pos), color(c), texCoords(_tex){}
   Float2 position, texCoords;
   Colorf color;
};