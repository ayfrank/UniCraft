#include "ScoutReachableBaseLocations.h"


ScoutReachableBaseLocations::ScoutReachableBaseLocations(KnowledgeBase* knowledgeBase, Utility* utility) : AbstractScouting(knowledgeBase, utility)
{
	scoutID = -1;
	tryCounter = 0;
	startPosition = NULL;
	nearness = 0;
	lastBaseVisited = 0;
	reset();
}


ScoutReachableBaseLocations::~ScoutReachableBaseLocations()
{
}

void ScoutReachableBaseLocations::reset()
{
	attacked = false;
	lastDestinationReached = true;
	inTheCenter = false;
	corner = 0;
}

void ScoutReachableBaseLocations::execute()
{
	set<Position, enemyBasesComparator> enemyBasePositions = knowledgeBase->getEnemyBasePositions();

	Unit scout = Broodwar->getUnit(scoutID);

	//if (knowledgeBase->isAnalyzed()) //If BWTA is finished to analyze
	//{
		if (scoutID == -1 || (scoutID != -1 && (scout->getHitPoints() <= 0 || !scout->exists()))) //Get a scout
		{
			reset();

			Unit commandCenter = Broodwar->getUnit(knowledgeBase->getCommandCenter());

			if (commandCenter != NULL && commandCenter->exists() && commandCenter->getHitPoints() > 0 && knowledgeBase->getWorkers().size() > 0)
			{
				Unit scout = commandCenter->getClosestUnit((Filter::IsIdle || Filter::IsGatheringMinerals) &&
					Filter::IsOwned && Filter::IsWorker && !Filter::IsConstructing && !Filter::IsUnderAttack);

				if (scout)
				{
					scoutID = scout->getID();
					knowledgeBase->removeWorker(scout->getID());
					knowledgeBase->setScout(scout->getID());
				}
			}
		}
		else
		{		
			if (scout->isUnderAttack()) //If the scout is under attack
			{
				if (startPosition == NULL)
					startPosition = &(getStartLocation(Broodwar->self())->getPosition());

				scout->move(*startPosition); //Run away to own base
				attacked = true;
			}
			else
			{
				if (baseLocations.size() == 0)
					baseLocations = knowledgeBase->getBaseLocations();

				if (inTheCenter && !attacked) //Se lo scout raggiunge il centro dell'area molto probabilmente non è colonizzata dal nemico, quindi esplolara in cerca di edifici non visibili
				{
					if (corner < 4)
					{
						tryCounter++;

						if (corner == 0) //NORD-WEST
						{
							scout->move(Position(centerX - 150, centerY + 150));						

							if (scout->getPosition() == Position(centerX - 150, centerY + 150) || tryCounter >= 50)
							{
								corner++;
								tryCounter = 0;
							}
						}
						else
							if (corner == 1) //NORD-OVEST
							{
								scout->move(Position(centerX + 150, centerY + 150));

								if (scout->getPosition() == Position(centerX + 150, centerY + 150) || tryCounter >= 50)
								{
									corner++;
									tryCounter = 0;
								}
							}
							else
								if (corner == 2) //SUD-WEST
								{
									scout->move(Position(centerX + 150, centerY - 150));

									if (scout->getPosition() == Position(centerX + 150, centerY - 150) || tryCounter >= 50)
									{
										corner++;
										tryCounter = 0;
									}
								}
								else
									if (corner == 3) //SUD-OVEST
									{
										scout->move(Position(centerX - 150, centerY - 150));

										if (scout->getPosition() == Position(centerX - 150, centerY - 150) || tryCounter >= 50)										{
											corner++;
											tryCounter = 0;
										}
									}
					}
					else
					{
						corner = 0;
						inTheCenter = false;
						lastDestinationReached = true;
						lastBaseVisited = (lastBaseVisited + 1) % baseLocations.size();

						while (!isConnected(baseLocations[lastBaseVisited]->getTilePosition(), scout->getTilePosition())) //Find a destination reachable
							lastBaseVisited = (lastBaseVisited + 1) % baseLocations.size();

						nearness = 0;
						tryCounter = 0;
					}
				}
				else
				{
					Position position = baseLocations[lastBaseVisited]->getPosition();

					int x1 = position.x;
					int y1 = position.y;

					int x2 = scout->getPosition().x;
					int	y2 = scout->getPosition().y;

					if (attacked && !scout->isUnderAttack()) //If the scout is no more under attack
					{
						attacked = false;
						lastDestinationReached = true;
						lastBaseVisited = (lastBaseVisited + 1) % baseLocations.size();

						while (!isConnected(baseLocations[lastBaseVisited]->getTilePosition(), scout->getTilePosition())) //Find a destination reachable
							lastBaseVisited = (lastBaseVisited + 1) % baseLocations.size();
					}

					if (abs(x1 - x2) <= DELTA_TILE && abs(y1 - y2) <= DELTA_TILE) //Se sono in un intorno della base
					{
						if (abs(x1 - x2) <= nearness && abs(y1 - y2) <= nearness) //If the scout is near the destination point
						{
							if (nearness == 0) //Se sono proprio al centro fai partire l'esplorazione del luogo
							{
								centerX = scout->getPosition().x;
								centerY = scout->getPosition().y;
								inTheCenter = true;
								tryCounter = 0;
							}
							else
							{
								lastDestinationReached = true;
								lastBaseVisited = (lastBaseVisited + 1) % baseLocations.size();

								while (!isConnected(baseLocations[lastBaseVisited]->getTilePosition(), scout->getTilePosition())) //Find a destination reachable
									lastBaseVisited = (lastBaseVisited + 1) % baseLocations.size();

								nearness = 0;
								tryCounter = 0;
							}
						}
						else
						{
							tryCounter++;

							if (tryCounter >= 40) //Se mi blocco o vengo ucciso o sono impossibilitato, dopo tot tentativi aumenta il range
							{
								nearness += 20;
								tryCounter = 0;
							}
						}
					}

					if (lastDestinationReached)
					{
						while (!isConnected(baseLocations[lastBaseVisited]->getTilePosition(), scout->getTilePosition())) //Find a destination reachable
							lastBaseVisited = (lastBaseVisited + 1) % baseLocations.size();

						Position position = baseLocations[lastBaseVisited]->getPosition();

						scout->move(position);

						lastDestinationReached = false;
					}

					Unit closestEnemyBase = scout->getClosestUnit(Filter::IsEnemy && (Filter::IsResourceDepot || Filter::GetType == UnitTypes::Terran_Bunker || Filter::GetType == UnitTypes::Zerg_Sunken_Colony));

					if (closestEnemyBase)
						knowledgeBase->addEnemyBasePosition(closestEnemyBase->getPosition());
				}
			}
		}
}
