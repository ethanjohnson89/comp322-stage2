#include"Player.h"

void Player::displayLocation() {
    wout << loc->getEntryText() << endl;
    if(loc->getName() == "Treacherous Reef" && randy) // Randy C. Stringer easter egg!
    {
            Sleep(3000);
            wout << endl << "You recall the epic battle in which you conquered the great fish Randy, whose head is now mounted on "
                << "the bulkhead of your ship. Thanks to you, the Treacherous Reef is a bit less treacherous." << endl;
            Sleep(4000);

            wout << endl << "Glancing around the rocks, you see a strange wooden sign in the distance that catches your eye. "
                << "Pulling out your trusy binoculars, you read its text:" << endl;
            wout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            wout << "           Randy C. Stringer, Ph.D" << endl;
            wout << "     Professor of Biblical and Religious Studies" << endl;
            wout << "      PRIVATE PROPERTY - BEWARE OF KILLER BIRDS" << endl;
            wout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            Sleep(4000);
                     
            wout << endl << "You see a thin man dressed in a colorful Tommy Hilfiger shirt standing on the rocks by the sign. "
                << "He calls out, \"Don't mind me. I'm just settling in to my new digs. Seems someone left me a lovely place with "
                << "my name on it. Little chilly, but it's great for bird watching.\"" << endl;
    }
}


void Player::saveFirstTimeInfo() {
	age = STARTING_AGE;
	gold = STARTING_GOLD;
	loc = STARTING_TOWN;
	experience = STARTING_EXP;
	bait = STARTING_BAIT;
	numFish = 0;
	vessel = STARTING_VESSEL;
	randy = false;
	discoveredArea();
}

void Player::setLocation(string locName) 
{
	int locId;

	for (unsigned int i = 0; i < areas.size(); i++) {
		if (areas[i]->getName() == locName)  {
			locId = areas[i]->getId();
			break;
		}
	}
	setLocation(locId);
	if (Player::loc==NULL) {Player::loc = STARTING_TOWN;}
	discoveredArea();
}

void Player::setLocation(Area* area)
{
	Player::loc = area;
	discoveredArea();
}

void Player::setLocation(int locId)
{
	Player::loc = getArea(locId);
	if (Player::loc==NULL) {Player::loc = STARTING_TOWN;}
	discoveredArea();
}

string Player::getLocationName() {
	return loc->getName();
}

int Player::getLocationId()
{
	return loc->getId();
}

string Player::getLocationEntryText()
{
	return loc->getEntryText();
}

void Player::sellAllFish()
{	
	if (getCarriedFishNum() < 1) { wout << "Alas, you have no fish to sell!" << endl; return;}
 
	InventoryIterator it;
	bool hadFish = false;
	for (it = inventory.begin(); it != inventory.end();)	{
		
		if (it->first->getId()  > 100 && it->first->getId() < 1000) /*Fish have ids between 100 and 1000*/ {
			wout << "Sold " << it->second << " " <<  it->first->getName() << " for " << it->first->getValue() * it->second << " gold. (" << it->first->getValue() << " gold ea)" << endl;

			Player::addGold(it->first->getValue() * it->second);
			it = inventory.erase(it);
		}
		else
			it++;
	}
	
}

void Player::addObjectToInventory(CarryableObject* obj, int amount)
{
	InventoryIterator it;
	it = inventory.find(obj);

	for (int i = 0; i < amount; i++)
	{
		if (it == inventory.end()) // if it's not in the inventory
			inventory.emplace(make_pair(obj, 1)); // add it to the inventory
		else
			inventory[obj] += 1;

		it = inventory.find(obj);
	}

}

void Player::addObjectToInventory(int objId, int amount) {
	CarryableObject* temp = NULL;
	for (unsigned int i = 0; i < miscItems.size(); i++) {
		if (miscItems.at(i).getId() == objId) {
			i = miscItems.size();
			temp = &miscItems.at(i);
		}
	}
	if (temp == NULL) {
		for (unsigned int i = 0; i < fish.size(); i++)
			for (unsigned int j = 0; j < fish[i].size(); j++)
				if (fish[i][j].getId() == objId) {
					temp = &fish[i][j];
					break;
				}
	}
	
	if (temp != NULL) addObjectToInventory(temp, amount);
	else cout << "Problem adding object to inventory" << endl;

}

int Player::getObjectPositionInInventory(int id)
{
	int pos = 0;
	InventoryIterator it;

	for (it = inventory.begin(); it != inventory.end(); it++)
	{
		pos++;
		if (it->first->getId() == id)
			return pos;
	}

	return -1;
}

