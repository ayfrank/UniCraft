#include "Sequence.h"


Sequence::Sequence()
{
}


Sequence::~Sequence()
{
}

bool Sequence::operation()
{
	list<Component*> children = this->getChildren();

	for (auto it = children.begin(); it != children.end(); it++)
		if (!(*it)->operation())
			return false;

	return true;
}
