#include "Composite.h"

Composite::Composite()
{
}


Composite::~Composite()
{
}

bool Composite::add(Component* component)
{
	component->setParent(this);
	children.push_back(component);
	return true;
}

bool Composite::remove(Component* component)
{
	for (auto it = children.begin(); it != children.end(); it++)
		if ((*it) == component)
		{
			component->setParent(nullptr);
			children.erase(it);
			return true;
		}

	return false;
}

list<Component*> Composite::getChildren()
{
	return children;
}