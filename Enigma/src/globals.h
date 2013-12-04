
#ifndef _GLOBALS_H
#define _GLOBALS_H

#include "cinder/gl/gl.h"
#include<vector>
using std::vector;
#include<string>
using std::string;

using namespace ci;

namespace windowNS
{
	static const int WINDOW_WIDTH  = 1000;
	static const int WINDOW_HEIGHT = 700;

	static const int EVENT_WINDOW_X = 100;
	static const int EVENT_WINDOW_Y = 5;
	static const int EVENT_WINDOW_WIDTH = WINDOW_WIDTH - EVENT_WINDOW_X - 5;
	static const int EVENT_WINDOW_HEIGHT = 350;
	static const Area EVENT_WINDOW_AREA(EVENT_WINDOW_X, EVENT_WINDOW_Y, EVENT_WINDOW_X + EVENT_WINDOW_WIDTH, EVENT_WINDOW_Y + EVENT_WINDOW_HEIGHT);

	static const int CONSOLE_X = 5;
	static const int CONSOLE_Y = EVENT_WINDOW_Y + EVENT_WINDOW_HEIGHT + 5;
	static const int CONSOLE_WIDTH = WINDOW_WIDTH - CONSOLE_X - 200;
	static const int CONSOLE_HEIGHT = WINDOW_HEIGHT - CONSOLE_Y - 5;

	static const int AREA_HEIGHT = 80;
	static const int AREA_WIDTH = 80;

	static const int INVENTORY_X = CONSOLE_X + CONSOLE_WIDTH + 5;
	static const int INVENTORY_Y = CONSOLE_Y;
	static const int INVENTORY_WIDTH = WINDOW_WIDTH - INVENTORY_X - 5;
	static const int INVENTORY_HEIGHT = WINDOW_HEIGHT - INVENTORY_Y - 5;

	static const int DIVIDER_X = 5;
	static const int DIVIDER_Y = EVENT_WINDOW_Y + EVENT_WINDOW_HEIGHT;
	static const int DIVIDER_WIDTH = WINDOW_WIDTH - 10;
	static const int DIVIDER_HEIGHT = 5;
}

#endif

