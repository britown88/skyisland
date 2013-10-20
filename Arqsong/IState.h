#pragma once

#include <string>
#include <vector>

class IState
{
public:
   virtual const std::string &getFilename()=0;//song file
   virtual const std::vector<IState*> &getTransitions()=0;//states this state can transition to
   virtual const std::vector<IState*> &getFriends()=0;//get the states that can play concurrently
   virtual const std::vector<float> &getDimensions()=0;

};