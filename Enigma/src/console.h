#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/Text.h"
#include <vector>
using std::vector;

using namespace ci;
using namespace ci::app;
using namespace std;

class Console {
private:
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

	void sendChar(char a);
	string sendLine();
	void output(string s); 
	void backspace();

	int getWidth(){return width;}
	int getHeight(){return height;}
	void setWidth(int a){width = a;}
	void setHeight(int a){height = a;}
	int getX(){return x;}
	int getY(){return y;}
	void setX(int a){x = a;}
	void setY(int a){y = a;}
	void setXY(int a, int b){x = a; y = b;}
	void setMaxLines(int a){maxLines = a;}
	void setInputLinePrefix(string s){inputLinePrefix = s;}
	void setFont(string s){font = s;mFont = Font( font, fontSize );}
	void setFontSize(int a){fontSize = a;mFont = Font( font, fontSize );}
	void setTextColor(Color c){textColor = c;}
	void setBackColor(ColorA c){backColor = c;}
	
};