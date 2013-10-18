#pragma once

#include "IEntityManager.h"

class CharacterAnimationManager : public IEntityManager
{
public:
    void updateOnScreenEntity(Entity &e);
    void updateOffScreenEntity(Entity &e);
};