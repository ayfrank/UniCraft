#include "ExampleAIModule.h"
#include <iostream>

using namespace BWAPI;
using namespace Filter;

bool analyzed;
bool analysis_just_finished;

void ExampleAIModule::onStart()
{
  // Hello World!
  Broodwar->sendText("Hello world!");

  // Print the map name.
  // BWAPI returns std::string when retrieving a string, don't forget to add .c_str() when printing!
  Broodwar << "The map is " << Broodwar->mapName() << "!" << std::endl;

  // Enable the UserInput flag, which allows us to control the bot and type messages.
  Broodwar->enableFlag(Flag::UserInput);

  // Uncomment the following line and the bot will know about everything through the fog of war (cheat).
  //Broodwar->enableFlag(Flag::CompleteMapInformation);

  // Set the command optimization level so that common commands can be grouped
  // and reduce the bot's APM (Actions Per Minute).
  Broodwar->setCommandOptimizationLevel(2);

  // Check if this is a replay
  if ( Broodwar->isReplay() )
  {

    // Announce the players in the replay
    Broodwar << "The following players are in this replay:" << std::endl;
    
    // Iterate all the players in the game using a std:: iterator
    Playerset players = Broodwar->getPlayers();
    for(auto p : players)
    {
      // Only print the player if they are not an observer
      if ( !p->isObserver() )
        Broodwar << p->getName() << ", playing as " << p->getRace() << std::endl;
    }

  }
  else // if this is not a replay
  {
    // Retrieve you and your enemy's races. enemy() will just return the first enemy.
    // If you wish to deal with multiple enemies then you must use enemies().
    if ( Broodwar->enemy() ) // First make sure there is an enemy
      Broodwar << "The matchup is " << Broodwar->self()->getRace() << " vs " << Broodwar->enemy()->getRace() << std::endl;
  }

  BWTA::readMap();
  analyzed = false;
  analysis_just_finished = false;

  barracksCount = 0;
  visited = false;
  chockepointToDefende = 0;
  x = 0, y = 0;
  sorted = false;

  CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)AnalyzeThread, NULL, 0, NULL);
}

void ExampleAIModule::onEnd(bool isWinner)
{
  // Called when the game ends
  if ( isWinner )
  {
    // Log your win here!
  }
}

