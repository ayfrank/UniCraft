#include "KnowledgeBase.h"


KnowledgeBase::KnowledgeBase()
{
	analyzed = false;
	readMap();
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)AnalyzeThread(this), NULL, 0, NULL);
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
