#include "Decorator.h"


Decorator::Decorator()
{
}


Decorator::~Decorator()
{
}

bool Decorator::add(Component* component)
{
	list<Component*> children = this->getChildren();

	if (children.size() >= 1)
		return false;
	else
		return Composite::add(component);
}
