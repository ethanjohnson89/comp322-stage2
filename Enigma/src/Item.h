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
	Item(int id, string name, string description);
	string examine();
	
	//setters and getters
	int getId() { return id; }
	void setId(int id) { Item::id = id; }
	string getName() { return name; }
	void setName(string name) { Item::name = name; }
	string getDescription() { return description; }
	void setDescription(string description) { Item::description = description; }


	//comparator for usage in STL map template
	bool operator<( const Item& other) const
      {
          if ( id < other.id )
          {
              return true;
          } else {
			  return false;
		  }
      }

};

#endif