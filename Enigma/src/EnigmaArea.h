/****************************************
Group #: 2
Members: Steve Patterson, James Mart, Nick Halvorsen, Ethan Johnson
Course: Comp 322
Date: 12/4/13
****************************************/

#ifndef __ENIGMA_AREA_H
#define __ENIGMA_AREA_H

#include <string>
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/Vector.h"
#include "cinder/app/AppNative.h"
#include "globals.h"
using std::string;
using namespace ci;
using namespace ci::app;
using namespace windowNS;

class EnigmaArea {

private:
	string name;
	string description;
	Vec2f position;
	gl::Texture thumbnailImage;
	gl::Texture backgroundImage;

public:
	EnigmaArea();
	virtual void initialize(string name, string description, float x, float y, gl::Texture thumbnailImage, gl::Texture backgroundImage);
	virtual void drawThumbnail();
	virtual void drawBackgroundImage();

	virtual string getName() { return name; }
	virtual void setName(string name) { EnigmaArea::name = name; }
	virtual string getDescription() { return description; }
	virtual void setDescription(string description) { EnigmaArea::description = description; }
	virtual Vec2f getPosition() { return position; }
	virtual void setPosition(Vec2f pos) { position = pos; }
	virtual gl::Texture getBackgroundImage() { return backgroundImage; }
};

#endif