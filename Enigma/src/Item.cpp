#include "Item.h"

Item::Item() {}

Item::Item(string name, string description) {
	Item::name = name;
	Item::description = description;
}

string Item::examine() {

	return "ITEM NAME: \n"+name+"\n DESCRIPTION: \n"+description;
	
}