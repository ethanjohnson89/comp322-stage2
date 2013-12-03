#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class EnigmaApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void EnigmaApp::setup()
{
}

void EnigmaApp::mouseDown( MouseEvent event )
{
}

void EnigmaApp::update()
{
}

void EnigmaApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( EnigmaApp, RendererGl )
