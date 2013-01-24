#pragma once

#include <set>

class FSMNode
{
public:
	virtual void onEnter(FSMNode*prevState) {}
	virtual void onExit(FSMNode*nextState) {}
	virtual void onUpdate() {}
};

class FSM
{
	std::set<FSMNode*> nodes;
	FSMNode* activeNode;

public:
	FSM():activeNode(nullptr){}

	void changeState(FSMNode* state);
	void update();

};

//==========Inherit new nodes here======
class MainGameState:public FSMNode
{
public:
	void update();
};