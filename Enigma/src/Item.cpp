/****************************************
Group #: 2
Members: Steve Patterson, James Mart, Nick Halvorsen, Ethan Johnson
Course: Comp 322
Date: 12/4/13
****************************************/

#include "Item.h"

Item::Item() {}

Item::Item(string name, string description) {
	Item::name = name;
	Item::description = description;
}

string Item::examine() const {

	return " ITEM NAME: \n"+name+"\n DESCRIPTION: \n"+description;
	
}