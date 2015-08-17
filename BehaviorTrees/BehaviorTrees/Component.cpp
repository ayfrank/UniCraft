#include "Component.h"


Component::Component()
{
	parent = nullptr;
}


Component::~Component()
{
}

bool Component::add(Component* component)
{
	return false;
}

bool Component::remove(Component* component)
{
	return false;
}

Component* Component::getParent()
{
	return parent;
}

void Component::setParent(Component* parent)
{
	this->parent = parent;
}

list<Component*> Component::getChildren()
{
	return list<Component*> ();
}