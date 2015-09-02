#pragma once

#include <set>
#include <vector>
#include "Precondition.h"

using namespace std;

class GoapAction
{
	public:
		GoapAction(float);
		~GoapAction();

		float getCost();
		vector<Precondition*> getPreconditions();

		bool hasEffect(string);

		void addPrecondition(Precondition*);
		void addEffect(string);
		
		virtual void performAction() = 0;
		virtual bool canBePopped(); //Some actions need time to run, call this method to know if an action can be popped from the path

	private:
		float cost;
		vector<Precondition*> preconditions;
		set<string> effects;
};

