#ifndef __GAMEMANAGER_H
#define __GAMEMANAGER_H

/************  Exceptions  **************

//invalidIndexException - thrown if index is accessed in a manager container that does not have an object at that index.

*****************************************/



class GameManager {

public:
	Map* getCurrentMap();
	Map* getMap(int index); //Throws invalidIndexException
	int getCurrentMapIndex();
	void setCurrentMap(int index); //Throws invalidIndexException
	Map* replaceMap(int index, Map* newmap); //Returns replaced map, throws invalidIndexException
	int getMapCount();

	Inventory* getCurrentInventory();
	int getCurrentInventoryIndex();
	void setCurrentInventory(int index);
	Inventory* getInventory(int index);
	void addInventory(Inventory* newInventory);
	Inventory* replaceInventory(int index, Inventory* newInventory);
	int getInventoryCount();

	typedef CommandIterator someType; 
	/*An alias for an iterator type provided by the internal data structure used to store Commands within the GameManager. 
	It is expected, but not required, that this will be a type similar to std::map<std::string,Command*>, with the key 
	being the commandís name.*/
	Command* getCommand(string cmdName); //Throws a commandNotFoundException
	void addCommand(Command* newCommand);
	CommandIterator getCommandIteratorBegin();
	CommandIterator getCommandIteratorEnd();
	int getCommandCount();

	MenuButton* getMenuButton(int index);
	void addMenuButton(MenuButton* newMenuButton);
	MenuButton* replaceMenuButton(int index, MenuButton* newMenuButton);
	int getMenuButtonCount();

	bool lookingAtMap;
	Console cons; 


private:

	Map* currentMap;
};

#endif