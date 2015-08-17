#pragma once

#include "Composite.h"

class Sequence final : public Composite
{
	public:
		Sequence();
		~Sequence();

		bool operation();
};

