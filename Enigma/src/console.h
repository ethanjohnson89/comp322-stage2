#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/Text.h"
#include <string>
#include <sstream>
#include <vector>
using std::vector;
using std::stringstream;

using namespace ci;
using namespace ci::app;
using namespace std;

class Console {
private:
	void adjustMaxLines();

	gl::Texture mTextTexture;
	Vec2f mSize;
	Font mFont;

	int x, y;
	string inputLine;
	vector<string> lines;
	int width, height;
	int maxLines;
	string inputLinePrefix;
	string font;
	int fontSize;
	Color textColor;
	Color backColor;

public:
	Console();
	void setup();
	void update();
	void draw();
	void render();

	void sendChar(char a); // make into private GameManager friend function
	string sendLine();	   // make into private GameManager friend function
	void output(string s); 
	void backspace();

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