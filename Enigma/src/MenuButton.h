
#ifndef _MENUBUTTON_H
#define _MENUBUTTON_H

#include "GameManager.h"
#include "Command.h"
#include "cinder/gl/gl.h"
#include "globals.h"
#include <string>
using std::string;
using namespace ci;
using namespace windowNS;


class MenuButton
{
private:
	string command; // the command that the button executes when clicked
	gl::Texture image;


public:
	MenuButton() { }
	void initialize(string command, gl::Texture image);
	void draw(int index, int total, int buttonClicked = -1);
	string getAssociatedCommand() { return command; }
	void setAssociatedCommand(string cmd) { command = cmd; }
	void setImage(gl::Texture img){image = img;}
};


#endif