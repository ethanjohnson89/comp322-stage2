#ifndef __GAMEMANAGER_H
#define __GAMEMANAGER_H
#include "Inventory.h"
#include "globals.h"
#include "EnigmaArea.h"
#include "console.h"
#include "ExceptionClasses.h"
#include "Worldmap.h"

class Command;
#include "Command.h"

#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include <boost/tokenizer.hpp>
#include <boost/thread/thread.hpp>

using std::string;
using std::stringstream;
using std::map;

class GameManager {

	friend class EnigmaApp;

public:
	GameManager():lookingAtMap(true), processingCommand(false), buttonClicked(-1), buttonFrames(0){gl::enableAlphaBlending();gl::color( ColorA(1.0f, 1.0f, 1.0f, 1.0f) );}

	Console con;
	
	Worldmap* getMap() {return currentMap;}
	void setMap(Worldmap *wm){currentMap = wm;}
	void lookAtMap(){lookingAtMap = true;}
	void lookAtArea(){lookingAtMap = false;}
	
	Inventory* getInventory() {return inventory;}
	void setInventory(Inventory *inv) {inventory = inv;}
	
	typedef std::map<std::string,Command>::iterator CommandIterator;
	Command getCommand(string cmdName); //Throws a commandNotFoundException
	void addCommand(Command com) { commands[com.getKey()] = com; }
	CommandIterator getCommandIteratorBegin() { return commands.begin(); }
	CommandIterator getCommandIteratorEnd() { return commands.end(); }
	int getCommandCount() { return commands.size(); }

	int buttonClicked;
	int buttonFrames;
	bool lookingAtMap;

	void printText(string s) { textToPrint << s; }

private:
	Inventory *inventory;
	Worldmap *currentMap;
	map<string,Command> commands;
	bool parseAndExecuteCommand(string commandLine); // returns true if the command function thread has been successfully spun off, false otherwise (happens if another command is already running)
	bool processingCommand;
	boost::thread activeCommandThread;
	friend void threadLauncher(CommandFunction function, GameManager *gm, vector<string> args); // helper function for launching commands
	stringstream textToPrint;
};

#endif