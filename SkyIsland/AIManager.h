#pragma once

#include "IEntityManager.h"

class AIManager : public IEntityManager
{
public:
    void updateOnScreenEntity(Entity &e);
    void updateOffScreenEntity(Entity &e);
};