int Player::getObjectPositionInInventory(CarryableObject* obj)
{
	return getObjectPositionInInventory(obj->getId());
}

CarryableObject Player::getObjectAtPosition(int pos)
{
	InventoryIterator it = inventory.begin();

	for (int i = 0; i < pos; i++)
		it++;

	return *it->first;
}

int Player::howManyOfThisObject(int id)
{
	InventoryIterator it;

	for (it = inventory.begin(); it != inventory.end(); it++)
	{
		if (it->first->getId() == id)
			return it->second;
	}

	return 0;
}

int Player::howManyOfThisObject(CarryableObject* obj)
{
	return howManyOfThisObject(obj->getId());
}

bool Player::isObjectInInventory(int id)
{
	if (getObjectPositionInInventory(id) == -1)
		return false;
	else
		return true;
}

bool Player::isObjectInInventory(CarryableObject* obj)
{
	return isObjectInInventory(obj->getId());
}

void Player::displayInventory()
{
	 wout << "______________________________________________________"  << endl;
	 wout << "Backpack:" << '\t' << gold << " gold" << ",\t" << bait << " bait" << endl;
	 wout << "------------------------------------------------------"  << endl;

	 InventoryIterator it;
	 
	 for (it = inventory.begin(); it != inventory.end(); it++)
		 wout << it->first->getName() << " x" << it->second << endl;

	 if (inventory.size() == 0)
		 wout << "\n\nEmpty\n\n" << endl;
	 wout << "------------------------------------------------------" << endl;
}

void Player::emptyInventory()
{
	inventory.clear();
}

int Player::getWaitTime() {
	
	int baseTime = rand() % 10000 + 10000; // 10 - 20 sec

	int ratio = (experience / (loc->getExpReq() + 50));

	if (ratio < 1)
		ratio = 1;

	int time = baseTime / ratio;

	if (time < MINIMUM_FISH_WAIT_TIME)
		time = MINIMUM_FISH_WAIT_TIME;

	return time;
}

int Player::canAccessArea(string areaName) {
	//0 means you aren't next to it.
	//-1 means you don't have the experience
	// 1 means good to go

	//Uncomment the below lines to turn pirate into an interactive fiction!
	Area* temp = getArea(areaName);
	//if (loc->areaAdjacent(temp)) {
		if (temp->getExpReq() > getLevel()) return -1;
		else if (temp->getExpReq() <= getLevel()) return true;
	//} else return 0

		else return false;
}

void Player::goFish()
{
	//Clear input buffer
		GetAsyncKeyState(VK_BACK);
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		cin.sync();

	if (getBait() < 1) {
		wout << "You are out of bait! Go buy some more from June at the docks!" << endl;
		return;
	}

	if (getCarriedFishNum() > getVesselCapacity()) {
		wout << "You really need to get rid of some of those fish before you go fishing for any more." << endl 
			 << "Upgrade your vessel to increase the number of fish you can carry!" << endl;
		return;
	}

	bool stillFishing = true, stopping = false, pauseFishing = false;
	Fish * theFish;


	//int type = SHALLOW_FISH;	   // temp value
								  //  normally you would get what type of fish are available
								 //   based on the location
							    //    something like int type = loc->getFishType();
	int type;
	if (loc->getName() == "Shallows") type = SHALLOW_FISH;
	else if (loc->getName() == "Deeps")	type = DEEP_FISH;
	else if(loc->getName() == "Treacherous Reef") type = REEF_FISH
	;else if (loc->getName() == "Randy Lair") //type = RANDY_FISH
	;else type=SHALLOW_FISH;
		
	
	wout << "Fishing! Location: " << loc->getName() << endl;
	wout << "------------------------------------------------------------" << endl;
	wout << "You cast out your line..." << endl;
	wout << "Press the backspace key to stop fishing!" << endl << endl;
	
	while (stillFishing) {
		
		if (!isAbleToFish()) break;

		if ((theFish = getFish(type)) == NULL) {wout << "Choosing a fish error." << endl; break;} 
		if (wait(getWaitTime())) //If the full wait time is waited
		{	
			int x = rand() % RANDOMS_CHANCE;
			if (x == 0)
				doARandomEvent(pauseFishing);
			else
				adjustStats(theFish); 

			if (pauseFishing)
				break;
		}
		else 
			stillFishing = false;
	}

	wout << "You pull in your line." << endl;
}

int Player::getLevel() { //Level = floor(experience/10)^(1/2)
	return static_cast<int>(floor(pow((experience/10.0),(1.0/2.0))));
}

