#include "WisePrint.h"

int getConsolePosX()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo (GetStdHandle (STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.X;
}


string getNextWordFromString(string bigString, int& pos)
{
	string tempString = "";

	tempString += bigString[pos++];

	if (tempString == " " || tempString == "\n" || tempString == "\t")
		return tempString;

	while (pos < (unsigned) bigString.length() && bigString[pos] != ' ' && bigString[pos] != '\n')
		tempString+= bigString[pos++];

	return tempString;
}

WisePrint& WisePrint::endl(WisePrint& wp)
{
    std::cout << std::endl;
    return wp;
}


WisePrint& WisePrint::operator<<(StandardEndLine manip)
{
    manip(std::cout);
    return *this;
}