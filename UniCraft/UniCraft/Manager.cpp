#include "Manager.h"



Manager::Manager(Strategy* strategy)
{
	this->strategy = strategy;
}


Manager::~Manager()
{
}

void Manager::performActionsOfThisStep()
{
	//TODO
}

