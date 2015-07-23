#include "KnowledgeBase.h"


DWORD WINAPI AnalyzeThread(KnowledgeBase* knowledgeBase)
{
	analyze();
	knowledgeBase->setAnalyzed(true);
	return 0;
}

KnowledgeBase::KnowledgeBase()
{
	analyzed = false;
	readMap();
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)AnalyzeThread(this), NULL, 0, NULL);

	for(auto &u : Broodwar->self()->getUnits())
		if(u->getType().isWorker())
			workers.push_back(u);
}

KnowledgeBase::~KnowledgeBase()
{
}

bool KnowledgeBase::isAnalyzed()
{
	analyzedLock.lock();
	return analyzed;
	analyzedLock.unlock();
}

void KnowledgeBase::setAnalyzed(bool analyzed)
{
	analyzedLock.lock();
	this->analyzed = analyzed;
	analyzedLock.unlock();
}

vector< UnitInterface* > KnowledgeBase::getWorkers()
{
	return workers;
}

vector< UnitInterface* > KnowledgeBase::getMarines()
{
	return marines;
}

set< Position, enemyBasesComparator > KnowledgeBase::getEnemyBasesPositions()
{
	return enemyBasesPositions;
}

vector< BaseLocation* > KnowledgeBase::getBaseLocations()
{
	if(isAnalyzed())
	{
		if(baseLocations.size() == 0)
		{
			auto baseLocations_ = BWTA::getBaseLocations();

			for(auto it = baseLocations_.begin(); it != baseLocations_.end(); it++)
				baseLocations.push_back(*it);
		}

		return baseLocations;
	}

	return baseLocations;
}

void KnowledgeBase::insertEnemyBasePosition(Position position)
{
	enemyBasesPositions.insert(position);
}
