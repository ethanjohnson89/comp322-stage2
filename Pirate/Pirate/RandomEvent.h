#pragma once

#ifndef RANDOMEVENT_H
#define RANDOMEVENT_H

#include "Player.h"
class Player;

class RandomEvent
{
public:
	RandomEvent(int r, void (*func)(Player*), bool stopfish = false, int place = -1){rarity = r; function = func, stopFish = stopfish; placeId = place;}
	int getRarity(){return rarity;}
	bool stopFishing(){return stopFish;}
	int getWhere(){return placeId;}
	void doEvent(Player* p){function(p);}

private:
	int placeId; // place = -1 means everywhere
	int rarity;
	void (*function)(Player* play);
	bool stopFish;

};
#endif