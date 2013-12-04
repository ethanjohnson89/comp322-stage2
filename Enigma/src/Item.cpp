#include "Item.h"

Item::Item() {}

Item::Item(int id, string name, string description) {
	Item::id = id;
	Item::name = name;
	Item::description = description;
}

string Item::examine() {

	return "ITEM NAME: \n"+name+"\n DESCRIPTION: \n"+description;
	
}