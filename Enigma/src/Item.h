/****************************************
Group #: 2
Members: Steve Patterson, James Mart, Nick Halvorsen, Ethan Johnson
Course: Comp 322
Date: 12/4/13
****************************************/

#ifndef __ITEM_H
#define __ITEM_H

#include <algorithm>
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
		string myName_lower = name, otherName_lower = other.name;
		std::transform(myName_lower.begin(), myName_lower.end(), myName_lower.begin(), ::tolower);
		std::transform(otherName_lower.begin(), otherName_lower.end(), otherName_lower.begin(), ::tolower);
		if(myName_lower < otherName_lower)
			return true;
		return false;
    }

	bool operator==(const Item& other) const
	{
		string myName_lower = name, otherName_lower = other.name;
		std::transform(myName_lower.begin(), myName_lower.end(), myName_lower.begin(), ::tolower);
		std::transform(otherName_lower.begin(), otherName_lower.end(), otherName_lower.begin(), ::tolower);
		if(myName_lower == otherName_lower)
			return true;
		return false;
	}

};

#endif