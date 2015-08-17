#include "TacticAction.h"


TacticAction::TacticAction(Tactic* tactic, Strategy* behaviorTrees)
{
	this->tactic = tactic;
	this->behaviorTrees = behaviorTrees;
}


TacticAction::~TacticAction()
{
}

bool TacticAction::operation()
{
	behaviorTrees->addTactic(tactic);
	return true;
}