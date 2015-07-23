#pragma once

#include "AbstractScouting.h"

class ScoutReachableBaseLocations :	public AbstractScouting
{
	public:
		ScoutReachableBaseLocations();
		~ScoutReachableBaseLocations();
		void execute();

	private:
		UnitInterface* scout;
		bool attacked;
		int lastBaseVisited;
		bool lastDestinationReached;
		Position* startPosition;
		vector< BaseLocation* > baseLocations;
		const int DELTA_TILE = 100;
};

