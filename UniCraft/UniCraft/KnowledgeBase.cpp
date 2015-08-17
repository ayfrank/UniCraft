#include "KnowledgeBase.h"

KnowledgeBase::KnowledgeBase()
{
	scout = -1;
	commandCenter = NULL;
	analyzed = false;

	for (auto &u : Broodwar->self()->getUnits())
	{
		if (u->getType().isWorker())
			workers.insert(u->getID());
		else
			if (u->getType().isResourceDepot())
				commandCenter = u->getID();
	}
}

KnowledgeBase::~KnowledgeBase()
{
}

set<int> KnowledgeBase::getWorkers()
{
	return workers;
}

set<int> KnowledgeBase::getMarines()
{
	return marines;
}

set<int> KnowledgeBase::getAttackingMarines()
{
	return attackingMarines;
}

bool KnowledgeBase::isNotAttacking(int marineID)
{
	if (attackingMarines.find(marineID) == attackingMarines.end())
		return true;

	return false;
}

set<Position, enemyBasesComparator> KnowledgeBase::getEnemyBasePositions()
{
	return enemyBasePositions;
}

bool isMoreDistant(BaseLocation* b1, BaseLocation* b2)
{
	Position p1 = b1->getPosition();
	Position p2 = b2->getPosition();

	int x = BWTA::getStartLocation(Broodwar->self())->getPosition().x;
	int y = BWTA::getStartLocation(Broodwar->self())->getPosition().y;

	int x1 = p1.x;
	int y1 = p1.y;
	int x2 = p2.x;
	int y2 = p2.y;

	return sqrt(pow((x1 - x), 2) + pow((y1 - y), 2)) < sqrt(pow((x2 - x), 2) + pow((y2 - y), 2));
}

vector<BaseLocation*> KnowledgeBase::getBaseLocations()
{
	//if (isAnalyzed())
	//{
		if (baseLocations.size() == 0)
		{
			auto baseLocations_ = BWTA::getBaseLocations();

			for (auto it = baseLocations_.begin(); it != baseLocations_.end(); it++)
				baseLocations.push_back(*it);
		
			sort(baseLocations.begin(), baseLocations.end(), isMoreDistant);
		}

		return baseLocations;
	//}

	//return baseLocations;
}

int KnowledgeBase::getCommandCenter()
{
	return commandCenter;
}

set< int > KnowledgeBase::getBarracks()
{
	return barracks;
}

void KnowledgeBase::addEnemyBasePosition(Position position)
{
	enemyBasePositions.insert(position);
}

void KnowledgeBase::removeWorker(int workerID)
{
	workers.erase(workerID);
}

void KnowledgeBase::removeMarine(int marineID)
{
	marines.erase(marineID);
}

void KnowledgeBase::removeAttackingMarine(int marineID)
{
	attackingMarines.erase(marineID);
}

void KnowledgeBase::removeBarrack(int barrackID)
{
	barracks.erase(barrackID);
}

void KnowledgeBase::addWorker(int workerID)
{
	workers.insert(workerID);
}

void KnowledgeBase::addAttackingMarine(int marineID)
{
	attackingMarines.insert(marineID);
}

void KnowledgeBase::addMarine(int marineID)
{
	marines.insert(marineID);
}

void KnowledgeBase::addBarrack(int barrackID)
{
	barracks.insert(barrackID);
}

void KnowledgeBase::setCommandCenter(int commandCenterID)
{
	commandCenter = commandCenterID;
}

int KnowledgeBase::getScout()
{
	return scout;
}

void KnowledgeBase::setScout(int scoutID)
{
	scout = scoutID;
}