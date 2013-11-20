#include "Globals.h"
#include "RandomEvent.cpp"
extern CarryableObject * getCarryableObject(int id);

//_________________________________________________________________
//---------------------Gameplay Variables------------------------
/******LISTS*****/
vector<Area*> areas;
vector<NPC*> NPCs;
vector<Object*> objects;
vector<Vessel*> vessels;
vector<RandomEvent> randoms;
vector<string> independentVerbs;
vector<string> dependentVerbs;
vector<string> directObjects; //The names of all NPCs and items are pushed into here.
vector<string> acceptedFillers;

/******PACE******/
int MINIMUM_FISH_WAIT_TIME = 600; // 1000 = 1 sec
int RANDOMS_CHANCE = 30; // every time you catch a fish, a 1 in RANDOMS_CHANCE chance

//_________________________________________________________________
//-------------------------Fish----------------------------------

vector<vector<Fish>> fish;
vector<Fish> shallowFish;
vector<Fish> deepFish;
vector<Fish> reefFish;

int SHALLOW_FISH = 0;
int DEEP_FISH = 1;
int REEF_FISH = 2;

/******AREAS*****/
Town town	(1, "Town", "You are home! Your lovely town - down town Farnape.", "Isn't it great to be some place familiar?", 0);
Town paletown (2, "Paletown", "You are now in Paletown", "Home of the Great Warbler", 0);
Water shallows (3, "Shallows", "The water is cool, the sun is shining - It's a great day to be swimming in these Shallows.", "It's only knee deep.", 0, SHALLOW_FISH);
Dock dock (4, "Dock", "You walk onto the dock, all sorts of boats are attached to the dock. To the right you see a sandy beach with lots of people.", "One of the oldest parts of this town, the dock is creaky, but it's still standing!", 0);
Water deeps (5, "Deeps", "The water is cold and dark. It's very quiet, almost eerie now that no one else is in sight.", "You shudder when you think to yourself what creatures could\nbe swimming under you at this very moment.", 25, DEEP_FISH);
Water treacherousReef(6, "Treacherous Reef", "It's completely silent now, only the dark shadows of the giant fish below can be seen as the moonlight shines on to the water", "An unsettling feeling creeps over your body as you realize the dangers that lurk here", 35, REEF_FISH);
Town beach (7, "Beach", "No one is here... huh... I thought I saw some people...Must have been a mirage.", "Strangely, no one is here right now.", 0);

/******NPCs******/
StandardNPC blindManWithAWagon("Roiburt", 1, "Blindess", "I've been blind all me life, matey.");
StandardNPC fishingTutor("Temby", 3, "Catching Fish", "Try typing, \"Set sail\" from the dock. That will start you fishing!", "Selling fish", "I heard there's a guy names Richie around here, he loves fish. He would probably buy them from you!", "Upgrades", "Once you have the money, there's a guy back at the dock named Victor who sells brand new vessels he has imported from the Snowlands to the north! He is great, that's where I got my ship over there!", "Deep Sea", "The deeps? That's just what we fisherman call the ocean when it gets deeper and there are bigger fish. Although plenty of rumors have been circulating about dangerous creatures making home in the deeps. Make sure you have a good vessel if you plan on going there!");
StandardNPC fishBuyer("Richie", &buyFish);
ShopkeeperNPC shop1("Jayden");
StandardNPC baitSeller("June", &sellBait);
StandardNPC shipUpgrader("Victor", &upgradeShip);

/*****ITEMS******/
Vessel swimTrunks(1, "Swim Trunks", 100, 10, "You have always been a fan of leopard spotted swimwear.", 0);
Vessel rubberFloat(2, "Rubber Float", 140, 20, "The name 'Bunston' is crudely written in Sharpie on the side.", 200);
Vessel catamaran(3, "Catamaran", 400, 60, "This thing is so dope.", 700);
Vessel boat(4, "Boat", 800, 120, "There is a small hole in the side of the boat. Ah, just ignore it.", 1000);
Vessel speedBoat(5, "Speed Boat", 1500, 200, "This thing is fast! Too bad fishing requires immobility...",1400);
Vessel barge(6, "Barge", 3000, 350, "Hah! No surfer is going to sink THIS thing.", 3000);
Vessel ship(7, "Big Boat", 5000, 700, "Now THIS is a sea-worthy vessel!", 4500);
Vessel aircraftCarrier(8, "Aircraft Carrier", 10000, 1500, "This has terrible gas mileage", 6000);
Vessel titaniumWarship(9, "Titanium Warship", 80000, 3500, "I feel almost indestructible!", 28000); 

