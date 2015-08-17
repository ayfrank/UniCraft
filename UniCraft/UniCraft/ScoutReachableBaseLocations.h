#pragma once

#include "AbstractScouting.h"

class ScoutReachableBaseLocations : public AbstractScouting
{
	public:
		ScoutReachableBaseLocations(KnowledgeBase*, Utility*);
		~ScoutReachableBaseLocations();
		void execute();

	private:
		int scoutID;

		void reset();

		//Scout specific base position
		bool inTheCenter;
		int corner;

		//Scouting
		bool attacked;
		int lastBaseVisited;
		bool lastDestinationReached;
		Position* startPosition;
		vector<BaseLocation*> baseLocations;

		//Trying to get as close as possible
		const int DELTA_TILE = 100;
		int nearness;
		int tryCounter;

		int centerX;
		int centerY;
};

