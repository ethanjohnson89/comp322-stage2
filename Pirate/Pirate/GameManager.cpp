#include"GameManager.h"


void GameManager::setUpGame() {
	system("title Pirate v1.0");
	dataFile = "lastgame.log";
	init();
}

void GameManager::saveGame()
{
	ofstream fout;
	string fname = player.getName();
	fname += ".txt";
	fout.open(fname);

	if (fout.fail())
	{
		fout.close();
		wout << "Save error: file " << fname << " failed to open." << endl;
		endOfPane();
		return;
	}
		
	fout << "lastplayed " << time(0) << endl;
	fout << "randy " << player.caughtRandy() << endl;
	fout << "age "  << player.getAge()  << endl;
	fout << "desc " << player.getDescriptor() << endl;
	fout << "gold " << player.getGold() << endl;
	fout << "location " << player.getLocationId() << endl;
	fout << "bait " << player.getBait() << endl;
	fout << "vessel " << player.getVesselID() << endl;

	fout << endl;
	fout << "inventory " << player.inventorySize() << endl;
	for (int i = 0; i < player.inventorySize(); i++)
		fout << player.getObjectAtPosition(i).getId() << " " << player.howManyOfThisObject(player.getObjectAtPosition(i).getId()) << endl;
	fout << "experience " << player.getExperience() << endl;
	fout << "discoveredareas " << player.howManyAreasDiscovered() << endl;
	for (int i = 0; i < player.howManyAreasDiscovered(); i++)
		fout << player.getDiscoveredAreaIdAtPos(i) << ' ';
	fout << endl;
	fout.close();
	
	if (player.getDebugMode()) wout << "Game saves here!" << endl;

	return;
}

void GameManager::loadGame(string playerName)
{
	ifstream fin;
	fin.open(playerName + ".txt");
	
	if (fin.fail()) {
		fin.close();
		wout << "File load error: failed to open \"" << playerName << ".txt\"";
		endOfPane();
		exit(1);
	}

	string dummy; 
	int age;
	string desc;
	int gold;
	int locationId;
	int t;
	int inventorySize;
	int objId;		//This will be used when objects are used more.
	int objAmount;	//Same with this^
	int exp;
	int bait;
	int vesselId;
	int numLoc;
	int locId;
	bool randy;

	fin >> dummy >> t;
	fin >> dummy >> randy;
	fin >> dummy >> age;
	fin >> dummy >> desc;
	fin >> dummy >> gold;
	fin >> dummy >> locationId;
	fin >> dummy >> bait;
	fin >> dummy >> vesselId;
	fin >> dummy >> inventorySize;
	for (int i = 0; i < inventorySize; i++)
	{
		fin >> objId >> objAmount;
		player.addObjectToInventory(getCarryableObject(objId), objAmount); 
	}
	fin >> dummy >> exp;
	fin >> dummy >> numLoc;
	for (int i = 0; i < numLoc; i++)
	{
		fin >> locId;
		player.discoveredArea(locId);
	}



	player.setExperience(exp);
	player.setName(playerName);
	player.setAge(age);
	player.setDescriptor(desc);
	player.setGold(gold);
	player.setLocation(locationId);
	player.setTimeLastPlayed(t);
	player.setBait(bait);
	player.setVessel(vesselId);
	player.setRandy(randy);
	player.setDebugMode(false);
	fin.close();
	movePlayerNameToTopOfList(playerName);
}

vector<string> GameManager::loadFileNames()
{
	vector<string> names;
	string n;
	ifstream fin;
	fin.open(SAVEGAMES_LIST_FILE);

	if (!fin.fail()) {
		fin >> n;
		while (!fin.eof()) {
			names.push_back(n);
			fin >> n;
		}
	}
	fin.close();
	return names;
}

void GameManager::saveFileNames(vector<string> names)
{
	ofstream fout;
	fout.open(SAVEGAMES_LIST_FILE);
	for (auto jimmy = names.begin(); jimmy != names.end(); jimmy++)
		fout << *jimmy << "\n";

	return;
}

void GameManager::movePlayerNameToTopOfList(string name) // whole function edited by Ethan
{
	vector<string> names = loadFileNames();
	bool gotten = false;
	for (auto brendan = names.begin(); brendan != names.end(); brendan++) { // delete the player's name in the vector
		if (*brendan == name) {
			names.erase(brendan);
			gotten = true;
			break;
		}
	}
	if (!gotten) return;
	names.insert(names.begin(), name); // and insert it in the beginning
	saveFileNames(names);
}

