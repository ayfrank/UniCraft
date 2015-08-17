#pragma once

#include "Component.h"

class Leaf : public Component
{
	public:
		Leaf();
		~Leaf();

		bool add(Component*) final;
		bool remove(Component*) final;

		list<Component*> getChildren() final;
};

