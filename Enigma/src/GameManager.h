#ifndef __GAMEMANAGER_H
#define __GAMEMANAGER_H
#include "Worldmap.h"
#include "Inventory.h"
#include "globals.h"
#include "EnigmaArea.h"
#include "console.h"
#include "ExceptionClasses.h"

class Command;
#include "Command.h"

#include <string>
#include <map>

using std::string;
using std::map;

class GameManager {

public:
	GameManager():lookingAtMap(false){}
	
	Worldmap* getMap() {return &currentMap;}
	void setMap(Worldmap wm){currentMap = wm;}
	
	Inventory* getInventory() {return &inventory;}
	void setInventory(Inventory inv) {inventory = inv;}
	
	typedef std::map<std::string,Command>::iterator CommandIterator;
	Command getCommand(string cmdName); //Throws a commandNotFoundException
	void addCommand(Command com) { commands[com.getKey()] = com; }
	CommandIterator getCommandIteratorBegin() { return commands.begin(); }
	CommandIterator getCommandIteratorEnd() { return commands.end(); }
	int getCommandCount() { return commands.size(); }

	/**************MULTIPLE INVENTORY SUPPORT*****************
	void addMap(Worldmap wm) {maps.push_back(wm);}
	Worldmap* getCurrentMap(){return &maps.at(mapIndex);}
	Worldmap* getMap(int index){return &maps.at(index);} //Throws invalidIndexException
	int getCurrentMapIndex(){return mapIndex;}
	void setCurrentMap(int index){mapIndex = index;} //Throws invalidIndexException
	Worldmap* replaceMap(int index, Worldmap* newmap){Worldmap* temp = &maps.at(index);maps.at(index) = *newmap;return temp;} //Returns replaced map, throws invalidIndexException
	int getMapCount(){return maps.size();}
	**********************************************************/

	//MenuButton* getMenuButton(int index);
	//void addMenuButton(MenuButton* newMenuButton);
	//MenuButton* replaceMenuButton(int index, MenuButton* newMenuButton);
	//int getMenuButtonCount();

	bool lookingAtMap;

private:

	Inventory inventory;
	Worldmap currentMap;
	map<string,Command> commands;
};

#endif