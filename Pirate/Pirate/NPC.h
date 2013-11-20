#ifndef __NPC_H
#define __NPC_H

#include "Menu.h"
#include "Player.h"

class Player;

class NPC
{
protected:
	string greeting;
	string name;
public:
	NPC(){;}
	NPC(string name,string greeting);
	string getName(){return name;}
	virtual void interact(Player* );
};

class StandardNPC : public NPC
{
protected:
	vector<string> topics;
	vector<string> bodies;
	void (*fp)(Player* player);

public:
	StandardNPC(){;}
	StandardNPC(string n, void (*tfp)(Player*)){name = n; fp = tfp;}
	StandardNPC(string name,int numOfTopics,...);
	void interact(Player*);
};

class RamblerNPC : public StandardNPC
{
public:
	RamblerNPC(){;}
	RamblerNPC(string name,int numOfTopics,...);
	void interact(Player *);
};

class ShopkeeperNPC : public NPC
{
protected:
	vector<int> stock;

public:
	ShopkeeperNPC(){;}
	ShopkeeperNPC(string name){ShopkeeperNPC::name = name;}
	ShopkeeperNPC(string name, vector<int> stock){ShopkeeperNPC::name = name; ShopkeeperNPC::stock = stock;} 
	void interact(Player*);
	void addItemToStock(int id);
	// to do: addItemToStock(string name)

};

#endif