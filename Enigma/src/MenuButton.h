/****************************************
Group #: 2
Members: Steve Patterson, James Mart, Nick Halvorsen, Ethan Johnson
Course: Comp 322
Date: 12/4/13
****************************************/

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
	virtual void initialize(string command, gl::Texture image);
	virtual void draw(int index, int total, int buttonClicked = -1);
	virtual string getAssociatedCommand() { return command; }
	virtual void setAssociatedCommand(string cmd) { command = cmd; }
	virtual void setImage(gl::Texture img){image = img;}
};


#endif