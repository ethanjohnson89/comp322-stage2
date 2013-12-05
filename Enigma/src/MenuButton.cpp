#include "MenuButton.h"

MenuButton::MenuButton()
{
	commandString = "";
}

void MenuButton::initialize(CommandFunction function, string commandString, gl::Texture backgroundImage)
{
	MenuButton::function = function;
	MenuButton::commandString = commandString;
	image = backgroundImage;
}

void MenuButton::draw(int index)
{
	gl::draw(image, Area(MENUBUTTONS_X, MENUBUTTONS_Y + index * MENUBUTTONS_HEIGHT, MENUBUTTONS_X + MENUBUTTONS_WIDTH, MENUBUTTONS_Y + (index+1) * MENUBUTTONS_HEIGHT - 1));
}