void GameManager::intro() {
	bool playing = false;
	int choice = 0;
	while (playing == false) {
	clear();
	wout << endl << "              PIRATE!" << endl;
	wout << endl <<
	"                 ;~					" << endl << 
	"               ./|\\.					" << endl << 
	"             ./ /|`\\.					" << endl << 
	"            /  | |  `\\.				" << endl << 
	"           |   | |    `\\.				" << endl << 
	"           |   \\|     `\\.			" << endl << 
	"         .  `----|________\\.			" << endl << 
	"         \\-----''----.....___			" << endl << 
	"          \\               ""/			" << endl << 
	"      ~^~^~^~^~^`~^~^`^~^~^`^~^~^		" << endl << 
	"       ~^~^~`~~^~^`~^~^~`~~^~^~		" << endl << endl << endl;
	choice = menu("Welcome to Pirate!", 4, "Play", "Instructions", "Credits", "Quit");
	if (choice == 1) {
		clear();
		int choice2 = 0;
		choice2 = menu("Choose a game option:",4 , "Continue a game","Create a new game","Delete a previous game", "Back");
		if (choice2 == 1) {
			vector<string> list = loadFileNames();
			if (list.size() == 0)
			{
				wout << "No profiles found." << endl;
				wout << "Starting new game." << endl;
				pause();
				choice2 = 2;
			}
			else {
				clear();
				list.push_back("Back");
				int choice = menu("Select your name from the list:", list);
				if (choice != list.size()) {
					wout << "\nLoading...";
					loadGame(list[choice-1]);
					playing = true;
				}
				clear();
			}
		}
		if (choice2 == 2) {
			newGameScreen();
			introInformation();
			player.saveFirstTimeInfo();
			// add player's name to list of files
			vector<string> list = loadFileNames();
			list.push_back(player.getName());
			saveFileNames(list);
			movePlayerNameToTopOfList(player.getName());
			saveGame();
			playing = true;
		}
		if (choice2 == 3) {deleteGame();}
		if (choice2 == 4) clear();
	}
	else if (choice == 2) {
		clear();
		wout << "No one has ever attempted to catch the legendary creature Randy and lived to " <<
			"tell about it. You, a shirtless nerd with naught but some trusty swim trunks, must " <<
			"rise to the challenge and attempt to cage him. " <<
			"The journey will be thrilling, lucrative, and above all - dangerous. " << endl << endl <<
			"Begin by fishing in the shallows. The market pays pretty good money for even " <<
			"the smaller catches. As you become more experienced and upgrade your vessel, " <<
			"you can move on to deeper waters to catch bigger fish. And after a very long " <<
			"time, when you feel ready, you may even attempt to catch Randy... Hah. Good luck." << endl << endl;
		pause();
		} else if (choice == 3) {
			clear();
			wout << endl << "   Graphics\tJoan Stark\thttp://www.geocities.com/spunk1111/aquatic.htm" <<endl;
			wout << "\t\tChris\t\thttp://www.chris.com/ASCII/index.php?art=transportation/nautical" << endl;
			wout << "\n   Everything else:" << 
				endl <<"\t   James Mart" <<
				endl <<"\t   Nick Halvorsen" <<
				endl <<"\t   Ethan Johnson" <<
				endl <<"\t   Steve Patterson" << endl;
			

			wout <<	"\t\t\t         /					" << endl << 
					"\t\t\t        ()					" << endl << 
					"\t\t\t        ||					" << endl << 
					"\t\t\t        ||					" << endl << 
					"\t\t\t    __   \\\\				" << endl << 
					"\t\t\t   <  >   \\\\				" << endl << 
					"\t\t\t    ||` .-\"||\".			" << endl << 
					"\t\t\t     \\\\/  _//. `\\			" << endl << 
					"\t\t\t      (  (-'  \\  \\		    " << endl << 
					"\t\t\t       \\  )   |  |			" << endl << 
					"\t\t\t        `\"   /  /			" << endl << 
					"\t\t\t            /  /			    " << endl << 
					"\t\t\t           |  (       _	    " << endl << 
					"\t\t\t            \\  `.-.-.'o`\\  " << endl << 
					"\t\t\t             '.( ( ( .--'	" << endl << 
					"\t\t\t               `\"`\"'`		" << endl;	
			pause();
			}
		else if(choice == 4) {wout << "Arr! Bad form!" << endl << endl; exit(0);}
	}
}