//_________________________________________________________________
//-------------------------Items----------------------------------
vector<CarryableObject> miscItems;

//_________________________________________________________________
//-------------------------Starting Info-------------------------

int STARTING_GOLD = 20;
int STARTING_AGE = 0;
Area* STARTING_TOWN = &town;
int STARTING_EXP = 0;
int STARTING_BAIT = 5;
string SAVEGAMES_LIST_FILE = "list.txt";
Vessel* STARTING_VESSEL = &swimTrunks;


//_________________________________________________________________
//-------------------------Useful Functions------------------------

void init() {
	srand(time(0));

	/*****AREAS*****/
	areas.push_back(&town);
	areas.push_back(&paletown);
	areas.push_back(&shallows);
	areas.push_back(&dock);
	areas.push_back(&deeps);
	areas.push_back(&treacherousReef);
	areas.push_back(&beach);
	
	/*****VESSELS*****/
	vessels.push_back(&swimTrunks);
	vessels.push_back(&rubberFloat);
	vessels.push_back(&catamaran);
	vessels.push_back(&boat);
	vessels.push_back(&speedBoat);
	vessels.push_back(&barge);
	vessels.push_back(&ship);
	vessels.push_back(&aircraftCarrier);
	vessels.push_back(&titaniumWarship);

	/*****NPC*****/
	// to do: make it so you don't have to add an npc to 2 different vectors. 
	NPCs.push_back(&blindManWithAWagon);
	NPCs.push_back(&fishingTutor);
	NPCs.push_back(&fishBuyer);
	NPCs.push_back(&shop1);
	NPCs.push_back(&baitSeller);
	NPCs.push_back(&baitSeller);
	NPCs.push_back(&shipUpgrader);

	paletown.addAdjacentArea(&town);
	town.addNPC(&blindManWithAWagon);
	town.addNPC(&shop1);
	town.addAdjacentArea(&dock);
	town.addAdjacentArea(&paletown);

	shallows.addNPC(&fishingTutor);
	shallows.addAdjacentArea(&dock);
	shallows.addAdjacentArea(&deeps);
	
	dock.addAdjacentArea(&shallows);
	dock.addAdjacentArea(&town);
	dock.addAdjacentArea(&beach);
	dock.addNPC(&fishBuyer);
	dock.addNPC(&baitSeller);
	dock.addNPC(&shipUpgrader);

	deeps.addAdjacentArea(&treacherousReef);
	deeps.addAdjacentArea(&shallows);
	treacherousReef.addAdjacentArea(&deeps);

	beach.addAdjacentArea(&dock);
	
//_________________________________________________________________
//-------------------------Shops---------------------------------
	
	// shop1 is the shop in town
	shop1.addItemToStock(1001);
	shop1.addItemToStock(1002);
	shop1.addItemToStock(1000);
	shop1.addItemToStock(104);
	
//_________________________________________________________________
//-------------------------Item Definitions----------------------
	
miscItems.push_back(CarryableObject(1000, "Helmet","This looks like it would fit nicely on a rat.", 22));
miscItems.push_back(CarryableObject(1001, "Grimy Token", "Admit One into Reggsby's Boulevard", 11));
miscItems.push_back(CarryableObject(1002, "Fencing Tutor", "Rodolfo will teach you the ins and outs of this age-old art", 500));


//_________________________________________________________________
//-------------------------Fish Definitions----------------------

// all you have to do to add a new fish is fill in the following line:
	//Note: Keep rarity between 1-200. 
// fishType.push_back(Fish(id, "name", "description", rarity (higher is more common), value, experience));
shallowFish.push_back(Fish(101, "Trout", "A tasty trout",										200, 2, 1));
shallowFish.push_back(Fish(102, "Minnow", "I'm not sure how this guy even bit the hook...",		200, 1, 1));
shallowFish.push_back(Fish(103, "Sunny", "A bright yellow fish, aptly named.",					200, 2, 1));
shallowFish.push_back(Fish(104, "Crawdad", "Crawmom has got to be around here somewhere...",	200, 2, 1));
shallowFish.push_back(Fish(105, "Grunt Fish", "He gives a final grunt as you toss the carcass into the cooler.", 200, 2, 1));
shallowFish.push_back(Fish(106, "Small Bass", "Why is he always frowning?",						200, 2, 1));
shallowFish.push_back(Fish(107, "Large Bass", "Huh... smiling! I guess bigger=happier.",		180, 3, 2));
shallowFish.push_back(Fish(108, "Flyfish", "Light as a feather!",								180, 2, 2));
shallowFish.push_back(Fish(109, "Catfish", "You drop it... it lands on its back.",				150, 3, 3));
shallowFish.push_back(Fish(110, "Lionfish", "More evolved catfish?",							150, 3, 3));
shallowFish.push_back(Fish(111, "Teeny", "Blacksmith's best friend.",							150, 3, 3));
shallowFish.push_back(Fish(112, "Rodentfish", "It has teeth.",									100, 4, 5));
shallowFish.push_back(Fish(113, "Gerbil", "I wonder if Richie will even buy this thing?",		100, 4, 5));
shallowFish.push_back(Fish(114, "Boot", "A leathery snack - not for the faint of heart.",		99, 5, 6));
shallowFish.push_back(Fish(115, "Spider Fish", "It has 8 fins!",								40, 10, 5));
shallowFish.push_back(Fish(116, "Freaky Trout", "This trout is kinda freaky.",					10,	35,	6));
shallowFish.push_back(Fish(117, "Gigantic Bass", "What the?! How is this in the shallows?!",    8,	55,	7));
shallowFish.push_back(Fish(118, "Rainbow Trout", "Trout is colors!",							10,	45,	6));
shallowFish.push_back(Fish(119, "Moony", "The counterpart to the Sunny?",						10,	45,	6));


//These shouldn't be in the shallows, these should be on Barnold's Isles
//shallowFish.push_back(Fish(110, "Moldy Bird", "This bird is kinda moldy.",		9, 16,	6));
//shallowFish.push_back(Fish(111, "Rusty Weasel", "This weasel is kinda rusty.",	8, 18,	7));
//shallowFish.push_back(Fish(112, "Flimsy Chimp", "This chimp is kinda flimsy.",	7, 20,	8));
//shallowFish.push_back(Fish(107, "Scapegoat", "Now all your problems can be someone else's.",	10, 50, 5));


deepFish.push_back(Fish(201, "Angler", "Meh, a common Angler.",					200, 30, 30));
deepFish.push_back(Fish(202, "Tiger Fish", "He even has fangs!",				200, 30, 30));
deepFish.push_back(Fish(203, "Hokey Fish", "Don't poke it!",					200, 30, 30));
deepFish.push_back(Fish(204, "Graybie", "Believe it, Reynolds.",				200, 30, 30));
deepFish.push_back(Fish(205, "Skowler", "A slightly bitter taste...",			190, 32, 31));
deepFish.push_back(Fish(206, "Eel", "Keep an eye out for the electric type!",	180, 34, 33));
deepFish.push_back(Fish(207, "Glowing Angler", "Woah! Is that glowing?!",		120, 58, 50));
deepFish.push_back(Fish(208, "Electric Eel", "This eel is kinda fast.",			100, 70, 60));
deepFish.push_back(Fish(209, "Vagabond", "What a strange place to wander.",		20, 100, 100));
deepFish.push_back(Fish(210, "Nemo", "Now he will never be found.",				1, 500, 100));

reefFish.push_back(Fish(301, "Tiger Shark", "It's 5 feet long!", 180, 210, 90));
reefFish.push_back(Fish(302, "Zebra Shark", "It's lathargic and docile", 200, 200, 90));
reefFish.push_back(Fish(303, "Great White Shark", "It's teeth are still soaked red from its last kill!", 180, 300, 100));
reefFish.push_back(Fish(304, "Whale Shark", "It's 60ft long! It barely fits on your vessel.", 160, 340, 100));
reefFish.push_back(Fish(305, "Skeleton Fish", "The bones clank as you carelessly chuck it in the trunk.", 160, 345, 130));
reefFish.push_back(Fish(306, "Water Dragon", "Rather than fire, this terrifying creature breathes out fear. It's scales are worth a fortune though.", 145, 350, 140));
reefFish.push_back(Fish(307, "Amphibious Mummy", "This fish has been dead for many years.", 145, 370, 150));
reefFish.push_back(Fish(308, "Octopus", "Keep an eye out for the 'rancid' variety.", 8, 500, 350));
reefFish.push_back(Fish(309, "Gigantic Minnow", "This whopping minnow is almost the size of your entire vessel", 1, 1000, 500));

fish.push_back(shallowFish); 
fish.push_back(deepFish);
fish.push_back(reefFish);

//_________________________________________________________________
//-------------------------Random Events-------------------------
//Any fishable place
randoms.push_back(RandomEvent(1000, &throwGold));
randoms.push_back(RandomEvent(800, &addSomeFish));
randoms.push_back(RandomEvent(1000, &experience));

//Shallows
randoms.push_back(RandomEvent(1000, &music, false, 3));

//Deeps
randoms.push_back(RandomEvent(1000, &prancer, false, 5));

//Reef
randoms.push_back(RandomEvent(1000, &graveStone, false, 6));
randoms.push_back(RandomEvent(600, &randy, true, 6));
randoms.push_back(RandomEvent(700, &apparition, false, 6));



//_________________________________________________________________
//-------------------------Global Keywords-------------------------

	for (unsigned int i = 0; i < areas.size(); i++) {
		string s = areas[i]->getName();
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		independentVerbs.push_back(s);
	}
	//Information
	independentVerbs.push_back("look");
	independentVerbs.push_back("see");
	independentVerbs.push_back("where");
	independentVerbs.push_back("who");
	independentVerbs.push_back("what");
	independentVerbs.push_back("gold");
	independentVerbs.push_back("bait");
	independentVerbs.push_back("level");
	independentVerbs.push_back("areas");
	independentVerbs.push_back("vessel");

	//Action
	independentVerbs.push_back("fish");
	
	//Unique (unique to certain areas)
	independentVerbs.push_back("exit");
	independentVerbs.push_back("save");
	independentVerbs.push_back("stop");
	independentVerbs.push_back("options");
	independentVerbs.push_back("quit");
	independentVerbs.push_back("inventory");
	independentVerbs.push_back("inv");
	independentVerbs.push_back("stats");
	independentVerbs.push_back("statistics");
	independentVerbs.push_back("help");

	//Interact
	dependentVerbs.push_back("talk");
	dependentVerbs.push_back("speak");
	dependentVerbs.push_back("examine");
	dependentVerbs.push_back("pick");
	dependentVerbs.push_back("drop");
	dependentVerbs.push_back("kill");
	dependentVerbs.push_back("beat");

	//travel
	dependentVerbs.push_back("go");
	dependentVerbs.push_back("travel");

	//Direct objects (NPCs, Areas, Objects, etc)
	for (unsigned int i = 0; i < areas.size(); i++)
	{
		string s = areas[i]->getName();
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		directObjects.push_back(s);	
	}
	for (unsigned int i = 0; i < NPCs.size(); i++)
	{
		string s = NPCs[i]->getName();
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		directObjects.push_back(s);	
	}
	for (unsigned int i = 0; i < vessels.size(); i++)
	{
		string s = vessels[i]->getName();
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		directObjects.push_back(s);	
	}
	unsigned int typesOfFish;
	for (typesOfFish = 0; typesOfFish < fish.size(); typesOfFish++);
	for (int i = 0; i < typesOfFish; i++) {
		for (unsigned int j = 0; j < fish[i].size(); j++) {
			string s = fish[i][j].getName();
			transform(s.begin(), s.end(), s.begin(), ::tolower);
			directObjects.push_back(s);	
		}
	}


	//Accepted Fillers
	acceptedFillers.push_back("to");
	acceptedFillers.push_back("with");
	acceptedFillers.push_back("the");
	acceptedFillers.push_back("up");
	acceptedFillers.push_back("of");
	acceptedFillers.push_back("all");	
	acceptedFillers.push_back("like");	
	acceptedFillers.push_back("um");
	acceptedFillers.push_back("uh");
	acceptedFillers.push_back("sorta");	
	acceptedFillers.push_back("kinda");			


	for (unsigned int i = 0; i < vessels.size(); i++) 
		objects.push_back(vessels.at(i));


} //End init function
int searchStringVec(vector<string> vec, string key) {
	vector<string> wordsInKey;
	wordsInKey = split(key, ' ');
	bool moreThanOneWord = (wordsInKey.size() == 2); 
	//Key is direct object
	//vec is input
	bool found = false;
	int index = 0;


	if (moreThanOneWord) {
		for (unsigned int i = 0; i < vec.size(); i++) {
			if (vec[i] == wordsInKey[0]){
				if (vec[i+1] == wordsInKey[1]) {
					found = true;
					index = i+1;
					break;
				}
				else break;
			}
		}
	}

	else {
		for (unsigned int i = 0;  i < vec.size(); i++) {
			if (vec[i] == key) {
				index = i+1;
				found = true;
				break;
			}
		}
	}
	if (found) return (index);
	else return 0;
}

