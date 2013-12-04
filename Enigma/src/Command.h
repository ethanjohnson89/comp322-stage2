#ifndef __COMMAND_H
#define __COMMAND_H

#include "GameManager.h"
#include<string>
#include<vector>
using std::vector;
using std::string;

class Command {
public:
	typedef string (*CommandFunction)(GameManager *gm, vector<string> args); //Function signature for Commanmd actions. Arguments to the command, 
																		// as identified by the parser, are passed to the command in the vector args. 
																		// The pointer to the GameManager allows action functions to interact with 
																		// the game as desired by the client.

	void setAssociatedFunction(CommandFunction *fn){associatedFunction = fn;}
	CommandFunction* getAssociatedFunction(){return associatedFunction;}

private: 
	CommandFunction* associatedFunction;
};

#endif