#include "Area.h"

void Area::displayEntryText() {
	wout << entryText;
}

NPC* Area::NPCPresent(string& name)
{
	for (unsigned int i = 0; i < NPCS.size(); i++)
	{
		if (NPCS[i]->getName() == name)
			return NPCS[i];
	}
	return NULL;
}

void Area::listNPCS()
{
	if (NPCS.empty())
		wout << "You're all alone..." << endl;
	else
	{
		wout << "This is who I can see here" << endl;
		for (unsigned int i = 0; i < NPCS.size(); i++)
		{
			wout << "\t" << NPCS[i]->getName() << endl;
		}
	}
}

Object* Area::objectPresent(string& objName) {

	for (unsigned int i = 0; i < objects.size(); i++) {
		if (objects[i]->getName() == objName) {
			return objects[i];
		}
	}
	return NULL;
}

void Area::listObjects(){
	if (objects.empty()) 
		wout << "There are no items around!" << endl;
	else {
		wout << "You can see: " << endl;
		for (unsigned int i = 0; i < objects.size(); i++) {
			wout << "\t" << objects[i]->getName() << endl;
		}
	}
}

bool Area::areaAdjacent(Area* name) {
	for (unsigned int i = 0; i < areasAdjacent.size(); i++) {
		if (areasAdjacent[i]->getName() == name->getName()) return true;
	}

	return false;

}