void ExampleAIModule::onFrame()
{
  // Called once every game frame

  // Display the game frame rate as text in the upper left area of the screen
  Broodwar->drawTextScreen(200, 0,  "FPS: %d", Broodwar->getFPS() );
  Broodwar->drawTextScreen(200, 20, "Average FPS: %f", Broodwar->getAverageFPS() );

  // Return if the game is a replay or is paused
  if ( Broodwar->isReplay() || Broodwar->isPaused() || !Broodwar->self() )
    return;

  //BWTA draw
  if (analyzed)
	drawTerrainData();

  if (analysis_just_finished)
  {
	  Broodwar << "Finished analyzing map." << std::endl;;
	  analysis_just_finished = false;
  }

  // Prevent spamming by only running our onFrame once every number of latency frames.
  // Latency frames are the number of frames before commands are processed.
  if ( Broodwar->getFrameCount() % Broodwar->getLatencyFrames() != 0 )
    return;

  // Iterate through all the units that we own
  for (auto &u : Broodwar->self()->getUnits())
  {
    // Ignore the unit if it no longer exists
    // Make sure to include this block when handling any Unit pointer!
    if ( !u->exists() )
      continue;

    // Ignore the unit if it has one of the following status ailments
    if ( u->isLockedDown() || u->isMaelstrommed() || u->isStasised() )
      continue;

    // Ignore the unit if it is in one of the following states
    if ( u->isLoaded() || !u->isPowered() || u->isStuck() )
      continue;

    // Ignore the unit if it is incomplete or busy constructing
    if ( !u->isCompleted() || u->isConstructing() )
      continue;


    // Finally make the unit do some stuff!
    // If the unit is a worker unit
    if ( u->getType().isWorker() )
    {
      // if our worker is idle
      if ( u->isIdle() )
      {
		//If minerals are >= 150 && there aren't any barracks builds once
		if (Broodwar->self()->minerals() >= 150 && barracksCount == 0)
		{
		 TilePosition tileBuildLocation = Broodwar->getBuildLocation(UnitTypes::Terran_Barracks, u->getTilePosition());
		 if (u->build(UnitTypes::Terran_Barracks, tileBuildLocation))
		  barracksCount++;
		}
		else
        // Order workers carrying a resource to return them to the center,
        // otherwise find a mineral patch to harvest.
        if ( u->isCarryingGas() || u->isCarryingMinerals() )
        {
          u->returnCargo();
        }
        else if ( !u->getPowerUp() )  // The worker cannot harvest anything if it
        {                             // is carrying a powerup such as a flag
			// Harvest from the nearest mineral patch or gas refinery
			if ( !u->gather( u->getClosestUnit( IsMineralField || IsRefinery )) )
			{
				// If the call fails, then print the last error message
				Broodwar << Broodwar->getLastError() << std::endl;
			}

        } // closure: has no powerup
      } // closure: if idle

    }
    else if ( u->getType().isResourceDepot() ) // A resource depot is a Command Center, Nexus, or Hatchery
    {
		if (!visited)
		{
			x = u->getPosition().x;
			y = u->getPosition().y;
			visited = true;
		}
      // Order the depot to construct more workers! But only when it is idle.
	  if (u->isIdle() && !(u->train(u->getType().getRace().getWorker())))
      {
        // If that fails, draw the error at the location so that you can visibly see what went wrong!
        // However, drawing the error once will only appear for a single frame
        // so create an event that keeps it on the screen for some frames
        Position pos = u->getPosition();
        Error lastErr = Broodwar->getLastError();
        Broodwar->registerEvent([pos,lastErr](Game*){ Broodwar->drawTextMap(pos, "%c%s", Text::White, lastErr.c_str()); },   // action
                                nullptr,    // condition
                                Broodwar->getLatencyFrames());  // frames to run

        // Retrieve the supply provider type in the case that we have run out of supplies
        UnitType supplyProviderType = u->getType().getRace().getSupplyProvider();
		
        static int lastChecked = 0;

        // If we are supply blocked and haven't tried constructing more recently
        if (  lastErr == Errors::Insufficient_Supply &&
              lastChecked + 400 < Broodwar->getFrameCount() &&
              Broodwar->self()->incompleteUnitCount(supplyProviderType) == 0 )
        {
          lastChecked = Broodwar->getFrameCount();

          // Retrieve a unit that is capable of constructing the supply needed
          Unit supplyBuilder = u->getClosestUnit(  GetType == supplyProviderType.whatBuilds().first &&
                                                    (IsIdle || IsGatheringMinerals) &&
                                                    IsOwned);

          // If a unit was found
          if ( supplyBuilder )
          {
            if ( supplyProviderType.isBuilding() )
            {
              TilePosition targetBuildLocation = Broodwar->getBuildLocation(supplyProviderType, supplyBuilder->getTilePosition());
              if ( targetBuildLocation )
              {
                // Register an event that draws the target build location
                Broodwar->registerEvent([targetBuildLocation,supplyProviderType](Game*)
                                        {
                                          Broodwar->drawBoxMap( Position(targetBuildLocation),
                                                                Position(targetBuildLocation + supplyProviderType.tileSize()),
                                                                Colors::Blue);
                                        },
                                        nullptr,  // condition
                                        supplyProviderType.buildTime() + 100 );  // frames to run

                // Order the builder to construct the supply structure
                supplyBuilder->build( supplyProviderType, targetBuildLocation );
				
              }
            }
            else
            {
              // Train the supply provider (Overlord) if the provider is not a structure
              supplyBuilder->train( supplyProviderType );
            }
          } // closure: supplyBuilder is valid
        } // closure: insufficient supply
      } // closure: failed to train idle unit

    }
	else if (u->getType() == UnitTypes::Terran_Barracks)
	{
		u->train(UnitTypes::Terran_Marine);
	}
	else if (u->getType() == UnitTypes::Terran_Marine && grouped.find(u->getID()) == grouped.end())
	{
		grouped.insert(u->getID());
		buildingGroup.push_back(u);

		if (buildingGroup.size() == 3)
		{
			BWTA::Chokepoint* it = sortedChockepoints[chockepointToDefende];

			if (chockepointToDefende < sortedChockepoints.size() - 1)
				chockepointToDefende++;

			Position position = it->getCenter();

			for (auto it = buildingGroup.begin(); it != buildingGroup.end(); it++)
				if (position)
					(*it)->attack(position);

			buildingGroup.clear();
		}
	}

  } // closure: unit iterator


  if (analyzed && !sorted)
  {
	  sortChockepoints();
	  sorted = true;
  }
}

