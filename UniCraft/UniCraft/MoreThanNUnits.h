#pragma once

#include <BehaviorTrees.h>
#include <BWAPI.h>

using namespace BWAPI;

class MoreThanNUnits :	public Condition
{
	public:
		MoreThanNUnits();
		~MoreThanNUnits();

		bool operation();

	private:
		const int N = 10;
};

