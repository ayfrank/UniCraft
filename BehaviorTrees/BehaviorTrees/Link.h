#pragma once

#include "Composite.h"

class Link final : public Composite
{
	public:
		Link();
		~Link();

		bool operation();
		bool add(Component*);
};

