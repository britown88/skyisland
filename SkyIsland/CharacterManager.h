#pragma once

#include "IEntityManager.h"

class CharacterManager : public IEntityManager
{
public:
    void updateOnScreenEntity(Entity &e);
    void updateOffScreenEntity(Entity &e);
};