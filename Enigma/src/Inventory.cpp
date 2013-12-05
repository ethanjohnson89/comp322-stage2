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
	
	render();
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
	render();

}

int Inventory::deleteItem(Item item) {

	if (items.find(item) != items.end()) {
		int previousQuantity = items[item];
		return previousQuantity;
	} else {
		return 0;
	}
	render();
}

vector<string> Inventory::getAllItems() {

	vector<string> inventory;
	Item tempItem;

	for (map<Item, int>::iterator it = items.begin(); it != items.end(); ++it){
		stringstream text;
		tempItem = it->first;
		text << tempItem.getName() << ": " << it->second;
		inventory.push_back(text.str());
		text.clear();
    }

	return inventory;
}

string Inventory::examineItem(string itemName)
{
	auto itemInInventory = items.find(Item(itemName, "")); // note that the description doesn't matter here since Item::operator== compares based only on name
	if(itemInInventory != items.end())
		return itemInInventory->first.examine();
	else
		return "You don't have one of those!";
}

void Inventory::render() {

	vector<string> items = getAllItems();
	int maxLines = getMaxLines();
	string txt = "INVENTORY:\n";
	for (unsigned int i = 0; i+scrollIndex < items.size() && i < maxLines; i++)
	{
		txt += items[i+scrollIndex];
		txt += "\n";
	}

	TextBox tbox = TextBox().alignment( TextBox::LEFT ).font( mFont ).size( Vec2i( INVENTORY_WIDTH, INVENTORY_HEIGHT ) ).text( txt );
	tbox.setColor(INVENTORY_TEXT_COLOR);
	tbox.setBackgroundColor(INVENTORY_BACK_COLOR);
	Vec2i sz = tbox.measure();
	textTexture = gl::Texture( tbox.render() );

}

void Inventory::draw() {


	gl::setMatricesWindow( getWindowSize() );
	gl::enableAlphaBlending();
	Vec2f pos(static_cast<float>(INVENTORY_X), static_cast<float>(INVENTORY_Y));

	if( textTexture )
		gl::draw( textTexture, pos );


}

void Inventory::setup()
{
	mFont = Font(INVENTORY_FONT, INVENTORY_FONT_SIZE );
	scrollIndex = 0;
	render();
}

void Inventory::incrementScrollIndex()
{
	if (!(scrollIndex +1 + getMaxLines() > items.size()))
		scrollIndex++;

	render();
}

void Inventory::decrementScrollIndex()
{
	if (scrollIndex > 0)
		scrollIndex--;

	render();
}

int Inventory::getMaxLines(){

	return INVENTORY_HEIGHT / (INVENTORY_FONT_SIZE / 1.1);
}