
#include "worldmap.h"

Worldmap::Worldmap()
{
	areaIndex = 0;
	defaultArea = 0;
	hasBackground = false;
	
}


void Worldmap::setCurrentArea(int index)
{
	if (index < areas.size() && index >= 0) 
		areaIndex = index;
}

void Worldmap::addArea(EnigmaArea *newArea)
{
	areas.push_back(newArea);
}

void Worldmap::draw()
{
	if (hasBackground)
		gl::draw(background, Area(windowNS::eventWindowX, windowNS::eventWindowY, windowNS::eventWindowX2, windowNS::eventWindowY2));

	for (int i = 0; i < areas.size(); i++)
		areas[i]->drawThumbnail();
}

int Worldmap::mapClicked(int x, int y)
{
	int areaWidth = 80;
	int areaHeight = 80;


	for (int i = 0; i < areas.size(); i++)
	{
		if (x > areas[i]->getPosition().x + windowNS::eventWindowX && x < areas[i]->getPosition().x + areaWidth  + windowNS::eventWindowX && 
			y > areas[i]->getPosition().y + windowNS::eventWindowY && y < areas[i]->getPosition().y + areaHeight + windowNS::eventWindowY)
		{
			return i;
		}
	}
	return -1;
}