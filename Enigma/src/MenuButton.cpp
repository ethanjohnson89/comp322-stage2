#include "MenuButton.h"

void MenuButton::initialize(string command, gl::Texture image)
{
	MenuButton::command = command;
	MenuButton::image = image;
}

void MenuButton::draw(int index, int total)
{
	int bufferSize = ((EVENT_WINDOW_HEIGHT - MENUBUTTONS_Y) - (MENUBUTTONS_HEIGHT * total)) / total; 
	gl::draw(image, Area(MENUBUTTONS_X, MENUBUTTONS_Y + index * (MENUBUTTONS_HEIGHT+bufferSize), MENUBUTTONS_X + MENUBUTTONS_WIDTH, MENUBUTTONS_Y + index * (MENUBUTTONS_HEIGHT+bufferSize) + MENUBUTTONS_HEIGHT));
}