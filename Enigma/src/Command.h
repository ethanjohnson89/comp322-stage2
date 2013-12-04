#ifndef __COMMAND_H
#define __COMMAND_H

class GameManager;
#include "GameManager.h"

#include<string>
#include<vector>
using std::vector;
using std::string;



class Command {
public:
	void setAssociatedFunction(CommandFunction *fn) {associatedFunction = fn;}
	CommandFunction* getAssociatedFunction() {return associatedFunction;}
	string getKey() {return key;}
private: 
	CommandFunction* associatedFunction;
	string key;
};

#endif