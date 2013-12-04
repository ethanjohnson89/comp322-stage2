#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "console.h"
#include "GameManager.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class EnigmaApp : public AppNative {
private:
	GameManager gm;
	Console con;
public:
	void setup();
	void prepareSettings(Settings *settings);
	void mouseDown( MouseEvent event );	
	void keyDown( KeyEvent event );
	void update();
	void draw();
};

void EnigmaApp::prepareSettings( Settings *settings ){
    settings->setWindowSize( 1000, 700 );
}


void EnigmaApp::setup()
{
	con.setup();
	con.setWidth(600);
	con.setHeight(200);
	con.setX(0);
	con.setY(505);
}

void EnigmaApp::mouseDown( MouseEvent event )
{
}

void EnigmaApp::keyDown( KeyEvent event ) 
{
	if( event.getCode() == KeyEvent::KEY_RETURN )
		con.sendLine();
	else if (event.getCode() == KeyEvent::KEY_BACKSPACE)
		con.backspace();
	else if (event.getChar() >= ' ' && event.getChar() < '~')
		con.sendChar(event.getChar());
}

void EnigmaApp::update()
{
}

void EnigmaApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 30, 0 ) );  
	con.draw();
}

CINDER_APP_NATIVE( EnigmaApp, RendererGl )