void gatherInputInformationFor(const vector<string>& vec, int& orderNum, bool& wordTypePresent,vector<string> theInput, string& theWord) {
	
	vector<string> wordsInVector;
	bool moreThanOneWord = false; 
	int index = 0;

	for (unsigned int i = 0; i < vec.size(); i++) {
		wordsInVector = split(vec[i], ' ');
		moreThanOneWord = (wordsInVector.size() == 2);
		if (orderNum = searchStringVec(theInput, vec[i])) {
			wordTypePresent = true;
			index = i;
			break;
		}
	}

	if (wordTypePresent) 
		theWord = vec[index];
	
	


}

vector<string> &split(const string &s, char delim, vector<string> &elems) {
	stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

bool stringInVect(string theString, vector<string>& theVector) {
	vector<string>::iterator iter;
	for (iter = theVector.begin(); iter != theVector.end(); iter++)
		if (*iter == theString) return true;
	
	return false;

}

CarryableObject * getCarryableObject(int id) // returns a pointer to the object given an id
{							  //  if not found, returns NULL
	for (unsigned int i = 0; i < fish.size(); i++)
		for (unsigned int j = 0; j < fish[i].size(); j++)
			if (fish[i][j].getId() == id)
				return &fish[i][j];
	
	for (unsigned int i = 0; i < miscItems.size(); i++)
		if (miscItems[i].getId() == id)
			return &miscItems[i];




	 // If another array of objects is added besides fish 
	//  (e.g. food), then this function needs to look 
   //   through that vector too

	return NULL;
}

CarryableObject* getCarryableObject(string name) {
	for (unsigned int i = 0; i < miscItems.size(); i++) 
		if (miscItems[i].getName() == name) 
			return &miscItems[i];

	for (unsigned int i = 0; i < fish.size(); i++)
		for (unsigned int j = 0; j < fish[i].size(); j++)
			if (fish[i][j].getName() == name)
				return &fish[i][j];

	return NULL;
}


Area * getArea(int id)
{
	for (unsigned int i = 0; i < areas.size(); i++)
		if (areas[i]->getId() == id)
			return areas[i];
	return NULL; 
}

Area * getArea(string name) {
	for (unsigned int i = 0; i < areas.size(); i++) 
		if (areas[i]->getName() == name)
			return areas[i];
	return NULL;
}

Vessel* getVessel(int id) {
	for (unsigned int i = 0; i < vessels.size(); i++) 
		if (vessels[i]->getID() == id) 
			return vessels[i];

	return NULL;
}

Vessel* getVessel(string name) {
	for (unsigned int i = 0; i < vessels.size(); i++) 
		if (vessels[i]->getName() == name) 
			return vessels[i];
	return NULL;
}

void showVessel(int id) {
	/*
	2 = rubberFloat
	3 = catamaran
	4 = boat
	5 = speedBoat
	6 = barge
	7 = ship
	8 = aircraftCarrier
	9 = titaniumWarship
	*/
	if (id == 1)
		wout <<
       " ,==c==. " << endl <<
       " |_/|\_|" << endl <<
       " | '|` |" << endl <<
       " |__|__|";
     
	else if (id == 2)
		wout << 
	"   __/\\__      " << endl << 
	"~~~\\____/~~~~~~" << endl <<
	"~  ~~~   ~     ";
	else if (id == 3) 
		wout <<
	"                 /|___       " << endl <<
    "               ///|   )) " << endl <<
    "             /////|   ))) " << endl <<
    "           ///////|    ))) " << endl <<
    "         /////////|     ))) " << endl <<
    "       ///////////|     )))) " << endl <<
    "     /////////////|     ))) " << endl <<
    "    //////////////|    ))) " << endl <<
    "  ////////////////|___))) " << endl <<
    "    ______________|________" << endl <<
    "    \\                    / " << endl <<
    "  ~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	else if (id == 4)
		wout << 
	"                         ||\\ " << endl <<
    "                         || \\ " << endl <<
    "                         ||  \\ " << endl <<
    "                         ||   \\ " << endl <<
    "                         ||    \\ " << endl <<
    "                         ||     \\ " << endl <<
    "                         ||      \\ " << endl <<
    "                         ||       \\ " << endl <<
    "                         ||        \\ " << endl <<
    "                         ||         \\ " << endl <<
    "                         ||          \\ " << endl <<
    "                         ||           \\ " << endl <<
    "                         ||            \\ " << endl <<
    "                         ||   ___---~~~` " << endl <<
    "                         ||~~~ ____....------... " << endl <<
    "                   ___...||~~~_____________    ~~-_" << endl <<
    "            __..-~~      ||   \\____________\\       = " << endl <<
    "        _.-~             `'    \\            \\       = " << endl <<
    "     .-~__                      ~~~~~~~~~~~'   ____.= " << endl <<
    "      \\   ~~~~~------......_______....-----~~~~     | " << endl <<
    "       `\\                                          /' " << endl <<
    "         `\\__                                     / " << endl <<
    "             ~~~~~------......_______....-----~~~'   ";
	else if (id==5) 
		wout << 
	"             __               " << endl <<  
    "             \\ \\___     .__   " << endl <<      
    "           .--\"\"___\\..--\"/   " << endl <<
    "       .__.|-\"\"\"..... ' /    " << endl <<
    "  _____\\_______________/_____";

	else if (id == 6)
		wout <<
	"              ,:\',:`,:\',:\' " << endl <<
    "           __||_||_||_||__" << endl <<
    "      ____[\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"]____" << endl <<
    "      \\ \" \'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\' |" << endl <<
    "  ~^~^~^^~^~^~^~^~^~^~^~~^~^~^^~~^~^";

    else if (id == 7)
		wout <<
    "                             |	" << endl <<
    "                             | " << endl <<
    "                             | " << endl <<
    "                     |       | " << endl <<
    "                     |      --- " << endl <<
    "                    ---     '-' " << endl <<
    "                    '-'  ____|_____ " << endl <<
    "                 ____|__/    |    / " << endl <<
    "                /    | /     |   / " << endl <<
    "               /     |(      |  ( " << endl <<
    "              (      | \\     |   \\ " << endl <<
    "               \\     |  \\____|____\\   /| " << endl <<
    "               /\\____|___`---.----` .' | " << endl <<
    "           .-'/      |  \\    |__.--'    \\ " << endl <<
    "         .'/ (       |   \\   |.          \\ " << endl <<
    "      _ /_/   \\      |    \\  | `.         \\ " << endl <<
    "       `-.'    \\.--._|.---`  |   `-._______\\ " << endl <<
    "          ``-.-------'-------'------------/ " << endl <<
    "              `'._______________________.'  " ;
	else if (id == 8)
		wout << 
	"                        |		" << endl <<
    "                       -+- " << endl <<
    "                     ---#---" << endl <<
    "                     __|_|__            __ " << endl <<
    "                     \\_____/           ||\\________ " << endl <<
    "       __   __   __  \\_____/            ^---------^ " << endl <<
    "      ||\\__||\\__||\\__|___  | \'-O-` " << endl <<
    "      -^---------^--^----^___.-------------.___.--------.___.------ " << endl <<
    "      `-------------|-------------------------------|-------------\'";
	else if (id == 9) 
		wout <<
	"                                       |\\ " << endl <<
    "                                      ||. " << endl <<
    "                                      ||;` " << endl <<
    "                                    ,\'|;  : " << endl <<
    "                                  ,\': |;  ` " << endl <<
    "                                ,\'  | ;  `-` " << endl <<
    "                              ,\'    | ;     : " << endl <<
    "                            ,\'    `-|;      ` " << endl <<
    "                           ;        ;        ` " << endl <<
    "                         ,\'      `--\\`-.   `--: " << endl <<
    "                   ,-._,\'`.         |\\||`-.   ` " << endl <<
    "                   `;-.`-._`.       | |\\ \ `-. ` " << endl <<
    "                    :`--`-.`-\\  `--.| /`\\;\\   `-: " << endl <<
    "                    ;      ``-`.    |/  ;  \\    `. " << endl <<
    "                    ;           `.`-/   ;   \\    ` " << endl <<
    "                    ;      :      `/    ;    \\    ` " << endl <<
    "            ,-._    |             /     ;   -`\\    : " << endl <<
    "            `;-.`-._| :          /      |      \\   ` " << endl <<
    "             ;   `-.|     :     /       |       \\   ` " << endl <<
    "             ;      | :    :   /        |        \\   : " << endl << 
    "             ;      | :       /   ;     |         \\  ` " << endl <<
    "             ;      |        /   ;      |       --`\\  ` " << endl <<
    "             |      |  :    /    ;      |           \\  : " << endl <<
    "             | :    |  :   /            ;            \\ ` " << endl <<
    "             |      :     ;            ;:\'-.._      -`\\ ` " << endl <<
    "             |  :   ;___  ;\'---....___;__:__| `-._     \\ : " << endl <<
    "             |      :   `;``-------\'\';||  :  \\    `-._  \\` " << endl <<
    "            -=======:===;===========;=||   :  \\       `-.\\: " << endl <<
    "                ___ ; _;_||        ;  ||___,:-.\\___,....__\\_ " << endl <<
    "               |`--:.|;_o||-______;,..-----\"\"\"\"\" __|__...-\'\' " << endl <<
    "       ----....|___     \"\"\"\"           S.S. Barry__||-------........________ " << endl <<
    "                   \"\"\"\"----....____      __..--\'\'  || ~~~~~ " << endl <<
    "            ~~~ ~~~                \"\"\"\"----....____|/    ~~~~~~~     ~~~~~~~ " << endl <<
    "       ~~~                ~~~~   ~~~~~~  ~  ~~~       ~~~~ " << endl <<
    "         ~~~~~      ~~~      ~     ~~~~~~~~~ ~~~                ~~~~~~~~~~ ";
}


