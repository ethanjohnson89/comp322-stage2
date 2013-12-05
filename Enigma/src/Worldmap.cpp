
#include "Worldmap.h"

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
		gl::draw(background, EVENT_WINDOW_AREA);

	for (int i = 0; i < areas.size(); i++)
		areas[i]->drawThumbnail();
}

int Worldmap::mapClicked(int x, int y)
{
	for (int i = 0; i < areas.size(); i++)
	{
		if (x > areas[i]->getPosition().x + EVENT_WINDOW_X && x < areas[i]->getPosition().x + AREA_WIDTH  + EVENT_WINDOW_X && 
			y > areas[i]->getPosition().y + EVENT_WINDOW_Y && y < areas[i]->getPosition().y + AREA_HEIGHT + EVENT_WINDOW_Y)
		{
			return i;
		}
	}
	return -1;
}