void GameManager::newGameScreen() {
		clear();

	long const double numOfStudentInDrBensinsKindergartenCounselingGroup = 43.22;

	if (numOfStudentInDrBensinsKindergartenCounselingGroup == 43.22)
		wout << "Ohoho!" << " Velcome to PIRATE! Arrr!" << endl;
	else if (341 == 88)
		wout << "Heck." << endl;
}

void GameManager::deleteGame()
{
	vector<string> names = loadFileNames();
	if (names.size() <= 0)
	{
		wout << "No previous games found." << endl;
		endOfPane();
		return;
	}

	if (names[names.size()-1] != "Nevermind.") names.push_back("Nevermind.");
	clear();

	int choice = menu("Which file would you like to delete?", names);
	if (choice == names.size()) return;
	string dummy="";
	dummy.append("Are you sure you want to delete ").append(names[choice-1]).append("?");
	int yn = menu(dummy,2,"No","Yes");	

	if (yn == 1) {
		wout << "Phew.";
		endOfPane();
		return;
	} else	{
		string filename = names[choice-1] + ".txt";
		for (auto dominoes = names.begin(); dominoes != names.end(); dominoes++)
			if (*dominoes == names[choice-1]) {
				names.erase(dominoes);
				break;
			}
		names.pop_back();
		saveFileNames(names);
		remove(filename.c_str());
		wout << "Okay - done (:" << endl;
	}
	endOfPane();
	return;
}

void GameManager::introInformation() {

	string name = "";
	string descriptor = "";
	vector<string> usedNames = loadFileNames();

	bool badName = true;

	while (badName)
	{
		wout << "What is your first name, sailor? ";
		cin >> name;
		if (name.size() > 30) badName = true;
		for (unsigned int i = 0; i < name.size(); i++) {
			badName = false;
			if (!isalpha(name[i]) && !isspace(name[i]))
				badName = true;
		}
		for (unsigned int ii = 0; ii < usedNames.size(); ii++) {
			if (usedNames[ii] == name) {
				badName = true;
				wout << "Arr, I already know that scallywag!" << endl;
			}	
		}
		if (name.size() == 0) badName = true;
		if (badName) wout << "'Ey. That ain't your name. No foolin'." << endl << endl;
		player.setDebugMode(false);
	}
	badName = true;
	while (badName)	{
		wout << "Describe yourself in one word: ";
		cin >> descriptor;
		badName = false;
		for (unsigned int i = 0; i < name.size(); i++)
			if (!isalpha(name[i]) && !isspace(name[i]))	badName = true;
		if (badName) wout << "Can't possibly be!" << endl << endl;
	}

	player.setIntroInfo(name, descriptor);
	clear();
	wout << endl << "Some useful commands to remember: " << endl;
	wout << "\tHelp: Helps new players if you don't understand what to do." << endl;
	wout << "\tOptions: A convenient menu that has useful functions in it. All functions in the menu are directly accessible from the game." << endl;
	wout << "\tStats: Reminds you of your name, your level, and shows you your experience progress towards your next level." << endl;
	wout << endl;
	wout << "You will start out in the Farnape Town, as a Level 0 Pirate. Feel free to explore!" << endl;
	wout << "You are now ready to start your adventure!" << endl;
	endOfPane();
}

int GameManager::runUntilExitRequest() {
	bool wantsToPlay = true;
	wout << player.location()->getEntryText() << endl << endl;

	while (wantsToPlay) {
		string action;
		action = getPlayerInput();
		if (action == "stop") wantsToPlay = false;
		else {
			respondTo(action);
			wout << endl;
		}
	}
	return 0;
}

string GameManager::getPlayerInput() {
	bool validInput = false;
	string action;
	clearInputStream();
	wout << "> ";
	getline(cin, action);
	transform(action.begin(), action.end(), action.begin(), ::tolower);
	for (unsigned int i = 0; i < action.length(); i++) {
		if(ispunct(action[i]))
          action.erase(i,1);
	}
	return action;
}