/******************NPC FUNCTIONS**************************/

void buyFish(Player* player){
	wout << "Hey! I'm Richie! I love fish. I have been buying all the catches from these Farnape fisherman for years!" << endl;
	if (player->getCarriedFishNum() < player->inventorySize()) wout << "You have some cool items! If you want to sell them, you can go talk to Jayden in town... he loves little trinkets!" << endl;
	switch (menu("Would you like to sell me all of your fish?",2,"Yes","No"))
	{
	case 1:
		player->sellAllFish();
		player->setFish(0);
		break;
	case 2:
		break;
	}
}

void sellBait(Player* player) {

	int baitCost = 1;

	wout << "Hey there, would you like to buy some bait? Bait costs "<< baitCost << " coin each!" << endl;
	wout << "You have " << player->getGold() << " coins. " << endl;
	int choice = menu("",2,"Yes","No");
	int num = 0;
	int anotherChoice = 0;
	switch (choice) {
	case 1:
		wout << "Great! I sell bait in bundles... How much would you like to buy?" << endl <<endl;
		anotherChoice = menu("", 5, "1 bait", "10 bait", "100 bait", "1000 bait", "5000 bait");
		if (anotherChoice == 1)		 num = 1;
		else if (anotherChoice == 2) num = 10;
		else if (anotherChoice == 3) num = 100;
		else if (anotherChoice == 4) num = 1000;
		else if (anotherChoice == 5) num = 5000;
		break;
	case 2:
		wout << "Okay, maybe next time!" << endl << endl;
		break;
	}

	if (num != 0) {
		if (player->getGold() >= num*baitCost) {
			wout << "Alright that's " << num*baitCost << " gold. Thank you!" << endl;
			player->addBait(num);
			player->subtractGold(num*baitCost);
			wout << "You now have " << player->getBait() << " bait!" << endl << endl;
		} else 
			wout << "Sorry dear, you don't have enough gold for that!" << endl;
	}


}

