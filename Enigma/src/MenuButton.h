
#ifndef _MENUBUTTON_H
#define _MENUBUTTON_H

#include "GameManager.h"
#include "cinder/gl/gl.h"
#include "globals.h"
#include <string>
using std::string;
using namespace ci;
using namespace windowNS;


class MenuButton
{
private:
	CommandFunction function; // the function that the button executes when clicked
	string commandString;    //  the message that the button displays when clicked
	gl::Texture image;


public:
	MenuButton();
	void draw(int index);
	CommandFunction getFunction(){return function;}
	void setFunction(CommandFunction f){function = f;}
	void setCommandString(string s){commandString = s;}
	string getCommandString() {return commandString;}
	void setImage(gl::Texture img){image = img;}

};


#endif