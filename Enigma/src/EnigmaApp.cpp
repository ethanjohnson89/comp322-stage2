#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Worldmap.h"
#include "console.h"
#include "GameManager.h"
#include "globals.h"
#include "EnigmaArea.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class EnigmaApp : public AppNative {
private:
	GameManager gm;
	Console con;
	Worldmap worldmap;
	bool mapActive;
	void eventAreaClicked(MouseEvent event);
	EnigmaArea testArea, testArea2;
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
	con.setY(windowNS::eventWindowY2 + 10);
	testArea.initialize("area", "this is an area", 0.0f, 0.0f, gl::Texture(loadImage(loadAsset("noImageAvailable.jpg"))), gl::Texture(loadImage(loadAsset("noImageAvailable.jpg"))));
	testArea2.initialize("area2", "this is an area", 200.0f, 0.0f, gl::Texture(loadImage(loadAsset("noImageAvailable.jpg"))), gl::Texture(loadImage(loadAsset("noImageAvailable.jpg"))));
	worldmap.setBackgroundPicture(gl::Texture(loadImage(loadAsset("worldmap1.jpg"))));
	worldmap.addArea(&testArea);
	worldmap.addArea(&testArea2);
}

void EnigmaApp::mouseDown( MouseEvent event )
{
	if (event.getX() > windowNS::eventWindowX  &&
		event.getX() < windowNS::eventWindowX2 &&
		event.getY() > windowNS::eventWindowY  &&
		event.getY() < windowNS::eventWindowY2)
	{
		eventAreaClicked(event);
	}

}

void EnigmaApp::eventAreaClicked(MouseEvent event)
{
	if (mapActive)
		worldmap.mapClicked(event.getX(), event.getY());
}

void EnigmaApp::keyDown( KeyEvent event ) 
{
	if (event.getChar() == '-') // debug
	{
		con.output("current area: " + worldmap.getCurrentArea()->getName());
		return;
	}

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
	worldmap.draw();
}

CINDER_APP_NATIVE( EnigmaApp, RendererGl )
