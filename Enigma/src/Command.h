/****************************************
Group #: 2
Members: Steve Patterson, James Mart, Nick Halvorsen, Ethan Johnson
Course: Comp 322
Date: 12/4/13
****************************************/

#ifndef __COMMAND_H
#define __COMMAND_H

class GameManager;
#include "GameManager.h"

#include<string>
#include<vector>
using std::vector;
using std::string;


typedef string (*CommandFunction)(GameManager* gm, vector<string> args); //Function signature for Commanmd actions. Arguments to the command, 
																		// as identified by the parser, are passed to the command in the vector args. 
																		// The pointer to the GameManager allows action functions to interact with 
																		// the game as desired by the client.

class Command {
public:	
	Command(){}
	Command(CommandFunction fn, string name):associatedFunction(fn), key(name){}
	void setAssociatedFunction(CommandFunction fn) {associatedFunction = fn;}
	CommandFunction getAssociatedFunction() {return associatedFunction;}
	string getKey() {return key;}
private: 
	CommandFunction associatedFunction;
	string key;
};

#endif