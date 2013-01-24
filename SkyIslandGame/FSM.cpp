#include "FSM.h"

void FSM::changeState(FSMNode* state)
{
	auto nextState = nodes.find(state);

	if(nextState != nodes.end())
	{
		FSMNode *next = *nextState;
		if(next == activeNode) return;

		if(activeNode) activeNode->onExit(next);		
		next->onEnter(activeNode);

		activeNode = next;
	}
}

void FSM::update()
{
	if(activeNode)
		activeNode->onUpdate();
}


void MainGameState::update()
{
}

