#pragma once

#include <vector>
#include "GoapAction.h"
#include "Path.h"

using namespace std;

class GoapPlanner
{
	public:
		GoapPlanner();
		~GoapPlanner();

		void addAction(GoapAction*);

		vector<GoapAction*> reachGoal(string goal);

	private:
		vector<GoapAction*> actions;
		
		bool searchCheapestPath(GoapAction*, float&, vector<GoapAction*>&);
};

