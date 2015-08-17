#pragma once
#include "Composite.h"

class Decorator : public Composite
{
	public:
		Decorator();
		~Decorator();

		bool add(Component*) final;
};

