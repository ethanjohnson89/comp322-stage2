#ifndef __INVENTORY_H
#define __INVENTORY_H

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/Text.h"
#include "globals.h"
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include "Item.h"
using namespace ci;
using namespace ci::app;
using std::string;
using std::map;
using std::vector;
using std::stringstream;
using namespace windowNS;

class Inventory {

public:
	void setup();
	int getItemQuantity(Item item);
	void setItemQuantity(Item item, int quantity);
	int addItem(Item item);
	int deleteItem(Item item);
	vector<string> getAllItems();
	string examineItem(string itemName);
	int getScrollIndex(){return scrollIndex;}
	void incrementScrollIndex();
	void decrementScrollIndex();

	typedef map<Item, int>::iterator InventoryItemIterator;

	InventoryItemIterator getItemIteratorBegin() { return items.begin(); }
	InventoryItemIterator getItemIteratorEnd() { return items.end(); }

	void render();
	void draw();

private:
	map<Item, int> items;
	gl::Texture textTexture;
	Font mFont;
	int scrollIndex;
	int getMaxLines();
	



};

#endif