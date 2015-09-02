#include "GoapAction.h"


GoapAction::GoapAction(float cost)
{
	this->cost = cost;
}

GoapAction::~GoapAction()
{
}

float GoapAction::getCost()
{
	return cost;
}

vector<Precondition*> GoapAction::getPreconditions()
{
	return preconditions;
}

bool GoapAction::hasEffect(string effect)
{
	return effects.find(effect) != effects.end();
}

void GoapAction::addPrecondition(Precondition* precondition)
{
	preconditions.push_back(precondition);
}

void GoapAction::addEffect(string effect)
{
	effects.insert(effect);
}

bool GoapAction::canBePopped()
{
	return true;
}