void GameManager::respondTo(string action) { //PARSER
	if (action=="") return;
	bool specialInput = false;
	bool shouldSave = false;

	specialInput = checkAdminCommands(specialInput, action);
	specialInput = checkUniqueCommands(specialInput, action);

	if (!specialInput) {

		bool independentVerbPresent = false;
		string theIndependentVerb="";
		int orderInd = 0;

		bool dependentVerbPresent = false;
		string theDependentVerb="";
		int orderDep = 0;

		bool directObjectPresent = false;
		string theDirectObject="";
		int orderDO = 0;

		vector<string> words;
		words = split(action, ' '); //Put words of input into this word vector
		int numWords = words.size(); //Count the number of words

		gatherInputInformationFor(independentVerbs, orderInd, independentVerbPresent, words, theIndependentVerb);
		gatherInputInformationFor(dependentVerbs, orderDep, dependentVerbPresent, words, theDependentVerb);
		gatherInputInformationFor(directObjects, orderDO, directObjectPresent, words, theDirectObject);

		if (numWords>1 && theDirectObject == theIndependentVerb)
			independentVerbPresent = false;

		if (split(theDirectObject,' ').size() > 1) numWords--;

		if (numWords == 1) {
			if (directObjectPresent && !independentVerbPresent) wout << "What about " << theDirectObject << "?" << endl;
			else if (dependentVerbPresent) wout << "Specificity, lad... specificity." << endl;
			else if (independentVerbPresent) doAction(theIndependentVerb);
			else unrecognizedInput();
		}

		if (numWords > 1) {
			shouldSave = true;
			bool unrec = false;
			if (independentVerbPresent) unrecognizedInput();
			else if (!directObjectPresent) unrecognizedInput();
			else if (!dependentVerbPresent) unrecognizedInput();
			else if (orderDep != 1) unrecognizedInput();
			else if (orderDO != numWords) unrecognizedInput(); //Must end statement with DO
			else {
				for (int i = 2; i < numWords; i++) //Search all middle words
					if (!stringInVect(words[i-1], acceptedFillers)) unrec = true; //Make sure they are acceptable fillers
				if (unrec==true) {unrecognizedInput();}
				else {
					Area* tempArea;
					NPC* tempNpc;
					Object* tempObject;

					if ((tempArea = getArea(theDirectObject))!=NULL){
						processAreaCommand(tempArea, theDependentVerb);
					}else if ((tempNpc = getNPC(theDirectObject))!=NULL) {
						processNpcCommand(tempNpc, theDependentVerb);
					}else if ((tempObject = getObject(theDirectObject))!=NULL) {
						processObjectCommand(tempObject, theDependentVerb);
					}else {
						wout << "Something is wrong with the parser." << endl;
						wout << "If you see this message, email James Mart about it immediately." << endl;
					}
			
				}
			}
		}
	}
	if (shouldSave) saveGame();
	return;
}

void GameManager::optionsMenu() {
	int choice = menu("Options:", 3, "Stats", "Save", "Save and Quit");
	if (choice == 2) {saveGame(); wout << "Game saved!" << endl;}
	else if (choice == 3) {
		int anotherChoice = menu("Are you sure?", 2, "No", "Yes");
		if (anotherChoice == 1) wout << "That was close." << endl;
		else if (anotherChoice == 2) {
			saveGame();
			wout << "Game saved!" << endl << "Thanks for playing!" << endl << endl;
			exit(0);
		}else wout << "Something went horribly wrong." << endl;
	} 
	else if (choice == 1)
		showStats();

}

void GameManager::showStats() {
	//50 total characters
	int experience_floor = player.getLevelFloor(); //If they are level 5, how much experience is required for level 5?
	int experience_ceiling = player.getLevelCeiling(); //The last exp point before their next level
	int relativeExp = player.getExperience() - experience_floor;
	int entireLevelExp = experience_ceiling-experience_floor;
	int numStars = static_cast<int>(50.0*relativeExp/entireLevelExp);

	wout << "---------------------STATISTICS---------------------" << endl;
	wout << endl << endl;
	wout << "Name: " << player.getName() << endl;
	wout << "Gold: " << player.getGold() << endl;
	wout << "Bait: " << player.getBait() << endl;
	wout << "Level: " << player.getLevel() << endl;
	wout << "Progress towards next level: " << endl;
	
	wout << "____________________________________________________" <<endl;
	for (int i = 0; i < numStars; i++) {
		wout << "*";
	}
	wout << endl << "____________________________________________________" <<endl;
	wout << endl;
	
}

