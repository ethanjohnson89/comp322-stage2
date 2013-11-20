#pragma once;

#include "RandomEvent.h"

static void throwGold(Player* player)
{
	int max = static_cast<int>(player->getGold()/30)+10;
	int num = rand()%max + 1;
	wout << "You chuck " << num << " gold into the ocean." << endl;
	player->subtractGold(num);
}

static void addSomeFish(Player* player)
{
	int amount = rand()%(player->getVesselCapacity()-player->getCarriedFishNum())+1;
	if (amount > 5) amount = rand()%5+1;
	int id = rand()%19+101;
	player->addObjectToInventory(id,amount); 
	wout << amount << " "<< getCarryableObject(id)->getName() << " launch into your mouth. You spit them into your net!" << endl;
}

static void graveStone(Player* player)
{
	string name = "";
	int choice = rand()%7;
	switch (choice) {
	case 0:
		name = "Ralphie";
		break;
	case 1:
		name = "Jerald";
		break;
	case 2:
		name = "Randon";
		break;
	case 3:
		name = "Temby";
		break;
	case 4:
		name = "Lenry";
		break;
	case 5:
		name = "Dennis";
		break;
	case 6:
		name = "Han Solo";
		break;
	}

	wout << "You pass an old gravestone floating in the water with the name of one who attempted to sail these waters before you. It appears his name was " << name << "." << endl;
}

static void prancer(Player* player) {
	wout << "You see Dasher and Dancer... where is prancer?" << endl;
}

static void apparition(Player* player) {

	wout << endl << "An apparition appears!" << endl;
	Sleep(1000);
	wout << "Apparition: Beware! An extremely dangerous fish is close at hand!" << endl;
	Sleep(4000);
	wout << player->getName() << ": I know. I'm here to catch it." << endl;
	Sleep(3000);
	wout << "Apparition: No! I once thought I was the most experienced fisherman in the world. I attempted to catch this fish, it destroyed my boat and killed all my crew... for your own good, go back! Stay away..." << endl;
	Sleep(8000);
	wout << endl << "...The apparition fades away." << endl << endl;
}

static void randy(Player* player)
{
	if (player->caughtRandy())
		return;

	Sleep(5000);
	system("cls");
	wout << "Randy Ho!" << endl << endl;
	Sleep(3000);

	if (player->getExperience() > getArea(player->getLocationId())->getExpReq() * 2)
		wout << "You approach Randy..." << endl;
	else
		wout << "You approach Randy cautiously..." << endl;

	Sleep(3000);

	int y = 3;

	while (y < 4)
	{
		y = rand() % 6;
		switch(y)
		{
		case 0:wout << "Randy lashes at your ship..." << endl; break;
		case 1:wout << "You barely manage to avoid Randy's flailing tendons..." << endl; break;
		case 2:wout << "Your ship sinks closer to a whirling vortex..." << endl; break;
		case 3:wout << "Randy slices off a piece of your vessel..." << endl; break;
		}
		Sleep (3000);
	}


	int x = rand() % 10;

	if (x < 5)
	{
		wout << endl << endl << "***** CONGRATULATIONS! You have caught Randy! *****" << endl;
		player->justCaughtRandy();
		wout << "Press a key to continue..." << endl;
		system("pause>nul");
		system("cls");

	}
	else 
	{
		wout << "With one final slap, Randy cleaves your vessel in two." << endl;
		wout << "Press a key to continue..." << endl;
		player->setVessel(STARTING_VESSEL);

		system("pause>nul");
		system("cls");
		
		Sleep(1000);
		wout << "... ";
		Sleep(2000);
		wout << "... ";
		Sleep(3000);
		wout << "\nYou wake up, surrounded by nothing but waters for miles, with just your trusty swim trunks." << endl;
		Sleep(3000);
		wout << "In the distance, you see something hovering towards you..." << endl;
		Sleep(3000);
		wout << "Barnold approaches in a ReMax hot air balloon. He reaches his hand out to you." << endl << endl;
		int choice = menu("Accept his help?", 2, "Yes", "No");

		if (choice != 1)
		{
			wout << "Barnold dives in the water anyways after you and drags you on his hot air balloon. He drops you off at " << STARTING_TOWN->getName() << "." << endl;
			player->setLocation(STARTING_TOWN);
		}
		else 
		{
			player->setLocation(getArea(3));
			wout << "You slowly sink under the water." << endl;
			Sleep(3000);
			wout << "Much time passes..." << endl;
			Sleep(3000);
			wout << "You wash up at the shallows." << endl;
			wout << "You're so lucky that Barnold noticed you and decided to help." << endl;
		}

	}


	return;
}

static void music(Player* player) {

	string name = "";

	int num = rand()%5;
	if (num == 0) name = "Fly Eagles Fly";
	if (num == 1) name = "Flight of the Bumblebees";
	if (num == 2) name = "Prelude in G# Minor";
	if (num == 3) name = "Pastoral Symphony";
	if (num == 4) name = "Free Bird";

	wout << "You hear the soft tune of " << name << " drifting across the water from the beach!" << endl;
}

static void experience(Player* player) {

	int maxAmount = 24;
	int amount = rand()%maxAmount+6;
	player->addExperience(amount);
	int scenario = rand()%5;
	if (scenario == 0)
		wout << "You try eating some of the fish bait... now that you know what it tastes like, that should help you catch fish quicker!" << endl;
	if (scenario == 1) 
		wout << "You remember a fishing tip that Temby gave you as a child... you feel slightly more experienced!" << endl;
	if (scenario == 2)
		wout << "With the skill of a master you pluck a dragon-fly from out of the air and eat it! You gain experience proportional to the skill it took to snag the dragon-fly." << endl;
	if (scenario == 3)
		wout << "An weak earthquake reminds you of the time you broke a toe. Huh... better not do that again. This new knowledge increases your experience." << endl;
	if (scenario == 4) {
		wout << "While waiting for a bite on your line, you wip out the fishing book your buddy Gary gave you." << endl << endl;
		Sleep(3500);
		wout << "\t\"Remember when you break a line, human hair is always a good substitute!" << endl;
		Sleep(2400);
		wout << "\t Also remember, the more experienced you get, the quicker you should be " << endl;
		Sleep(2400);
		wout << "\t able to catch the fish. Lastly, remember, above all: You can ALWAYS " << endl;
		Sleep(2400);
		wout << "\t count on Barnold!\"" << endl << endl;
		wout << "All these tips make you much more confident in your abilities." << endl;
		Sleep(3000);
	}
}