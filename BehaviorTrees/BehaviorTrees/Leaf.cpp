#include "Leaf.h"


Leaf::Leaf()
{
}


Leaf::~Leaf()
{
}

bool Leaf::add(Component* component)
{
	return Component::add(component);
}

bool Leaf::remove(Component* component)
{
	return Component::remove(component);
}
