#pragma once
#include "IStateManager.h"

#include <memory>

class IStateManagerFactory
{
public:
   virtual std::unique_ptr<IStateManager> buildStateManager(std::vector<IState*> states)=0;
};