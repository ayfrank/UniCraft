#pragma once

#include <BWTA.h>
#include <Windows.h>
#include <mutex>

using namespace std;
using namespace BWTA;

class KnowledgeBase
{
	public:		
		KnowledgeBase();
		~KnowledgeBase();

		bool isAnalyzed();
		void setAnalyzed(bool);

		vector< BaseLocation* > getBaseLocations();

	private:
		bool analyzed; //True when BWTA will finish to analyze
		vector< BaseLocation* > baseLocations; //A position on the map where it makes sense to place a base (i.e. near minerals)

		mutex analyzedLock;
};

DWORD WINAPI AnalyzeThread(KnowledgeBase* knowledgeBase)
{
	analyze();
	knowledgeBase->setAnalyzed(true);
	return 0;
}

