#ifndef __INVENTORY_H
#define __INVENTORY_H

#include <vector>
#include <string>
#include <sstream>
#include <map>
#include "Item.h"
using std::string;
using std::map;
using std::vector;
using std::stringstream;

class Inventory {

public:
	int getItemQuantity(Item item);
	void setItemQuantity(Item item, int quantity);
	int addItem(Item item);
	int deleteItem(Item item);
	vector<string> getAllItems();

	typedef map<Item, int>::iterator InventoryItemIterator;

	InventoryItemIterator getItemIteratorBegin() { return items.begin(); }
	InventoryItemIterator getItemIteratorEnd() { return items.end(); }

private:
	map<Item, int> items;
	



};

#endif