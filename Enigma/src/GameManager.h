#ifndef __GAMEMANAGER_H
#define __GAMEMANAGER_H

class GameManager {

public:
	GameManager(){}
	//Worldmap* getCurrentMap();
	//Worldmap* getMap(int index); //Throws invalidIndexException
	//int getCurrentMapIndex();
	//void setCurrentMap(int index); //Throws invalidIndexException
	//Worldmap* replaceMap(int index, Map* newmap); //Returns replaced map, throws invalidIndexException
	//int getMapCount();

	//Inventory* getCurrentInventory();
	int getCurrentInventoryIndex(){return 1;}
	//void setCurrentInventory(int index);
	//Inventory* getInventory(int index);
	//void addInventory(Inventory* newInventory);
	//Inventory* replaceInventory(int index, Inventory* newInventory);
	//int getInventoryCount();

	//typedef CommandIterator someType; 
	///*An alias for an iterator type provided by the internal data structure used to store Commands within the GameManager. 
	//It is expected, but not required, that this will be a type similar to std::map<std::string,Command*>, with the key 
	//being the command’s name.*/
	//Command* getCommand(string cmdName); //Throws a commandNotFoundException
	//void addCommand(Command* newCommand);
	//CommandIterator getCommandIteratorBegin();
	//CommandIterator getCommandIteratorEnd();
	//int getCommandCount();

	//MenuButton* getMenuButton(int index);
	//void addMenuButton(MenuButton* newMenuButton);
	//MenuButton* replaceMenuButton(int index, MenuButton* newMenuButton);
	//int getMenuButtonCount();

	//bool lookingAtMap;
	//Console cons; 


private:

	//Map* currentMap;
};

#endif