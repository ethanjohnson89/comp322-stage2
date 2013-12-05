#include "MenuButton.h"

void MenuButton::initialize(string command, gl::Texture image)
{
	MenuButton::command = command;
	MenuButton::image = image;
}

void MenuButton::draw(int index)
{
	gl::draw(image, Area(MENUBUTTONS_X, MENUBUTTONS_Y + index * MENUBUTTONS_HEIGHT, MENUBUTTONS_X + MENUBUTTONS_WIDTH, MENUBUTTONS_Y + (index+1) * MENUBUTTONS_HEIGHT - 1));
}