void ExampleAIModule::onSendText(std::string text)
{
	if (text == "/analyze") {
		if (analyzed == false) {
			Broodwar << "Analyzing map... this may take a minute" << std::endl;
			CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)AnalyzeThread, NULL, 0, NULL);
		}
	}
	else {
		// Send the text to the game if it is not being processed.
		Broodwar->sendText("%s", text.c_str());
	}

  // Make sure to use %s and pass the text as a parameter,
  // otherwise you may run into problems when you use the %(percent) character!

}

void ExampleAIModule::onReceiveText(BWAPI::Player player, std::string text)
{
  // Parse the received text
  Broodwar << player->getName() << " said \"" << text << "\"" << std::endl;
}

void ExampleAIModule::onPlayerLeft(BWAPI::Player player)
{
  // Interact verbally with the other players in the game by
  // announcing that the other player has left.
  Broodwar->sendText("Goodbye %s!", player->getName().c_str());
}

void ExampleAIModule::onNukeDetect(BWAPI::Position target)
{

  // Check if the target is a valid position
  if ( target )
  {
    // if so, print the location of the nuclear strike target
    Broodwar << "Nuclear Launch Detected at " << target << std::endl;
  }
  else 
  {
    // Otherwise, ask other players where the nuke is!
    Broodwar->sendText("Where's the nuke?");
  }

  // You can also retrieve all the nuclear missile targets using Broodwar->getNukeDots()!
}

void ExampleAIModule::onUnitDiscover(BWAPI::Unit unit)
{
}

void ExampleAIModule::onUnitEvade(BWAPI::Unit unit)
{
}

void ExampleAIModule::onUnitShow(BWAPI::Unit unit)
{
}

void ExampleAIModule::onUnitHide(BWAPI::Unit unit)
{
}

void ExampleAIModule::onUnitCreate(BWAPI::Unit unit)
{
  if ( Broodwar->isReplay() )
  {
    // if we are in a replay, then we will print out the build order of the structures
    if ( unit->getType().isBuilding() && !unit->getPlayer()->isNeutral() )
    {
      int seconds = Broodwar->getFrameCount()/24;
      int minutes = seconds/60;
      seconds %= 60;
      Broodwar->sendText("%.2d:%.2d: %s creates a %s", minutes, seconds, unit->getPlayer()->getName().c_str(), unit->getType().c_str());
    }
  }
}

void ExampleAIModule::onUnitDestroy(BWAPI::Unit unit)
{
}

void ExampleAIModule::onUnitMorph(BWAPI::Unit unit)
{
  if ( Broodwar->isReplay() )
  {
    // if we are in a replay, then we will print out the build order of the structures
    if ( unit->getType().isBuilding() && !unit->getPlayer()->isNeutral() )
    {
      int seconds = Broodwar->getFrameCount()/24;
      int minutes = seconds/60;
      seconds %= 60;
      Broodwar->sendText("%.2d:%.2d: %s morphs a %s", minutes, seconds, unit->getPlayer()->getName().c_str(), unit->getType().c_str());
    }
  }
}

void ExampleAIModule::onUnitRenegade(BWAPI::Unit unit)
{
}

void ExampleAIModule::onSaveGame(std::string gameName)
{
  Broodwar << "The game was saved to \"" << gameName << "\"" << std::endl;
}

void ExampleAIModule::onUnitComplete(BWAPI::Unit unit)
{
}

