#pragma once

#include <BehaviorTrees.h>
#include <BWAPI.h>

using namespace BWAPI;

class LessThanNUnits : public Condition
{
	public:
		LessThanNUnits();
		~LessThanNUnits();

		bool operation();

	private:
		const int N = 10;
};

