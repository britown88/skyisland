#pragma once

#include "IEntityManager.h"

class DamageMarkerManager : public IEntityManager
{
public:
    void updateOnScreenEntity(Entity &e);
    void updateOffScreenEntity(Entity &e);
};