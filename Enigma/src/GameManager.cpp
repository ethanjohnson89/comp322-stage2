#include "GameManager.h"

Command GameManager::getCommand(string cmdName) {
	if(commands.find(cmdName) != commands.end())
		return commands[cmdName];
	//throw CommandNotFoundException();
}