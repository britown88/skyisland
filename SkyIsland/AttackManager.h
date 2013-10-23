#pragma once

#include "IEntityManager.h"

class AttackManager : public IEntityManager
{
public:
    void updateOnScreenEntity(Entity &e);
    void updateOffScreenEntity(Entity &e);
};