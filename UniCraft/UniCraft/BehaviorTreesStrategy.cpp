#include "BehaviorTreesStrategy.h"

BehaviorTreesStrategy::BehaviorTreesStrategy()
{
	knowledgeBase = new KnowledgeBase();
	utility = new Utility(knowledgeBase);

	utility->analyze();

	//TACTICS
	buildBuildings = new BuildBuildings(knowledgeBase, utility);
	collectResources = new CollectResources(knowledgeBase, utility);
	createWorkers = new CreateWorkers(knowledgeBase, utility);
	createMarines = new CreateMarines(knowledgeBase, utility);
	defend = new Defend(knowledgeBase, utility);
	scoutReachableLocations = new ScoutReachableBaseLocations(knowledgeBase, utility);
	waveAttack = new WaveAttack(knowledgeBase, utility);
	seekAndDestroy = new SeekAndDestroy(knowledgeBase, utility);

	//BTREES TASKS

		//Common Tasks -- duplicated for delete, flyweight?
		Component* isThereACommandCenter = new IsThereACommandCenter(knowledgeBase);
		Component* insertCommandCenterIntoBuildingQueue = new InsertCommandCenterIntoBuildingQueue(utility);
		Component* lessThanNUnits = new LessThanNUnits();

		//WorkersTree Tasks
		Component* workersTree = new Link();
		Component* selector1 = new SequentialSelector();
		Component* moreThanNWorkers = new MoreThanNWorkers(knowledgeBase);
		Component* selector2 = new SequentialSelector();
		Component* sequence1 = new Sequence();
		Component* createWorkersAction = new TacticAction(createWorkers, this);

		//MarinesTree Tasks
		Component* marinesTree = new Link();
		Component* selector3 = new SequentialSelector();
		Component* sequence2 = new Sequence();
		Component* selector4 = new SequentialSelector();
		Component* sequence3 = new Sequence();
		Component* isThereAnyBarrack = new IsThereAnyBarrack(knowledgeBase);
		Component* createMarinesAction = new TacticAction(createMarines, this);
		Component* moreThanNBarracks = new MoreThanNBarracks(knowledgeBase);
		Component* insertBarracksIntoBuildingQueue = new InsertBarracksIntoBuildingQueue(utility, knowledgeBase);

		//BuildBuildingsTree Tasks
		Component* buildBuildingsTree = new Link();
		Component* selector5 = new SequentialSelector();
		Component* isBuildingQueueEmpty = new IsBuildingQueueEmpty(utility);
		Component* buildBuildingsAction = new TacticAction(buildBuildings, this);

		//CollectResourcesTree Tasks
		Component* collectResourcesTree = new Link();
		Component* selector6 = new SequentialSelector();
		Component* sequence4 = new Sequence();
		Component* collectResourcesAction = new TacticAction(collectResources, this);

		//SupplyDepotsTree Tasks
		Component* supplyDepotsTree = new Link();
		Component* selector7 = new SequentialSelector();
		Component* areThereEnoughSupplies = new AreThereEnoughSupplies();
		Component* insertSupplyDepotsIntoBuildingQueue = new InsertSupplyDepotsIntoBuildingQueue(utility);

		//ScoutTree Tasks
		Component* scoutTree = new Link();
		Component* selector8 = new SequentialSelector();
		//Component* moreThanNUnits = new MoreThanNUnits();
		Component* scoutAction = new TacticAction(scoutReachableLocations, this);

		//WarTree Tasks
		Component* warTree = new Link();
		Component* selector9 = new SequentialSelector();
		Component* sequence5 = new Sequence();
		Component* underAttack = new UnderAttack(knowledgeBase);
		Component* defendAction = new TacticAction(defend, this);
		Component* sequence6 = new Sequence();
		Component* isFirstAttack = new IsFirstAttack(waveAttack);
		Component* selector10 = new SequentialSelector();
		Component* lessThan20Marines = new LessThanNMarines(knowledgeBase, 20);
		Component* attackAction = new TacticAction(waveAttack, this);
		Component* selector11 = new SequentialSelector();
		Component* lessThan30Marines = new LessThanNMarines(knowledgeBase, 30);

		//SeekAndDestroy Tree
		Component* seekAndDestroyTree = new Link();
		Component* selector12 = new SequentialSelector();
		Component* isNotFirstAttack = new IsNotFirstAttack(waveAttack);
		Component* seekAndDestroyAction = new TacticAction(seekAndDestroy, this);

	//BTREES BUILD
	root = new Sequence();

		//WorkersTree Build
		sequence1->add(isThereACommandCenter);
		sequence1->add(createWorkersAction);
		selector2->add(sequence1);
		selector2->add(insertCommandCenterIntoBuildingQueue);
		selector1->add(moreThanNWorkers);
		selector1->add(selector2);
		workersTree->add(selector1);
		root->add(workersTree);

		//MarinesTree Build
		sequence3->add(isThereAnyBarrack);
		sequence3->add(createMarinesAction);
		sequence2->add(sequence3);
		sequence2->add(moreThanNBarracks);
		selector4->add(lessThanNUnits);
		selector4->add(insertBarracksIntoBuildingQueue);
		selector3->add(sequence2);
		selector3->add(selector4);
		marinesTree->add(selector3);
		root->add(marinesTree);

		//BuildBuildingsTree Build
		selector5->add(isBuildingQueueEmpty);
		selector5->add(buildBuildingsAction);
		buildBuildingsTree->add(selector5);
		root->add(buildBuildingsTree);

		//CollectResourcesTree Build
		sequence4->add(isThereACommandCenter);
		sequence4->add(collectResourcesAction);
		selector6->add(sequence4);
		selector6->add(insertCommandCenterIntoBuildingQueue);
		collectResourcesTree->add(selector6);
		root->add(collectResourcesTree);

		//SupplyDepotsTree Build
		selector7->add(areThereEnoughSupplies);
		selector7->add(insertSupplyDepotsIntoBuildingQueue);
		supplyDepotsTree->add(selector7);
		root->add(supplyDepotsTree);

		//ScoutTree Build
		selector8->add(lessThanNUnits);
		selector8->add(scoutAction);
		scoutTree->add(selector8);
		root->add(scoutTree);

		//WarTree Build
		sequence5->add(underAttack);
		sequence5->add(defendAction);
		selector10->add(lessThan20Marines);
		selector10->add(attackAction);
		sequence6->add(isFirstAttack);
		sequence6->add(selector10);
		selector11->add(lessThan30Marines);
		selector11->add(attackAction);
		selector9->add(sequence5);
		selector9->add(sequence6);
		selector9->add(selector11);
		warTree->add(selector9);
		root->add(warTree);

		//SeekAndDestroyTree
		selector12->add(isNotFirstAttack);
		selector12->add(seekAndDestroyAction);
		seekAndDestroyTree->add(selector12);
		root->add(seekAndDestroyTree);
}


BehaviorTreesStrategy::~BehaviorTreesStrategy()
{
	delete knowledgeBase;
	delete utility;
	delete buildBuildings;
	delete collectResources;
	delete createWorkers;
	delete createMarines;
	delete defend;
	delete scoutReachableLocations;
	delete waveAttack;
	delete seekAndDestroy;

	list<Component*> components = root->getChildren();

	delete root;

	while (components.size() > 0)
	{
		Component* component = components.front();
		components.pop_front();

		if (component)
		{
			components.insert(components.end(), component->getChildren().begin(), component->getChildren().end());

			delete component;
		}
	}
}

void BehaviorTreesStrategy::compute()
{
	tactics.clear();
	root->operation();
}
