

#include "worldmap.h"

Worldmap::Worldmap()
{
	areaIndex = 0;
	defaultArea = 0;
	backgroundFilename = "none";
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
	//if (backgroundFilename != "none")
	//	gl::draw(background, windowNS::eventWindowBounds);

	for (int i = 0; i < areas.size(); i++)
		areas[i]->drawThumbnail();
}

int Worldmap::mapClicked(int x, int y)
{
	int areaWidth = 80;
	int areaHeight = 80;


	for (int i = 0; i < areas.size(); i++)
	{
		if (x > areas[i]->getPosition().x && x < areas[i]->getPosition().x + areaWidth && 
			y > areas[i]->getPosition().y && y < areas[i]->getPosition().y + areaHeight)
		{
			setCurrentArea(i);
			return i;
		}
	}
	return -1;
}