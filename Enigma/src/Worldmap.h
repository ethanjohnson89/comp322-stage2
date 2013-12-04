/*
#ifndef _WORLDMAP_H
#define _WORLDMAP_H

#include "area.h"
#include <string>
using std::string;

struct MapLoc
{
	MapLoc(Area* a, int X, int Y, string picfname) {area = a; x = X; y = Y; pictureFilename = picfname;}
	Area* area;
	int x, y;
	string pictureFilename;
};

class Worldmap
{
private: 
	vector<MapLoc> areas;
	int areaIndex;
	int defaultArea;

public:
	Worldmap();

	void draw();
	
	Area* getArea(int index) {return areas[index].area;}
	Area* getCurrentArea() {return getArea(areaIndex);}
	int   getCurrentAreaIndex() {return areaIndex;}
	int	  getAreaCount() {return areas.size();}
	void  setDefaultArea(int a) {defaultArea = a;}
	void  setAreaToDefault() {areaIndex = defaultArea;}

	void  setCurrentArea(int index);
	void  addArea(Area *newArea, int mapX, int mapY, string picFilename);
	Area* replaceArea(int index, Area *newArea);
};
#endif

*/