#pragma once

#include "IScene.h"
#include "Rect.h"

static class Physics
{


public:

   static void updateWorldPhsyics(IScene &world, Rectf viewBounds);
};