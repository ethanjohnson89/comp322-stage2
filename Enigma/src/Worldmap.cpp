/*

#include "worldmap.h"

Worldmap::Worldmap()
{
	areaIndex = -1;
	defaultArea = -1;
}

Area* Worldmap::replaceArea(int index, Area *newArea)
{
	Area* oldArea = areas[index];
	areas[index] = newArea;
	return oldArea;
}

void Worldmap::setCurrentArea(int index)
{
	if (index < areas.size() && index >= 0) 
		areaIndex = index;
}

void Worldmap::addArea(Area *newArea, int mapX, int mapY, string picFilename);
{
	areas.push_back(MapLoc(newArea, mapX, mapY, picFilename));
}

void Worldmap::draw()
{
	// draw
}


*/