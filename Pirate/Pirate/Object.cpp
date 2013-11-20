#include "Object.h"

Object operator<(Object left, Object right)
{
	if (left.getId() < right.getId())
		return left;
	else
		return right;
}

Fish::Fish(int id, string name, string description, int rarity, int value, int exp)
{
	Fish::id = id;
	Fish::name = name;
	Fish::description = description;
	Fish::rarity = rarity;
	Fish::value = value;
	Fish::experience = exp;
	sellable = true;
}