void upgradeShip(Player* player) {
	vector<string> vesselNames;
	int currentVessel = -1;
	for (unsigned int i = 0; i < vessels.size(); i++) 
		vesselNames.push_back(vessels.at(i)->getName());
	vesselNames.push_back("No thank you.");
	wout << "Oy! Ye want a new vessel? Ye talkin to the right person." << endl;
	int choice = menu("What kind of ship ye want? You currently have the "+player->getVesselName()+" vessel.", vesselNames);

	if (choice == vesselNames.size()) {wout << "Fine! Come back when yer man enough to get a REAL ship!" << endl; return;}

	//choice--; //converts to index
	currentVessel = player->getVesselID();
	
	system("cls");
	Vessel* chosen = getVessel(choice);
	wout << "The " << chosen->getName() << "!" << endl << endl;

	//ASCII ART
	wout << endl;
	showVessel(chosen->getID());
	wout << endl << endl;
	wout << "Specs: " << endl;
	wout << "\tCapacity: " << chosen->getCapacity() << endl;
	wout << "\tHealth: " << chosen->getHealth() << endl;
	wout << "\tPrice: " << chosen->getPrice() << endl;

	wout << endl;
	if (choice < currentVessel) 
		wout << "Eh, I hope you're sure about this... you know you already have a better vessel than this." << endl;
	else if (choice == currentVessel) 
		wout << "What, is your current " << player->getVesselName() << " not good enough for ye?" << endl;
	else if (choice == currentVessel+1)
		wout << "A sensible choice..." << endl;
	else if (choice > currentVessel+1)
		wout << "Oy! That's far better than whatcha currently have, I hope ye can handle something this nice!" << endl;
	wout << endl;

	int menuChoice = menu("Are you sure? Purchasing a new vessel will likely result in the loss of your old vessel.", 2, "Yes", "No");
	if (menuChoice == 2) {
		wout << "Alright well, your loss. Come back when you're sure!" << endl;
		return;
	} 
	if (player->getGold() < getVessel(choice)->getPrice()) {
		wout << "Ya don't even have the money fer that! Git real, son. Come back when ya got at least " << chosen->getPrice() << " gold." << endl << endl;
		return;
	}

	wout << "Congratulations! You just purchased the " << chosen->getName() << " vessel!" << endl;
	Vessel* oldVessel = getVessel(player->getVesselID());
	player->setVessel(chosen);
	player->subtractGold(chosen->getPrice());
	system("pause>nul");
	system("cls");

	int r = rand()%5;
	int num = 0;
	if (r == 0) wout << "Inexplicably, your old vessel bursts into flames." << endl;
	if (r == 1) wout << "You donate your "<< oldVessel->getName() << " to charity. How kind of you." << endl; 
	if (r == 2) wout << "You allow your " << oldVessel->getName() << " to be smashed to pieces by vermin." << endl;
	if (r == 3) {
		num = rand()%5 + 1;
		wout << "With a wave of his wand, Victor turns your old vessel into " << num << " bait. Kindly, he gives it to you." << endl;
		player->addBait(num);
	}
	if (r == 4) wout << "Unfortunately, the crane lifting your new vessel into the water rolls right overtop of your old vessel, completely destroying it." << endl;

}

