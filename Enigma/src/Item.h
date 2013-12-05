#ifndef __ITEM_H
#define __ITEM_H

#include <string>
using std::string;

class Item {

private:

	int id;
	string name;
	string description;

public:

	Item();
	Item(string name, string description);
	string examine() const;
	
	//setters and getters
	string getName() { return name; }
	void setName(string name) { Item::name = name; }
	string getDescription() { return description; }
	void setDescription(string description) { Item::description = description; }


	//comparator for usage in STL map template
	bool operator<( const Item& other) const
    {
		if(name < other.name)
			return true;
		return false;
    }

	bool operator==(const Item& other) const
	{
		if(name == other.name)
			return true;
		return false;
	}

};

#endif