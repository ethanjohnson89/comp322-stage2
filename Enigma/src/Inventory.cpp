#include "Inventory.h"


int Inventory::getItemQuantity(Item item) {

	if(items.find(item) == items.end()) {
		return 0; // throw itemDoesntExist exception?
	} else {
		// in inventory
		return items[item];
	}
}

int Inventory::addItem(Item item) {

	if(items.find(item) == items.end()) {
		// not in inventory
		items[item] = 1;
	} else {
		//in inventory
		items[item] = items[item] + 1;
	}

	return items[item];
}

void Inventory::setItemQuantity(Item item, int quantity) {
	
	if (quantity == 0) {
		items.erase(item);
		return;
	}
	if (items.find(item) != items.end()) {
		items[item] = quantity;
	} 

}

int Inventory::deleteItem(Item item) {

	if (items.find(item) != items.end()) {
		int previousQuantity = items[item];
		return previousQuantity;
	} else {
		return 0;
	}
}

vector<string> Inventory::getAllItems() {

	vector<string> inventory;
	stringstream text;
	Item tempItem;

	for (map<Item, int>::iterator it = items.begin(); it != items.end(); ++it){
		tempItem = it->first;
		text << tempItem.getName() << ": " << it->second;
		inventory.push_back(text.str());
		text.clear();
    }

	return inventory;
}