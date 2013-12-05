
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




#endif