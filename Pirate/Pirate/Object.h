#ifndef __OBJECT_H
#define __OBJECT_H

#include <iostream>
#include <string>


using std::string;

class Object
{
protected:
	string name;
	string description;
	int id;
public:
	Object(){name="error"; id = -1;}
	Object operator<(Object right);
	string getName(){return name;}
	string getDescription(){return description;}
	int    getId(){return id;}
	void examine();
};

class CarryableObject : public Object
{
protected:
	int value;
	bool sellable;
public:
	CarryableObject(){;}
	CarryableObject(int id, string name, string description, int value){CarryableObject::id = id; CarryableObject::name = name; CarryableObject::description = description; CarryableObject::value = value;}
	virtual void interact(){;}
	bool isSellable(){return sellable;}
	int getValue(){return value;}
};

class Fish : public CarryableObject
{
public:
	Fish(int id, string name, string description, int rarity, int value, int exp);
	int getRarity(){return rarity;}
	int getExperience(){return experience;}
private:
	int rarity;
	int experience;
};

class Food : public CarryableObject
{
protected:
	int nutritionValue;
public:
	Food(){;}
	Food(string name, string description, int value, int nutrition){Food::name = name; Food::description = description; Food::value = value; Food::nutritionValue = nutrition;}
	//void consume(){wout << "Mmm. That was good" << std::endl;}
};

class Vessel : public Object
{
protected:
	int health;
	int capacity;
	int price;
public:
	Vessel(int theId, string theName, int theHealth, int theCapacity, string theDescription, int thePrice){id=theId; name=theName;  health=theHealth; capacity=theCapacity; description=theDescription;price = thePrice;}
	int getHealth() {return health;}
	int subtractHealth(int amount) {health -= amount;}
	void setHealth(int level) {health = level;}
	int getID() {return id;}
	int getCapacity() {return capacity;}
	int getPrice(){return price;}
};

#endif