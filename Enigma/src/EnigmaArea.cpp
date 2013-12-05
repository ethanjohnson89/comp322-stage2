/****************************************
Group #: 2
Members: Steve Patterson, James Mart, Nick Halvorsen, Ethan Johnson
Course: Comp 322
Date: 12/4/13
****************************************/

#include "EnigmaArea.h"

EnigmaArea::EnigmaArea() {}

void EnigmaArea::initialize(string name, string description, float x, float y, gl::Texture thumbnailImage, gl::Texture backgroundImage)
{
	EnigmaArea::name = name;
	EnigmaArea::description = description;
	position = Vec2f(x, y);
	EnigmaArea::thumbnailImage = thumbnailImage;
	EnigmaArea::backgroundImage = backgroundImage;
}

void EnigmaArea::drawThumbnail() {
	Vec2f position2 = position + Vec2f(EVENT_WINDOW_X, EVENT_WINDOW_Y);
	Area position3 = Area(position2.x, position2.y, position2.x + AREA_WIDTH, position2.y + AREA_HEIGHT); 
	gl::draw(thumbnailImage, position3);
}

void EnigmaArea::drawBackgroundImage() {


	gl::draw(backgroundImage, EVENT_WINDOW_AREA);//Vec2f(EVENT_WINDOW_X, EVENT_WINDOW_Y)); 
}
