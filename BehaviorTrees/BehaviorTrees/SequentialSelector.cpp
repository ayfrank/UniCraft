#include "SequentialSelector.h"


SequentialSelector::SequentialSelector()
{
}


SequentialSelector::~SequentialSelector()
{
}

bool SequentialSelector::operation()
{
	list<Component*> children = this->getChildren();

	for (auto it = children.begin(); it != children.end(); it++)
		if ((*it)->operation())
			return true;

	return false;
}
