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
	void initialize(string name, string description, float x, float y, gl::Texture thumbnailImage, gl::Texture backgroundImage);
	void drawThumbnail();
	void drawBackgroundImage();
//	Command::CommandFunction onEntry;

	//getters and setters
	string getName() { return name; }
	void setName(string name) { EnigmaArea::name = name; }
	string getDescription() { return description; }
	void setDescription(string description) { EnigmaArea::description = description; }
	Vec2f getPosition() { return position; }
	void setPosition(Vec2f pos) { position = pos; }
};

#endif