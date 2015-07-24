#pragma once

#include "Strategy.h"

class Manager
{
	public:
		Manager(Strategy* strategy);
		~Manager();
		void performActionsOfThisStep();

	private:
		Strategy* strategy;
};