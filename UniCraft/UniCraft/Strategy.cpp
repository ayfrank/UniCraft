#include "Strategy.h"


Strategy::Strategy()
{
}


Strategy::~Strategy()
{
}

void Strategy::performActionsOfThisStep()
{
	for (auto it = tactics.begin(); it != tactics.end(); it++)
		(*it)->execute();
}

void Strategy::addTactic(Tactic* tactic)
{
	tactics.push_back(tactic);
}