int Player::getLevelFloor() {
	if (getLevel() == 0) return 0;
	else return static_cast<int>((10*pow((getLevel()),2.0)));
}

int Player::getLevelCeiling() {
	return static_cast<int>(10*pow((getLevel()+1.0), 2.0)-1.0);
}

int Player::getCarriedFishNum() {
	int count = 0;
	if (inventory.size() > 0) {
		for (auto it = inventory.begin(); it != inventory.end(); it++)	{
			if (it->first->getId()  > 100 && it->first->getId() < 1000) /*Fish have ids between 100 and 1000*/ 
				count += it->second;
		}
	}
	return count;
}

bool Player::isAbleToFish() {
	
	if (getBait() < 1) {
			wout << "You are out of bait! Buy more from June at the dock." << endl; 
			return false;
	}
		
	if (getCarriedFishNum() >= getVesselCapacity()) {
			wout << "Whew! If ye catch any more fish, you'll sink!" << endl;
			return false;
	}
	return true;
}

Fish* Player::getFish(int type) {
	int totalRarity, x;
	Fish* temp = NULL;
	//Setting up rarities
	totalRarity = 0;
	for (unsigned int i = 0; i < fish[type].size(); i++)
		totalRarity += fish[type][i].getRarity();
	x = rand() % totalRarity;

	//Choosing fish
	for (unsigned int i = 0; i < fish[type].size(); i++){
		x -= fish[type][i].getRarity();
		if (x <= 0)	{
			temp = &fish[type][i];
			break;
		}
	}

	/*Error Checking*/	if (x > 0)	{wout << "fishing error of some sort - Check it check it check it OUT! SAVE NOW AND QUIT!! AAAAGGGGHHHHH!!!!" << endl;return NULL;}

	return temp;
}

void Player::adjustStats(Fish* theCatch) {
	int temp = getLevel();
	subtractBait();
	addExperience(theCatch->getExperience());
	addObjectToInventory(theCatch);
	numFish++;
	int temp2 = getLevel();
	wout << "You caught a " << theCatch->getName() << "." << endl;
	if (temp != temp2) wout << endl << "*****CONGRATULATIONS!*****" << endl << "   You have leveled up!   " << endl << "   You are now level " << temp2 << "!" << endl << "**************************" << endl << endl;
}

bool Player::wait(int waitTime) {
	bool continuing = true;
	for (int i = 0; i < waitTime; i+=10) {
		Sleep(10);
		if(GetAsyncKeyState(VK_BACK)) continuing = false;  //Backspace key 			
		if (!continuing) break;
	}
	return continuing;
}

void Player::setVessel(Vessel* theVessel) {
	vessel = theVessel;
}

void Player::setVessel(int vesselID) {
	vessel = getVessel(vesselID);
	if (vessel==NULL) {vessel = STARTING_VESSEL;}
}

void Player::setVessel(string vesselName) {
	vessel = getVessel(vesselName);
	if (vessel==NULL) {vessel = STARTING_VESSEL;}
}

void Player::discoveredArea(int id)
{
	discoveredAreas.insert(id);
}

void Player::discoveredArea()
{
	discoveredAreas.insert(loc->getId());
}

void Player::printDiscoveredAreas()
{
	wout << "Areas discovered:" << endl;
	for (set<int>::iterator it = discoveredAreas.begin(); it != discoveredAreas.end(); it++)
	{
		Area* a = getArea(*it);
		if (a == NULL)
			wout << "error";
		else
			wout << a->getName() << endl;
	}
}

int Player::howManyAreasDiscovered()
{
	return discoveredAreas.size();
}

int	Player::getDiscoveredAreaIdAtPos(int pos)
{
	int x = 0;
	set<int>::iterator it = discoveredAreas.begin();

	while (it != discoveredAreas.end() && x != pos)
	{
		it++;
		x++;
	}
	return *it;
}

void Player::doARandomEvent(bool& pauseFishing)
{
	int rarityTotal = 0;
	for (int i = 0; i < randoms.size(); i++)
		if (randoms[i].getWhere() == -1 || randoms[i].getWhere() == loc->getId())
			rarityTotal += randoms[i].getRarity();

	int x = rand() % rarityTotal;
	int tempAt = 0;

	while (x >= 0)
	{
		x -= randoms[tempAt].getRarity();
		
		if (x >= 0)
			tempAt++;
	}

	randoms[tempAt].doEvent(this);

	pauseFishing = randoms[tempAt].stopFishing();
}