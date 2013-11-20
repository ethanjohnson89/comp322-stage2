#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"
#include"Area.h"
#include "RandomEvent.h"

class RandomEvent;
extern vector<RandomEvent> randoms;
extern int RANDOMS_CHANCE;

class Area;
extern int STARTING_GOLD;
extern int STARTING_AGE;
extern int STARTING_BAIT;
extern int MINIMUM_FISH_WAIT_TIME;

extern int STARTING_EXP;
extern Area* STARTING_TOWN;
extern Vessel* STARTING_VESSEL;
extern int SHALLOW_FISH;
extern int DEEP_FISH;
extern int REEF_FISH;

extern vector<vector<Fish>> fish;
extern Area * getArea(int id);
extern Area * getArea(string name);
extern Vessel* getVessel(int vesselID);
extern Vessel* getVessel(string vesselName);
extern CarryableObject* getCarryableObject(int id);
extern CarryableObject* getCarryableObject(string name);

extern vector<Vessel*> vessels;
extern vector<Area*> areas;
extern vector<CarryableObject> miscItems;
typedef map<CarryableObject*, int>::iterator InventoryIterator;

class Player {
public:
	~Player(){/*delete loc;*/};		//MEMORY LEAK - change this so it works
	void build(string fileName);

	void saveFirstTimeInfo(); /* Give player the starting items and stats */
	void setIntroInfo(string n, string d){name = n; descriptor = d;}

	//Basic Info
	void   setName(string theName) {name = theName;} 
	string getName()	{return name;}
	int    getAge()		{return age;}
	void   setAge(int a)	{age = a;}
	string getDescriptor(){return descriptor;}
	void   setDescriptor(string d){descriptor = d;}
	void   setDebugMode(bool b){debugMode = b;}
	bool   getDebugMode(){return debugMode;}

	//gold
	int  getGold()		{return gold;}
	void setGold(int g)	{gold = g;}
	void addGold(int g)	{gold += g;}
	void subtractGold(int g) {gold -= g;}

	//bait
	int  getBait()		{return bait;}
	void setBait(int b) {bait = b;}
	void addBait(int b) {bait += b;}
	void subtractBait() {bait--;}
	
	//experience and level
	int getExperience() {return experience;}
	void setExperience(int exp) {experience = exp;}
	void addExperience(int howMuch) {experience+=howMuch;}
	int getLevel();
	int getLevelFloor();
	int getLevelCeiling();

	//location
	void   setLocation(Area* area);
	void   setLocation(int locId);
	void   setLocation(string location);
	void   changeLocation(Area* area) {setLocation(area); displayLocation();}
	void   changeLocation(int locId) {setLocation(locId); displayLocation();}
	void   changeLocation(string location) {setLocation(location);displayLocation();}
	int    getLocationId();
	string getLocationName();
	string getLocationEntryText();
	Area*  location(){return loc;}
	void   displayLocation();
	int	   canAccessArea(string areaName);
	void   discoveredArea(int id);
	void   discoveredArea(); // current area 
	void   printDiscoveredAreas();
	int    howManyAreasDiscovered();
	int	   getDiscoveredAreaIdAtPos(int pos);

	//Vessel
	void	setVessel(Vessel*);
	void	setVessel(int vesselID);
	void	setVessel(string vesselName);
	string	getVesselName() {return vessel->getName();}
	int		getVesselID() {return vessel->getID();}
	Vessel* getCurrentVessel(){return vessel;}
	string	getVesselDescription(){return vessel->getDescription();}
	int		getVesselHealth(){return vessel->getHealth();}
	void	subtractVesselHealth(int h) {vessel->subtractHealth(h);}
	void	setVesselHealth(int h) {vessel->setHealth(h);}
	int		getVesselCapacity() {return vessel->getCapacity();}

	//Time stamping
	void setTimeLastPlayed(int t){timeLastPlayed = t;}
	int  getTimeLastPlayed(){return timeLastPlayed;}
	
	//Inventory
	void  addObjectToInventory(CarryableObject* obj, int amount = 1);
	void  addObjectToInventory(int objId, int amount = 1);
	bool  isObjectInInventory(int id);
	bool  isObjectInInventory(CarryableObject* obj);
	int   howManyOfThisObject(int id);
	int   howManyOfThisObject(CarryableObject* obj);
	int	  getObjectPositionInInventory(int id);
	int	  getObjectPositionInInventory(CarryableObject * obj);
	CarryableObject  getObjectAtPosition(int pos);
	int	  inventorySize(){return inventory.size();}
	void  displayInventory();
	void  emptyInventory();
	void  sellAllFish();

	//fishing
	void goFish();
	int  getWaitTime();
	void setFish(int f) {numFish = f;}
	int  getCarriedFishNum();
	bool isAbleToFish();
	Fish* getFish(int type);
	void adjustStats(Fish* theCatch);
	bool wait(int waitTime);
	void doARandomEvent(bool& pauseFishing);
	bool caughtRandy(){return randy;}
	void justCaughtRandy(){randy = true;}
	void setRandy(bool b){randy = b;}

private:
	string name;
	string descriptor;
	int age;
	int gold;
	int timeLastPlayed;
	int experience;
	int level;
	int bait;
	int numFish;
	bool debugMode;
	bool randy;

	Vessel* vessel;
	Area* loc;
	map<CarryableObject*, int> inventory;
	set<int> discoveredAreas;
};


#endif