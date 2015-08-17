#pragma once

#include "Strategy.h"

#include <BehaviorTrees.h>

#include "TacticAction.h"

#include "MoreThanNWorkers.h"
#include "IsThereACommandCenter.h"
#include "InsertCommandCenterIntoBuildingQueue.h"
#include "IsThereAnyBarrack.h"
#include "MoreThanNBarracks.h"
#include "LessThanNUnits.h"
#include "InsertBarracksIntoBuildingQueue.h"
#include "IsBuildingQueueEmpty.h"
#include "AreThereEnoughSupplies.h"
#include "InsertSupplyDepotsIntoBuildingQueue.h"
#include "MoreThanNUnits.h"
#include "UnderAttack.h"
#include "IsFirstAttack.h"
#include "LessThanNMarines.h"

#include "CollectResources.h"
#include "ScoutReachableBaseLocations.h"
#include "CreateWorkers.h"
#include "CreateMarines.h"
#include "BuildBuildings.h"
#include "WaveAttack.h"
#include "Defend.h"
#include "SeekAndDestroy.h"
#include "IsNotFirstAttack.h"

class BehaviorTreesStrategy : public Strategy
{
	public:
		BehaviorTreesStrategy();
		~BehaviorTreesStrategy();

		void compute();

	private:
		Tactic* buildBuildings;
		Tactic* collectResources;
		Tactic* createWorkers;
		Tactic* createMarines;
		Tactic* defend;
		Tactic* scoutReachableLocations;
		Tactic* waveAttack;
		Tactic* seekAndDestroy;

		Component* root;
};

