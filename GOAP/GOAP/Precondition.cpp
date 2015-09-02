#include "Precondition.h"


Precondition::Precondition(string name)
{
	this->name = name;
}


Precondition::~Precondition()
{
}

string Precondition::getName()
{
	return name;
}