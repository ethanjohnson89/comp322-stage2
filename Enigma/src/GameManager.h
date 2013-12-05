/****************************************
Group #: 2
Members: Steve Patterson, James Mart, Nick Halvorsen, Ethan Johnson
Course: Comp 322
Date: 12/4/13
****************************************/

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
	
	virtual Worldmap* getMap() {return currentMap;}
	virtual void setMap(Worldmap *wm){currentMap = wm;}
	virtual void lookAtMap(){lookingAtMap = true;}
	virtual void lookAtArea(){lookingAtMap = false;}
	
	virtual Inventory* getInventory() {return inventory;}
	virtual void setInventory(Inventory *inv) {inventory = inv;}
	
	typedef std::map<std::string,Command>::iterator CommandIterator;
	virtual Command getCommand(string cmdName); //Throws a commandNotFoundException
	virtual void addCommand(Command com) { commands[com.getKey()] = com; }
	virtual CommandIterator getCommandIteratorBegin() { return commands.begin(); }
	virtual CommandIterator getCommandIteratorEnd() { return commands.end(); }
	virtual int getCommandCount() { return commands.size(); }

	int buttonClicked;
	int buttonFrames;
	bool lookingAtMap;

	virtual void printText(string s) { textToPrint << s; }

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