void GameManager::unrecognizedInput() {
	wout << "I don't be knowing what you mean, scallywag!" << endl;
}

Area* GameManager::getArea(string areaName) {
	
	for (unsigned int i =0; i < areas.size(); i++)  {
		string temp = areas[i]->getName();
		transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
		if (temp == areaName) return areas[i];
	}
	
	return NULL;
}

NPC* GameManager::getNPC(string NPCName) {
	for (unsigned int i =0; i < NPCs.size(); i++) {
		string temp = NPCs[i]->getName();
		transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
		if (temp == NPCName) return NPCs[i];
	}
	return NULL;
}

Object* GameManager::getObject(string objectName) {
	for (unsigned int i =0; i < objects.size(); i++) {
		string temp = objects[i]->getName();
		transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
		if (temp == objectName) return objects[i];
	}

	unsigned int typesOfFish;
	for (typesOfFish = 0; typesOfFish < fish.size(); typesOfFish++);
	for (int i = 0; i < typesOfFish; i++) {
		for (unsigned int j = 0; j < fish[i].size(); j++) {
			string s = fish[i][j].getName();
			transform(s.begin(), s.end(), s.begin(), ::tolower);
			if (s == objectName) return &fish[i][j];
		}
	}

	return NULL;
}

void GameManager::helpMenu() {
	int choice = 0;
	while (choice != 8) {
		wout << endl;
		choice = menu("Help", 8, "Where am I?", "What should I do?", "How do I fish?", "How do I sell my fish?", "How do I upgrade my vessel?", "How do I get out of this game?", "What are some useful commands?", "That's all for now.");
		if (choice == 1) {doAction("where");}
		else if (choice == 2) {
			wout << "Start out by fishing down at the dock. You can sell all your fish to Richie. He loves fish." << endl;
		}else if (choice == 3) {
			wout << "Just go to the dock and \"set sail\" into the shallows. From there you can just type \"Go fish\". The more experienced you are, the quicker you will be able to catch them. " << endl;
		}else if (choice == 4) {
			wout << "Find and talk to Richie at the dock. He loves fish." << endl;
		}else if (choice == 5) {
			wout << "Upgrading your vessel is easy if you have the money! Just talk to Victor at the dock and he will tell you how to upgrade your ship! They can get pretty expensive, but it's worth it!" << endl;
		}else if (choice == 6) {
			wout << "Just type \"quit\"! The game will automatically save." << endl;
		}else if (choice == 7) 
			wout << 		
				"      Command  _|_\tFunction" << endl << 
				"Help            |  Display Help menu" << endl << 
				"Go to *Area*    |  Moves character location to the specified area" << endl << 
				"Examine *X*     |  You can examine items, vessels, areas, npcs, pretty much everything!" << endl << 
				"Talk to *Npc*   |  Begins a conversation with the specified NPC" << endl << 
				"Set sail        |  Will move your character into the waters where you can then go fishing" << endl << 
				"Go fish         |  Initiates fishing sequence" << endl << 
				"Sell fish       |  Will begin a conversation with the NPC who buys fish (Must be in range of NPC)" << endl << 
				"Buy bait       _|_ Will begin a conversation with the NPC who sells bait (Must be in range of NPC)" << endl << 
				"There are lots of commands! Experiment with different commands to find those that work!" << endl << endl;
		
	}
	wout << endl;
}

void GameManager::displayLocation() {
	bool normalMap = true;
	if (normalMap) {
		wout << "MAP:                                                          " << endl <<
				"            FARNAPE          COAST        OCEAN               " << endl <<
				"|------------------------------------------------------------|" << endl <<
				"|                              (                Treacherous  |" << endl <<
				"|                              )                     Reef    |" << endl <<
				"|                              (  S                          |" << endl <<
				"|                        Dock  )  H          D               |" << endl <<
				"|                        ````  (  A          E               |" << endl <<
				"|        Town                  )  L          E               |" << endl <<
				"|        ````              B   (  L          P               |" << endl <<
				"|                          E   )  O          S               |" << endl <<
				"|                          A   (  W                          |" << endl <<
				"|                          C   )  S                          |" << endl <<
				"|                          H   (                             |" << endl <<
				"|                              )                             |" << endl <<
				"|                              (                             |" << endl <<
				"|                              )                             |" << endl <<
				"|                              (                             |" << endl <<
				"|------------------------------------------------------------|" << endl << endl;
		wout << "You are at " << player.getLocationName() << "." << endl << endl;
	}
}

