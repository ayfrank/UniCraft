#pragma once

#include "Selector.h"

class SequentialSelector final : public Selector
{
	public:
		SequentialSelector();
		~SequentialSelector();

		bool operation();
};

