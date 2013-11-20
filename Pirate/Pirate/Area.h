#ifndef AREA_H
#define AREA_H

#include"NPC.h"
class NPC;

class Area {
public:
	virtual string getEntryText()=0;
	string getName() {return name;}
	int getId() {return id;}
	string getDescription() {return description;}
	void displayEntryText();
	bool isFishable() {return fishable;}

	//Adjacent area INFO
	void addAdjacentArea(Area* area){areasAdjacent.push_back(area);}
	bool areaAdjacent(Area* name);

	//Object INFO
	Object* objectPresent(string& objName);
	void listObjects();

	//NPC INFO
	NPC* NPCPresent(string& name);
	void addNPC(NPC* pNPC){NPCS.push_back(pNPC);}
	void listNPCS();

	//EXPERIENCE
	int getExpReq(){return expReq;}

protected:
	int id;
	string name;
	string entryText;
	string description;
	int expReq;
	bool fishable;

	vector<string>::iterator iter;
	vector<Object*> objects;
	vector<Area*> areasAdjacent;
	vector<NPC*> NPCS;
};


class Town : public Area {
public:
	Town(int i, string n, string et, string d, int xp){id = i; name = n; entryText = et; description = d; expReq = xp; fishable = false;}
	virtual string getEntryText(){return entryText;}
private:
	string entryText;
};

class Water : public Area
{
public:
	int getFishType() {return fishType;}
	Water(int i, string n, string et, string d, int xp, int type){id = i; name = n; entryText = et; description = d; expReq = xp; fishType = type; fishable = true;}
	virtual string getEntryText(){return entryText;}
private:
	int fishType;
	string entryText;
};

class Dock : public Area  
{
public:
	Dock(int i, string n, string et, string d, int xp){id = i; name = n; entryText = et; description = d; expReq = xp;fishable = false;}
	virtual string getEntryText(){return entryText;}
private:
	string entryText;
};

#endif