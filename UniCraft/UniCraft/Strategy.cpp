#include "Strategy.h"


Strategy::Strategy()
{
}


Strategy::~Strategy()
{
}

void Strategy::executeActionOfThisStep()
{
	for (auto it = tactics.begin(); it != tactics.end(); it++)
		(*it)->execute();
}

void Strategy::addTactic(Tactic* tactic)
{
	tactics.push_back(tactic);
}