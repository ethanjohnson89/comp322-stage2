/****************************

VERSION 2.0

****************************/


#include "GameManager.h"

int main() {
	int exitStatus;
	GameManager manager;
	manager.setUpGame();
	
	manager.intro();
	exitStatus = manager.runUntilExitRequest();

	if (exitStatus != -1) manager.saveGame();

	return 0;
}
