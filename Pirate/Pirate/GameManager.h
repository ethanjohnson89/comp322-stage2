#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include"Globals.h"
#include"Player.h"

extern string SAVEGAMES_LIST_FILE;
extern StandardNPC blindManWithAWagon;

extern vector<Area*> areas;
extern vector<NPC*> NPCs;
extern vector<Object*> objects; 
extern vector<string> dependentVerbs;
extern vector<string> independentVerbs;
extern vector<string> directObjects;
extern vector<string> acceptedFillers;


typedef map<CarryableObject*, int>::iterator InventoryIterator;

class GameManager {
public:
	void setUpGame();
	void intro();
	void newGameScreen();
	void introInformation();
	int runUntilExitRequest();
	void saveGame();
	void loadGame(string playerName);
	void deleteGame();
	void saveFileNames(vector<string> names);
	vector<string> loadFileNames();
	string getPlayerInput();
	void respondTo(string action);
	void helpMenu();
	
	void displayLocation();
	void showStats();
	void movePlayerNameToTopOfList(string name);
	void continueGame();
	void endOfPane() {system("pause>nul");system("cls");}
	void pause() {system("pause>nul");}
	void clear() {system("cls");}
	void clearInputStream() {cin.clear();cin.sync();FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));cin.ignore(cin.rdbuf()->in_avail());	}
	string getAction();
	void doAction(string);
	void optionsMenu();
	void unrecognizedInput();

	void processAreaCommand(Area*, string);
	void processNpcCommand(NPC*, string);
	void processObjectCommand(Object*, string);
		
	bool checkAdminCommands(bool specialInput, string& action);
	bool checkUniqueCommands(bool specialInput, string& action);
	
	Area* getArea(string areaName);
	NPC* getNPC(string NPCName);
	Object* getObject(string objectName);

private:
	string dataFile;
	Player player;
};




#endif