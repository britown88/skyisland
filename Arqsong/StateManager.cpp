#include "IStateManager.h"
#include <algorithm>

struct State
{
   State(IState *state):state(state){}
   IState * state;
   bool isFinished(){return true;}
};

template<typename T, typename U>
bool contains(T const &range, U const &value)
{
   auto iter = std::find(begin(range), end(range), value);
   return iter != end(range);
}

class StateManager : public IStateManager
{
   std::vector<State> m_allStates, m_playingStates;
   std::vector<float> m_dimensions;

public:
   //what does this tyhing do?
   //a bunch of shit
   
   StateManager(std::vector<IState*> states, int dimensionCount):
      m_dimensions(dimensionCount, 0.0f)
   {
      for(auto s : states)
         m_allStates.push_back(s);
   }

   void setDimension(int index, float value)
   {
      if(index < m_dimensions.size())
         m_dimensions[index] = value;
   }

   void update()
   {
      //shit will be done here
      //it will blow
      //YOUR
      //MINFG
      for(auto &s : m_playingStates)
      {
         if(s.isFinished())
         {
            std::vector<IState*> trans = s.state->getTransitions();
            auto &friends = s.state->getFriends();

            //remove nonfriends from trans list
            for(size_t i = 0; i < trans.size();)
            {
               bool removed = false;
               for(auto &ps : m_playingStates)
               {
                  if( &ps == &s)
                     continue;

                  if(!contains(friends, ps.state))
                  {                     
                     removed = true;
                     break;
                  }

                  auto &psFriends = ps.state->getFriends();

                  if(!contains(psFriends, trans[i]))
                  {
                     removed = true;
                     break;
                  }
               }

               if(removed)
               {
                  std::swap(trans[i], trans.back());
                  trans.pop_back();
               }
               else
                  ++i;
            }

            //now have valid list of transitions

         }
      }

   }
};