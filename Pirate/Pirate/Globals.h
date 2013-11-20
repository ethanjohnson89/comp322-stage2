#ifndef INCLUDES_H
#define INCLUDES_H

#include"Area.h"

void init();
vector<string> &split(const string &s, char delim, vector<string> &elems);
vector<string> split(const string &s, char delim);
void gatherInputInformationFor(const vector<string>& vec, int& orderNum, bool& wordTypePresent, vector<string> theInput, string& theWord);
int searchStringVec(vector<string> vec, string key);
Area * getArea(int id);
Area * getArea(string name);
Vessel* getVessel(string);
Vessel* getVessel(int);
CarryableObject* getCarryableObject(int id);
CarryableObject* getCarryableObject(string name);
bool stringInVect(string, vector<string>&);
bool stringInVect(string, vector<string>&);
void showVessel(int id);

void buyFish(Player* player);
void sellBait(Player* player);
void upgradeShip(Player* player);

template <class T>
int search(vector<T> vec, T key) {
	int num = vec.size();
	bool found = false;
	int i = 0;
	for (i = 0;  i < num; i++) {
		if (vec[i] == key) {
			found = true;
			break;
		}
	}

	if (found == true) return i;
	else return 0;
}


#endif