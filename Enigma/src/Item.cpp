#include "Item.h"

Item::Item() {}

Item::Item(string name, string description) {
	Item::name = name;
	Item::description = description;
}

string Item::examine() const {

	return " ITEM NAME: \n"+name+"\n DESCRIPTION: \n"+description;
	
}