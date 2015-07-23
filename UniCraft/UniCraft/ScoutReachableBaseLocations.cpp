#include "ScoutReachableBaseLocations.h"


ScoutReachableBaseLocations::ScoutReachableBaseLocations()
{
	scout = NULL;
	attacked = false;
	lastBaseVisited = 0;
	lastDestinationReached = true;
	startPosition = NULL;
}


ScoutReachableBaseLocations::~ScoutReachableBaseLocations()
{
}

void ScoutReachableBaseLocations::execute()
{
	if(knowledgeBase->isAnalyzed()) //If BWTA is finished to analyze
	{
		if(scout == NULL || scout->getHitPoints() <= 0) //Get a scout
		{
			//TODO
		}

		if(scout->isUnderAttack()) //If the scout is under attack
		{
			if(startPosition == NULL)
				startPosition = &(getStartLocation(Broodwar->self())->getPosition());

			scout->move(*startPosition); //Run away to own base
			attacked = true;
		}
		else
		{
			if (baseLocations.size() == 0)
				baseLocations = knowledgeBase->getBaseLocations();

			Position position = baseLocations[lastBaseVisited]->getPosition();

			int x1 = position.x;
			int y1 = position.y;

			int x2 = scout->getPosition().x;
			int y2 = scout->getPosition().y;

			if(attacked && !scout->isUnderAttack()) //If the scout is no more under attack
			{
				attacked = false;
				lastDestinationReached = true;
				lastBaseVisited = (lastBaseVisited + 1) % baseLocations.size();

				while (!isConnected(baseLocations[lastBaseVisited]->getTilePosition(), scout->getTilePosition())) //Find a destination reachable
					lastBaseVisited = (lastBaseVisited + 1) % baseLocations.size();
			}

			if(abs(x1 - x2) <= DELTA_TILE && abs(y1 - y2) <= DELTA_TILE) //If the scout is near the destination point
			{
				lastDestinationReached = true;
				lastBaseVisited = (lastBaseVisited + 1) % baseLocations.size();

				while (!isConnected(baseLocations[lastBaseVisited]->getTilePosition(), scout->getTilePosition())) //Find a destination reachable
					lastBaseVisited = (lastBaseVisited + 1) % baseLocations.size();
			}

			if(lastDestinationReached)
			{
				Position position = baseLocations[lastBaseVisited]->getPosition();
				scout->move(position);
				lastDestinationReached = false;
			}

			for (auto &u : Broodwar->enemy()->getUnits())
				if (u->getType().isResourceDepot())
					knowledgeBase->insertEnemyBasePosition(u->getPosition());
		}
	}
}
