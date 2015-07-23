#pragma once

#include <BWAPI.h>
#include <BWTA.h>
#include <Windows.h>
#include <mutex>

using namespace std;
using namespace BWAPI;
using namespace BWTA;

struct enemyBasesComparator
{
	bool operator()(const Position& p1, const Position& p2) const
	{
		return (p1.x == p2.x && p1.y == p2.y);
	}
};

class KnowledgeBase
{
	public:		
		KnowledgeBase();
		~KnowledgeBase();

		bool isAnalyzed();
		void setAnalyzed(bool);

		vector< UnitInterface* > getWorkers();
		vector< UnitInterface* > getMarines();
		vector< BaseLocation* > getBaseLocations();
		set< Position, enemyBasesComparator > getEnemyBasesPositions();

		void insertEnemyBasePosition(Position);

	private:
		bool analyzed; //True when BWTA will finish to analyze
		vector< BaseLocation* > baseLocations; //A position on the map where it makes sense to place a base (i.e. near minerals)
		vector< UnitInterface* > workers;
		vector< UnitInterface* > marines;
		set< Position, enemyBasesComparator > enemyBasesPositions;

		mutex analyzedLock;
};