void GameManager::doAction(string action) {
	for (unsigned int i = 0; i < areas.size(); i++) {
		string s = areas[i]->getName();
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		if (action == s) respondTo("go to "+ s);
	}

	if (action=="look" || action=="see") {player.location()->displayEntryText(); wout << endl; player.location()->listNPCS();}
	if (action=="who" ) player.location()->listNPCS();
	if (action=="where")  displayLocation();
	if (action=="what") player.location()->listObjects();
	if (action=="fish") {
			int access = -123;
			if (player.location()->isFishable()) {wout << endl;
				player.goFish(); saveGame();}
			else {
				wout << endl;
				int choice = menu("Where would you like to fish?", 3, "Shallows", "Deeps", "Treacherous Reef");
				if (choice == 1) 
					if ((access = player.canAccessArea("Shallows")) == 1) player.setLocation("Shallows");
					else if (access = -1) wout << "You don't have the experience to go there yet! " << endl << endl;
				if (choice == 2)
					if ((access = player.canAccessArea("Deeps")) == 1) player.setLocation("Deeps");
					else if (access = -1) wout << "You don't have the experience to go there yet! Try again when you are level " << getArea("deeps")->getExpReq() << "." << endl << endl;
				if (choice == 3)
					if ((access = player.canAccessArea("Treacherous Reef")) == 1) player.setLocation("Treacherous Reef"); 
					else if (access = -1) wout << "You don't have the experience to go there yet!" << endl << endl;
			}
			if (player.location()->isFishable() && access == 1) {wout << endl;
				player.goFish(); saveGame();}
			else if (access != 1); // prevents duplicate "You can't do that" message
			else wout << "You can't do that here... You should go set sail from the dock!" << endl; 
	}
	if (action=="exit" || action=="quit" || action=="stop") {saveGame(); wout << "Game saved!"<<endl<<"Thanks for playing!" << endl << endl; exit(0);}
	if (action=="save") {saveGame(); wout << "Game saved!\n";}
	if (action=="inventory" || action == "inv") player.displayInventory();
	if (action=="options") optionsMenu();
	if (action=="stats" || action=="statistics") showStats();
	if (action=="help") helpMenu();
	if (action=="level") wout << "You are level " << player.getLevel() << endl << endl;
	if (action=="gold") wout << "You have " << player.getGold() << " gold. " << endl << endl;
	if (action=="bait") wout << "You have " << player.getBait() << " bait. " << endl << endl;
	if (action=="areas") player.printDiscoveredAreas();
	if (action=="vessel") {
		wout << "Your current vessel is the " << player.getVesselName() << "." << endl;
		wout << endl;
		showVessel(player.getVesselID());
		wout << endl << endl;
		wout << "Stats:" << endl;
		wout << "\tCapacity: "<< player.getVesselCapacity() << endl;
		wout << "\tHealth: " << player.getVesselHealth() << endl;
	}

}

bool GameManager::checkAdminCommands(bool specialInput, string& action) {
	/***************************ADMIN COMMANDS*******************************/
	if (action == "scquit") {saveGame(); wout << "Game saved!" << endl; exit(0);}
	if (action == "scgold") {specialInput = true; player.addGold(10000); wout << "10000 gold added" << endl;}
	if (action == "scbait") {specialInput = true; player.addBait(500); wout << "500 bait added" << endl;}
	if (action == "scsuperman") {
		specialInput = true;
		wout << "You are now superman. GG. " << endl;
		player.setGold(999999);
		player.setExperience(999999);
		player.setBait(99999);
		wout << "You now have " << player.getGold() << " gold, " << player.getBait() << " bait, and you are now level " << player.getLevel() << endl;
		system("pause>nul");
		player.setVessel(9); //Titanium Warship
		wout << "Oh and you have the best vessel: Titanium Warship" << endl;
	}
	if (action == "scfishdebug") {
		specialInput = true;
		wout << "Fish being carried: " << player.getCarriedFishNum() << endl;
		wout << "Vessel capacity: " << player.getVesselCapacity() << endl;
		wout << endl;
	}
	if (action == "scdebugmode") {specialInput = true; player.setDebugMode(true); wout << "Debug mode activated" << endl;}
	if (action == "scdebugmode off") {specialInput = true; player.setDebugMode(false); wout << "Debug mode deactivated" << endl;}
	if (action == "north" || action == "south" || action == "east" || action == "west" || action == "go north" || action == "go south" || action == "go east" || action == "go west") {specialInput = true; wout << "Ya know, places in Farnape aren't aligned to a grid. So you can't really travel to a place only giving a direction. Use names!" << endl;}

	/***************************************************************************/
	return specialInput;
}