void ExampleAIModule::drawTerrainData()
{
	//we will iterate through all the base locations, and draw their outlines.
	for (std::set<BWTA::BaseLocation*>::const_iterator i = BWTA::getBaseLocations().begin(); i != BWTA::getBaseLocations().end(); i++)
	{
		TilePosition p = (*i)->getTilePosition();
		Position c = (*i)->getPosition();

		//draw outline of center location
		Broodwar->drawBoxMap(p.x * 32, p.y * 32, p.x * 32 + 4 * 32, p.y * 32 + 3 * 32, Colors::Blue);

		//draw a circle at each mineral patch
		for (Unitset::iterator j = (*i)->getStaticMinerals().begin(); j != (*i)->getStaticMinerals().end(); j++)
		{
			Position q = (*j)->getInitialPosition();
			Broodwar->drawCircleMap(q.x, q.y, 30, Colors::Cyan);
		}

		//draw the outlines of vespene geysers
		for (Unitset::iterator j = (*i)->getGeysers().begin(); j != (*i)->getGeysers().end(); j++)
		{
			TilePosition q = (*j)->getInitialTilePosition();
			Broodwar->drawBoxMap(q.x * 32, q.y * 32, q.x * 32 + 4 * 32, q.y * 32 + 2 * 32, Colors::Orange);
		}

		//if this is an island expansion, draw a yellow circle around the base location
		if ((*i)->isIsland())
			Broodwar->drawCircleMap(c, 80, Colors::Yellow);
	}

	//we will iterate through all the regions and draw the polygon outline of it in green.
	for (std::set<BWTA::Region*>::const_iterator r = BWTA::getRegions().begin(); r != BWTA::getRegions().end(); r++)
	{
		BWTA::Polygon p = (*r)->getPolygon();
		for (int j = 0; j<(int)p.size(); j++)
		{
			Position point1 = p[j];
			Position point2 = p[(j + 1) % p.size()];
			Broodwar->drawLineMap(point1, point2, Colors::Green);
		}
	}

	//we will visualize the chokepoints with red lines
	for (std::set<BWTA::Region*>::const_iterator r = BWTA::getRegions().begin(); r != BWTA::getRegions().end(); r++)
	{
		for (std::set<BWTA::Chokepoint*>::const_iterator c = (*r)->getChokepoints().begin(); c != (*r)->getChokepoints().end(); c++)
		{
			Position point1 = (*c)->getSides().first;
			Position point2 = (*c)->getSides().second;
			Broodwar->drawLineMap(point1, point2, Colors::Red);
		}
	}
}

void ExampleAIModule::sortChockepoints() //just a stupid bubble sort
{
	std::set< BWTA::Chokepoint* > chockepoints = BWTA::getChokepoints();

	for (auto it = chockepoints.begin(); it != chockepoints.end(); it++)
	{
		sortedChockepoints.push_back(*it);
	}

	bool sorted = false;

	for (unsigned int i = 0; i < sortedChockepoints.size() && !sorted; i++)
	{
		sorted = true;
		for (unsigned int j = 0; j < sortedChockepoints.size() - 1 - i; j++)
		{
			Position p1 = sortedChockepoints[j]->getCenter();
			Position p2 = sortedChockepoints[j+1]->getCenter();

			if (isMoreDistant(p1, p2))
			{
				BWTA::Chokepoint* tmp = sortedChockepoints[j];
				sortedChockepoints[j] = sortedChockepoints[j + 1];
				sortedChockepoints[j + 1] = tmp;
				sorted = false;
			}
		}
	}
}

bool ExampleAIModule::isMoreDistant(Position p1, Position p2)
{
	int x1 = p1.x;
	int y1 = p1.y;
	int x2 = p2.x;
	int y2 = p2.y;

	return sqrt(pow((x1 - x), 2) + pow((y1 - y), 2)) > sqrt(pow((x2 - x), 2) + pow((y2 - y), 2));
}

DWORD WINAPI AnalyzeThread()
{
	BWTA::analyze();

	analyzed = true;
	analysis_just_finished = true;
	return 0;
}