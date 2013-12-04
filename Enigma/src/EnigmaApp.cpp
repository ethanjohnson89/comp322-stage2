#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "GameManager.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class EnigmaApp : public AppNative {
private:
	GameManager gm;
	Console con;
	Worldmap worldmap;
	bool mapActive;
	bool eventAreaClicked(MouseEvent event);
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
    settings->setWindowSize( WINDOW_WIDTH, WINDOW_HEIGHT );
}


void EnigmaApp::setup()
{
	con.setup();
	testArea.initialize("area", "this is an area", 0.0f, 0.0f, gl::Texture(loadImage(loadAsset("area1.jpg"))), gl::Texture(loadImage(loadAsset("area1.jpg"))));
	testArea2.initialize("area2", "this is an area2", 200.0f, 0.0f, gl::Texture(loadImage(loadAsset("area1.jpg"))), gl::Texture(loadImage(loadAsset("area1.jpg"))));
	worldmap.setBackgroundPicture(gl::Texture(loadImage(loadAsset("worldmap1.jpg"))));
	worldmap.addArea(&testArea);
	worldmap.addArea(&testArea2);
	con.output("--- Welcome to the Enigma engine. ---");
	con.output(" ");
}

void EnigmaApp::mouseDown( MouseEvent event )
{
	if (eventAreaClicked(event)) {
		if (mapActive)
		{
			int oldArea = worldmap.getCurrentAreaIndex();
			int newArea = worldmap.mapClicked(event.getX(), event.getY());
			if (newArea != -1 && newArea != oldArea)
			{
				worldmap.setCurrentArea(newArea);
				con.output("You have entered " + worldmap.getArea(newArea)->getName());
			}
		}
	}
}

bool EnigmaApp::eventAreaClicked(MouseEvent event)
{
	return 
		event.getX() > EVENT_WINDOW_X  && 
		event.getX() < EVENT_WINDOW_X + EVENT_WINDOW_WIDTH &&	
		event.getY() > EVENT_WINDOW_Y  && 
		event.getY() < EVENT_WINDOW_Y + EVENT_WINDOW_HEIGHT;
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
	gl::drawSolidRect(Rectf(windowNS::DIVIDER_X, windowNS::DIVIDER_Y, windowNS::DIVIDER_WIDTH + windowNS::DIVIDER_X, windowNS::DIVIDER_HEIGHT + windowNS::DIVIDER_Y));
}

CINDER_APP_NATIVE( EnigmaApp, RendererGl )
