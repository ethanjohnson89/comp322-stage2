#include "MenuButton.h"

void MenuButton::initialize(string command, gl::Texture image)
{
	MenuButton::command = command;
	MenuButton::image = image;
}

void MenuButton::draw(int index, int total, int buttonClicked)
{
	
	int bufferSize = ((EVENT_WINDOW_HEIGHT - MENUBUTTONS_Y) - (MENUBUTTONS_HEIGHT * total)) / total; 
	if (buttonClicked==-1) gl::draw(image, Area(MENUBUTTONS_X, MENUBUTTONS_Y + index * (MENUBUTTONS_HEIGHT+bufferSize), MENUBUTTONS_X + MENUBUTTONS_WIDTH, MENUBUTTONS_Y + index * (MENUBUTTONS_HEIGHT+bufferSize) + MENUBUTTONS_HEIGHT));
	else gl::draw(image, Area(MENUBUTTONS_X+2, (MENUBUTTONS_Y + index * (MENUBUTTONS_HEIGHT+bufferSize))+2, MENUBUTTONS_X + MENUBUTTONS_WIDTH - 5, (MENUBUTTONS_Y + index * (MENUBUTTONS_HEIGHT+bufferSize) + MENUBUTTONS_HEIGHT)-5));
}