#include "NPC.h"


extern CarryableObject * getCarryableObject(int id);

NPC::NPC(string name, string greeting)
{
	NPC::name = name;
	NPC::greeting = greeting;
}
void NPC::interact(Player* player)
{
	wout << name << " : " << greeting << endl;
}

StandardNPC::StandardNPC(string name,int numOfTopics,...)
{
	StandardNPC::name = name;
	char* s;
	va_list args;
	va_start(args,numOfTopics);
	for (int i = 0; i < numOfTopics; i++)
	{
		s = va_arg(args,char*);
		topics.push_back(s);
		s = va_arg(args,char*);
		bodies.push_back(s);
	}
	va_end(args);
}
void StandardNPC::interact(Player* player)
{
	if (fp != NULL) fp(player);
	else {
		wout << name << " : ";
		int choice = 1;
		vector<string> topics;
		topics = StandardNPC::topics;
		topics.push_back("Nothing now, thank you");
		choice = menu("What do you want to talk about?",topics);
		while (choice != topics.size())	{
			wout << bodies[choice-1] << endl;
			choice = menu("What do you want to talk about?",topics);
		}
	}
}


RamblerNPC::RamblerNPC(string name,int numOfTopics,...)
{
	RamblerNPC::name = name;
	char* s;
	va_list args;
	va_start(args,numOfTopics);
	for (int i = 0; i < numOfTopics; i++)
	{
		s = va_arg(args,char*);
		topics.push_back(s);
		s = va_arg(args,char*);
		bodies.push_back(s);
	}
	va_end(args);
}
void RamblerNPC::interact(Player* player)
{
	wout << name << " : ";
	int choice = 1;
	vector<string> topics;
	topics = StandardNPC::topics;
	topics.push_back("Nothing now, thank you");
	choice = menu("What do you want to talk about?",topics);
	while (choice != topics.size())
	{
		char* s = new char[bodies[choice-1].size()];
		char* lastPercent;
		strcpy(s,bodies[choice-1].c_str());
		lastPercent = strpbrk(s,"%");
		if (lastPercent != NULL)
		{
			wout << strtok(s,"%") << endl;
			getch();
			lastPercent = strpbrk(lastPercent+1,"%");
			while (lastPercent != NULL)
			{
				wout << strtok(NULL,"%") << endl;
				lastPercent = strpbrk(lastPercent+1,"%");
				getch();
			}
			wout << strtok(NULL,"%") << endl;
		}
		else
			wout << s << endl;
		delete [] s;
		choice = menu("What do you want to talk about?",topics);
	}
}


void ShopkeeperNPC::interact(Player* player)
{
	wout << endl << name << ": ";
	int choice = menu("Welcome to my humble shop!", 3, "Browse wares", "Sell items", "Leave");

	if (choice == 1) {
		bool stillLooking = true;
		while (stillLooking) {
			vector<string> itemsForSale;
			vector<int>	itemsForSaleIds;
			for (int i = 0; i < stock.size(); i++) {
				itemsForSale.push_back(getCarryableObject(stock[i])->getName());
				itemsForSaleIds.push_back(getCarryableObject(stock[i])->getId());
			}
			itemsForSale.push_back("Nothing. In fact, I want to leave.");

			wout << endl;
			choice = menu("What do you wanna buy?", itemsForSale);
			CarryableObject* specifiedItem = getCarryableObject(itemsForSaleIds[choice - 1]);

			if (choice == itemsForSale.size()) {// they chose leave
				wout << "Oh, I see how it is." << endl;
				wout << "Have a nice day." << endl;
				stillLooking = false;
			}
			else if (specifiedItem->getValue() > player->getGold()) 
				wout << "I, uh, don't know how to tell you this, but ...\n you don't have enough money for that. Sorry." << endl;
			
			else {
				wout << endl << "\t" << specifiedItem->getDescription() << endl << "\tThis item costs "<< specifiedItem->getValue() << " coins. You have " << player->getGold() << " coins." <<endl << endl;
				int areYouSure = menu("Are you sure you want to buy this item?", 2, "Yes", "No");
				if (areYouSure == 1) {
					wout << "Thanks! Here's your " << specifiedItem->getName() << "." << endl <<endl;
					player->addObjectToInventory(specifiedItem);
					player->addGold(-1 * specifiedItem->getValue()); 
				} else {
					wout << "Maybe next time. " << endl << endl;
				}
			}
		}


	}
	if (choice == 2) {
		wout << endl << "I'm not buying any items at the moment.";
	}
	


	return;
}

void ShopkeeperNPC::addItemToStock(int id)
{
	//stock.push_back(getCarryableObject(id)->getId());
	stock.push_back(id);
	return;
}