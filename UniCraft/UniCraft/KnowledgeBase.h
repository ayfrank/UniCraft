#pragma once

#include <BWAPI.h>
#include <BWTA.h>
#include <Windows.h>
#include <algorithm>

using namespace std;
using namespace BWAPI;
using namespace BWTA;

struct enemyBasesComparator
{
	bool operator()(const Position& p1, const Position& p2) const
	{
		return !(p1.x == p2.x && p1.y == p2.y);
	}
};

class KnowledgeBase
{
	public:
		KnowledgeBase();
		~KnowledgeBase();

		set< int > getWorkers();
		set< int > getMarines();
		set< int > getAttackingMarines();
		set< int > getBarracks();
		int getCommandCenter();
		vector< BaseLocation* > getBaseLocations();
		set< Position, enemyBasesComparator > getEnemyBasePositions();
		int getScout();

		void addWorker(int);
		void addMarine(int);
		void addAttackingMarine(int);
		void addBarrack(int);
		void addEnemyBasePosition(Position);

		void setScout(int);
		void setCommandCenter(int);

		void removeWorker(int);
		void removeMarine(int);
		void removeAttackingMarine(int);
		void removeBarrack(int);

		bool isNotAttacking(int);

	private:
		bool analyzed; //True when BWTA will finish to analyze

		vector<BaseLocation*> baseLocations; //A position on the map where it makes sense to place a base (i.e. near minerals)
		set<Position, enemyBasesComparator> enemyBasePositions;

		set<int> workers;
		set<int> marines;
		set<int> attackingMarines;
		set<int> barracks;
		int commandCenter;
		int scout;
};
