
#ifndef _COMMANDFUNCTIONS_H
#define _COMMANDFUNCTIONS_H

#include "GameManager.h"

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
	gm->printText("Help: Up/Down arrows: scroll inventory");
	return "";
}

string goToArea(GameManager *gm, vector<string> args)
{
	gm->lookingAtMap = false;
	Worldmap *currentMap = gm->getMap();
	int targetAreaIndex = 0;
	for(; targetAreaIndex < currentMap->getAreaCount(); targetAreaIndex++)
		if(currentMap->getArea(targetAreaIndex)->getName() == args[0])
			break;
	if(targetAreaIndex >= currentMap->getAreaCount())
	{
		gm->printText("Sorry, I don't know of that place!");
		return "";
	}

	currentMap->setCurrentArea(targetAreaIndex);
	gm->lookAtArea();
	return "";
}

string examineItem(GameManager *gm, vector<string> args)
{
	string itemName = args[0];
	for(int i = 1; i < args.size(); i++)
	{
		itemName += " ";
		itemName += args[i];
	}

	string examineResult = gm->getInventory()->examineItem(itemName);
	gm->printText(examineResult);

	return "";
}


#endif