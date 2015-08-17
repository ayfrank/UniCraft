#include "Link.h"

Link::Link()
{
}


Link::~Link()
{
}

bool Link::operation()
{
	list<Component*> children = this->getChildren();

	for (auto it = children.begin(); it != children.end(); it++)
		return (*it)->operation();

	return false;
}

bool Link::add(Component* component)
{
	list<Component*> children = this->getChildren();

	if (children.size() >= 1)
		return false;
	else
		return Composite::add(component);
}
