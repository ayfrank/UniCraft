#pragma once

#include <vector>
#include "GoapAction.h"

using namespace std;

class Path
{
	public:
		Path();
		~Path();

		void setReachable(bool);
		void setPath(vector<GoapAction*>);
		void setCost(float);

		bool isReachable();
		vector<GoapAction*> getPath();
		float getCost();

	private:
		float cost;
		bool reachable;
		vector<GoapAction*> path;
};
