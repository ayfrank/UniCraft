#pragma once

#include "Strategy.h"

class Manager
{
	public:
		Manager(Strategy*);
		~Manager();
		void performActionsOfThisStep();

	private:
		Strategy* strategy;
};