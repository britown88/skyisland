#pragma once

#include "Rect.h"
#include "Color.h"
#include "Entity.h"
#include <string>

namespace CompHelpers
{
   void addRectangleMeshComponent(Entity &e, Rectf rect, Colorf color);
   void addRectangleMeshComponent(Entity &e, Rectf rect, Colorf c1, Colorf c2, Colorf c3, Colorf c4);
   Rectf getEntityBounds(Entity& e);
}