bool GameManager::checkUniqueCommands(bool specialInput, string& action) {
	//If specialInput is set to true, the parser will not continue to parse the command.
	// ie - Whatever is written here will be exactly what happens based on that input.
	/***************************UNIQUE COMMANDS*******************************/
	if (action == "who can i see" || action == "who is here" || action == "who is around") action="who";
	if (action == "go fish" || action == "go fishing" || action == "fish") action="fish";
	if (action == "sell fish" || action == "sell to richie") {wout << "Richie: "; action="talk to richie";}
	if (action == "where am i") action = "where";
	if (action == "what is this") {specialInput = true; wout << "What?! Get yer head outta the sand, matey! This be Pirate! Start fishin'!" << endl;}
	if (action == "who am i") {specialInput = true;	wout << "Who are yer? Oh boy, with wits like these, I don' see how you are gunna catch Randy..." << endl; wout << "Yer name is " << player.getName() << ". Now off with yer." << endl; }
	if (action == "set sail") action = "go to shallows";
	if (action == "help me") action = "help";
	if (action == "hm" || action == "hmm") {specialInput = true; wout << "Yeah, keep thinkin'." << endl;}
	if (action == "look around") action="look";
	if (action == "hello" || action == "hi") wout << "Hello!" << endl;
	if (action == "buy bait" || action == "buy from june") {wout << "June: "; action = "talk to june";}
	if (action == "lvl") action = "level";
	if (action == "pirate") {specialInput = true; wout << "Arr!" << endl;}
	if (action == "what is my vessel" || action == "what vessel do i have" || action == "what vessel" || action == "my vessel") action = "vessel";
	
	/***************************************************************************/
	return specialInput;
}

void GameManager::processAreaCommand(Area* area, string command) {
	
	if (command == "go" || command == "travel") {
		if (player.location()->getName() == area->getName()) wout << "You are already here! " << endl;
		//Uncomment the below line to turn pirate into an interactive fiction game!
		//else if (!player.location()->areaAdjacent(area)) wout << "You can't get there from here!" << endl;
		else if (player.getLevel() < area->getExpReq()) wout << "You aren't experienced enough to go there! Try again when you are level " << area->getExpReq() << ".\n";
		else player.changeLocation(area);			
	} else if (command == "examine") {
		if (player.location()->getName() != area->getName()) wout << "Yer a detective, ain't cha? You gotta actually be near the place you tryin to examine!" << endl;
		else
			wout << area->getDescription() << endl;
	} else {
		wout << "You can't do that in the " << player.location()->getName();
	}


}

void GameManager::processNpcCommand(NPC* npc, string command) {
	
	if (command == "talk" || command == "speak") {
		if (!player.location()->NPCPresent(npc->getName())) wout << "Ya can't be talking to " << npc->getName() << " unless yer closer to 'em!" << endl;
		else npc->interact(&player);
	}
	else if (command == "beat") {
		if (!player.location()->NPCPresent(npc->getName())) wout << "Why would ya do that?! Well 'ee ain't here anyways." << endl;
		else { 
			int randomNumber = rand()%10+1;
			wout << "You beat " << randomNumber << " gold out of " << npc->getName() << "." << endl;
			player.addGold(randomNumber);
		}
	} else if (command == "kill") 
		wout << "You scamp. Don't do that." << endl;

	else 
		wout << "You can't do that with " << npc->getName() << endl;
}

void GameManager::processObjectCommand(Object* obj, string command) {
	if (command == "drop" && obj->getName() == "swim trunks")
		wout << "You're now nude." << endl;
	else if (command == "examine") { 
		if (player.getObjectPositionInInventory(obj->getId()) != -1) wout << obj->getDescription() << endl << endl;
		else wout << "You don't have that!" << endl << endl;
	}
	else 
		wout << "You can't do that with " << obj->getName() << endl;
}