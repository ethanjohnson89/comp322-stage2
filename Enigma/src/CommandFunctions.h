
#ifndef _COMMANDFUNCTIONS_H
#define _COMMANDFUNCTIONS_H

#include "GameManager.h"

#include <algorithm>
#include <vector>
#include <string>
using std::vector;
using std::string;

string lookAtMap(GameManager* gm, vector<string> args)
{
	gm->lookAtMap();
	return "";
}

string dummyCommand(GameManager *gm, vector<string> args)
{
	// nothing happens here
	return "";
}

string help(GameManager *gm, vector<string> args)
{
	gm->printText("\nKey Bindings:\n     Up/Down arrows: scroll inventory\n");
	gm->printText("Commands:\n     Go *AreaName*:  Goes to a new area.\n");
	gm->printText("\n     Examine *ItemName*:  Displays the item's name and description\n");
	gm->printText("\n     Exit");
	return "";
}

string goToArea(GameManager *gm, vector<string> args)
{
	std::transform(args[0].begin(), args[0].end(), args[0].begin(), ::tolower);

	Worldmap *currentMap = gm->getMap();
	int targetAreaIndex = 0;
	for(; targetAreaIndex < currentMap->getAreaCount(); targetAreaIndex++)
	{
		string areaName_lower = currentMap->getArea(targetAreaIndex)->getName();
		std::transform(areaName_lower.begin(), areaName_lower.end(), areaName_lower.begin(), ::tolower);
		if(areaName_lower == args[0])
			break;
	}
	if(targetAreaIndex >= currentMap->getAreaCount())
	{
		gm->printText("Sorry, I don't know of that place!");
		return "";
	}

	
	if (currentMap->getCurrentAreaIndex() != targetAreaIndex)
	{
		currentMap->setCurrentArea(targetAreaIndex);
		gm->printText("You have entered " + currentMap->getArea(targetAreaIndex)->getName());
	}
	else if(!gm->lookingAtMap)
		gm->printText("You are already in that area.");
	gm->lookAtArea();
	return "";
}

string examineItem(GameManager *gm, vector<string> args)
{
	string itemName = args[0];
	for(unsigned int i = 1; i < args.size(); i++)
	{
		itemName += " ";
		itemName += args[i];
	}

	string examineResult = gm->getInventory()->examineItem(itemName);
	gm->printText(examineResult);

	return "";
}

string exit(GameManager *gm, vector<string> args)
{
	exit(0);
}

#endif