#include"GameManager.h"

Command* GameManager::getCommand(string cmdName) {
	for (unsigned int i = 0; i < commands.size(); i++) 
		if (commands[i].getKey() == cmdName) return &commands[i];
	return NULL;
}