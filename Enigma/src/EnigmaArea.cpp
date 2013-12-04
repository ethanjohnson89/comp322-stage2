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
	gl::draw(thumbnailImage, position);
}

void EnigmaArea::drawBackgroundImage() {
	gl::draw(backgroundImage, Vec2f(0.0f, 0.0f)); // change 0.0f to top-left corner of event area when we have it in Globals.h
}