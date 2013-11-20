// WisePrint.h
// Nick Halvorsen
// Oct-2013

/*	
	WisePrint is similar to std::cout, but it doesn't split words between lines.
	Use:
	wout << "abcd";
*/

#ifndef WISEPRINT_H
#define WISEPRINT_H

#include <iostream>
#include <sstream>
#include <string>
#include <Windows.h>
using std::stringstream;
using std::string;


typedef std::basic_ostream<char, std::char_traits<char> > CoutType;
typedef CoutType& (*StandardEndLine)(CoutType&);


string getNextWordFromString(string bigString, int& pos);
int getConsolePosX();

class WisePrint
{
public:

	template <class T>
	friend WisePrint& operator<<(WisePrint& out, T thing);
	WisePrint& operator<<(StandardEndLine manip);
private:
	WisePrint& endl(WisePrint& wp);
};

template <class T>
WisePrint& operator<<(WisePrint& out, T thing)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo (GetStdHandle (STD_OUTPUT_HANDLE), &csbi);
	int lineLength = csbi.srWindow.Right + 1;
	int extraChars = getConsolePosX();
	
	int posAt = 0;
	stringstream ss;
	ss << thing;
	string thingString;
	thingString = ss.str();
	bool lastCharWasASpace = true;
	
	string nextWord = "";
	string nextLine = "";

	while ((unsigned)posAt < thingString.length())
	{
		nextWord = getNextWordFromString(thingString, posAt);

		if (getConsolePosX() + nextWord.length() == lineLength)
			if (nextWord[nextWord.length() - 1] == ' ')
				lastCharWasASpace = true;
			else
				lastCharWasASpace = false;

		if (getConsolePosX() + nextWord.length() > (unsigned)lineLength)
			std::cout << std::endl;

		if (!lastCharWasASpace && getConsolePosX() == 0 && nextWord == " ")
			lastCharWasASpace = true;
		else
			std::cout << nextWord;
	}

	return out;
}

static WisePrint wout;

#endif