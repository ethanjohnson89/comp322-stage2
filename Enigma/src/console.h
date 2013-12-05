#ifndef _CONSOLE_H
#define _CONSOLE_H

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/Text.h"
#include "boost/thread/mutex.hpp"
#include "globals.h"
#include <string>
#include <sstream>
#include <vector>
using std::vector;
using std::stringstream;

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace windowNS;

class Console {
private:
	void adjustMaxLines();
	int  getLineCharsLimit();

	gl::Texture mTextTexture;
	Vec2f mSize;
	Font mFont;
	int x, y, width, height;
	string inputLine;
	vector<string> lines;
	int maxLines;
	string inputLinePrefix;
	string font;
	int fontSize;
	Color textColor;
	Color backColor;

	boost::mutex lineBufferMutex;

	// These functions will be called by the friend class EnigmaApp
	friend class EnigmaApp;
	void sendChar(char a);
	string sendLine();
	void output(string s); // only accessible within Console and EnigmaApp, see the friend function below for other uses
	void backspace();
	friend void output(Console *cons, string s) { cons->output(s); } // friend function for use by any class that needs to print output to the console

public:
	Console();
	void setup();
	void update();
	void draw();
	void render();

	int getWidth(){return width;}
	void setWidth(int a){width = a; adjustMaxLines();}
	int getHeight(){return height;}
	void setHeight(int a){height = a; adjustMaxLines();}
	int getX(){return x;}
	int getY(){return y;}
	void setX(int a){x = a;}
	void setY(int a){y = a;}
	void setXY(int a, int b){x = a; y = b;}
	void setInputLinePrefix(string s){inputLinePrefix = s;}
	void setFontSize(int a);
	int  getFontSize(){return fontSize;}
	void setTextColor(Color c){textColor = c;}
	void setBackColor(ColorA c){backColor = c;}
	ColorA getTextColor(){return textColor;}
	ColorA getBackColor(){return backColor;}
	
};

#endif