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
	gl::draw(thumbnailImage, position2);
}

void EnigmaArea::drawBackgroundImage() {


	gl::draw(backgroundImage, EVENT_WINDOW_AREA);//Vec2f(EVENT_WINDOW_X, EVENT_WINDOW_Y)); 
}
