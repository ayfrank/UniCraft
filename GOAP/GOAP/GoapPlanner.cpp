#include "GoapPlanner.h"

#include <iostream>
using namespace std;
GoapPlanner::GoapPlanner()
{
}

GoapPlanner::~GoapPlanner()
{
}

void GoapPlanner::addAction(GoapAction* action)
{
	actions.push_back(action);
}

vector<GoapAction*> GoapPlanner::reachGoal(string goal)
{
	float min = FLT_MAX;
	vector<GoapAction*> cheapestPath;

	for (unsigned int i = 0; i < actions.size(); i++)
	{
		if (actions[i]->hasEffect(goal))
		{
			float cost = 0;
			vector<GoapAction*> path;
			bool result = searchCheapestPath(actions[i], cost, path);

			if (result && cost <= min)
			{
				cheapestPath = path;
				min = cost;
			}
		}
	}

	/*cout << "Result: " << result << endl;
	cout << "Cost: " << cost << endl;

	for (int i = 0; i < cheapestPath.size(); i++)
		cout << cheapestPath[i]->nome << " ";
	cout << endl;*/

	return cheapestPath;
}

bool GoapPlanner::searchCheapestPath(GoapAction* action, float& cost, vector<GoapAction*>& path)
{
	vector<Precondition*> preconditions = action->getPreconditions();

	int index = -1;

	bool unsatisfied = false;

	for (unsigned int i = 0; i < preconditions.size() && !unsatisfied; i++) //Check if there are some preconditions unsatisfied
	{
		if (preconditions[i]->check() == false)
		{
			index = i;
			unsatisfied = true;
		}
	}

	if (index == -1) //If there aren't any preconditions unsatisfied
	{
		cost += action->getCost();
		path.push_back(action);
		return true;
	}
	else //If there is at least one precondition unsatisfied
	{
		int toSatisfy = 0;
		int satisfied = 0;

		for (unsigned int i = index; i < preconditions.size(); i++)
		{
			if (preconditions[i]->check() == false)
			{
				vector<Path*> paths;

				toSatisfy++;

				for (unsigned int j = 0; j < actions.size(); j++) //Find all the paths that satisfy that unsatisfied precondition
				{
					if (actions[j]->hasEffect(preconditions[i]->getName())) //If an action satisfy a precondition
					{
						Path* path_ = new Path();
						float cost_ = 0;
						vector<GoapAction*> actions_;
						bool result = searchCheapestPath(actions[j], cost_, actions_);

						path_->setReachable(result);
						path_->setCost(cost_);
						path_->setPath(actions_);

						paths.push_back(path_);
					}
				}

				//Find the cheapest path
				float min = FLT_MAX;
				int indexMin;
				bool find = false;
				for (unsigned int j = 0; j < paths.size(); j++)
				{
					if (paths[j]->isReachable() && paths[j]->getCost() <= min)
					{
						min = paths[j]->getCost();
						indexMin = j;
						find = true;
					}
				}

				if (find)
				{
					satisfied++;
				
					vector<GoapAction*> p = paths[indexMin]->getPath();

					path.insert(path.end(), p.begin(), p.end());
					cost += paths[indexMin]->getCost();
				}

				for (unsigned int j = 0; j < paths.size(); j++)
					delete paths[j];
			}
		}
		path.push_back(action);
		cost += action->getCost();
		return toSatisfy == satisfied;
	}
}

