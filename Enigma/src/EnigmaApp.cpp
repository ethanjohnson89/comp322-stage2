#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "GameManager.h"
#include "CommandFunctions.h"
#include "globals.h"
#include "EnigmaArea.h"
#include "MenuButton.h"

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
	bool menuButtonAreaClicked(MouseEvent event);
	EnigmaArea testArea, testArea2;
	vector<MenuButton> menuButtons;
	MenuButton button1, button2, button3, button4;
	Item testItem;
	Inventory inv;
	int menuButtonClicked;
public:
	void outputDebugInfo(GameManager*, vector<string>);
	void setup();
	void prepareSettings(Settings *settings);
	void mouseDown( MouseEvent event );	
	void keyDown( KeyEvent event );
	void update();
	void draw();
};

void EnigmaApp::prepareSettings( Settings *settings ){
	Window::Format fmt; fmt.setTitle("Enigma Text-Adventure Engine V1.0");
	fmt.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	settings->prepareWindow(fmt);
}


void EnigmaApp::setup()
{

	con.setup();
	testArea.initialize("area", "this is an area", 0.0f, 0.0f, gl::Texture(loadImage(loadAsset("area1.jpg"))), gl::Texture(loadImage(loadAsset("area1.jpg"))));
	testArea2.initialize("area2", "this is an area2", 200.0f, 0.0f, gl::Texture(loadImage(loadAsset("area1.jpg"))), gl::Texture(loadImage(loadAsset("area1.jpg"))));

	worldmap.setBackgroundPicture(gl::Texture(loadImage(loadAsset("worldmap1.jpg"))));
	worldmap.addArea(&testArea);
	worldmap.addArea(&testArea2);

	button1.setImage(gl::Texture(loadImage(loadAsset("button1.jpg"))));
	button2.setImage(gl::Texture(loadImage(loadAsset("button2.jpg"))));
	button3.setImage(gl::Texture(loadImage(loadAsset("button3.jpg"))));
	button4.setImage(gl::Texture(loadImage(loadAsset("button4.jpg"))));
	//button1.setFunction(lookAtMap);
	//button1.setCommandString("Looking at map...");
	//button2.setCommandString("button2 clicked");
	//button3.setCommandString("button3 clicked");
	//button4.setCommandString("button4 clicked");
	button1.setAssociatedCommand("map");
	button2.setAssociatedCommand("dummy2");
	button3.setAssociatedCommand("dummy3");
	button4.setAssociatedCommand("dummy4");
	menuButtons.push_back(button1);
	menuButtons.push_back(button2);
	menuButtons.push_back(button3);
	menuButtons.push_back(button4);

	gm.addCommand(Command(lookAtMap, "map"));
	gm.addCommand(Command(dummyCommand, "dummy2"));
	gm.addCommand(Command(dummyCommand, "dummy3"));
	gm.addCommand(Command(dummyCommand, "dummy4"));

	con.output("pgup / pgdn to scroll inventory.");
	con.output(" ");
	menuButtonClicked = -1;
	testItem.setId(1);
	testItem.setDescription("testitem desc");
	testItem.setName("test item");
	inv.setup();
	inv.addItem(testItem);
	inv.addItem(testItem);
	inv.addItem(testItem);
	for (int i = 5; i < 30; i++)
	{
		testItem.setId(i);
		for (int x = 0; x < i; x++)
			inv.addItem(testItem);
	}

	//vector<string> args;
	
	//Command com(&outputDebugInfo(&gm, args), "Enigma::debug");
	


}

void EnigmaApp::mouseDown( MouseEvent event )
{
	menuButtonClicked = -1;

	if (eventAreaClicked(event)) {
		if (mapActive)
		{
			int oldArea = worldmap.getCurrentAreaIndex();
			int newArea = worldmap.mapClicked(event.getX(), event.getY());
			if (newArea != -1)
			{
				if (newArea != oldArea)
				{
					worldmap.setCurrentArea(newArea);
					con.output("You have entered " + worldmap.getArea(newArea)->getName());
				}
				else
				{
					con.output("You are already in that area.");
				}
				worldmap.setCurrentArea(newArea);
				gm.lookAtArea();
			}
		}
	}
	else if (menuButtonAreaClicked(event))
	{
		int bufferSize = ((EVENT_WINDOW_HEIGHT - MENUBUTTONS_Y) - (MENUBUTTONS_HEIGHT * menuButtons.size())) / menuButtons.size(); 
		for (int index = 0; index < menuButtons.size(); index++)
		{
			if (event.getX() > MENUBUTTONS_X  && 
			event.getX() < MENUBUTTONS_X + MENUBUTTONS_WIDTH &&	
			event.getY() > MENUBUTTONS_Y + index * (MENUBUTTONS_HEIGHT+bufferSize) && 
			event.getY() < MENUBUTTONS_Y + index * (MENUBUTTONS_HEIGHT+bufferSize) + MENUBUTTONS_HEIGHT)
			{
				//menuButtons[index].getFunction();
				con.output(">" + menuButtons[index].getAssociatedCommand());
				menuButtonClicked = index;
				bool result = gm.parseAndExecuteCommand(menuButtons[index].getAssociatedCommand());
				break;
			}
		}
	}
}

bool EnigmaApp::eventAreaClicked(MouseEvent event)
{
	return 
		event.getX() > EVENT_WINDOW_X && 
		event.getX() < EVENT_WINDOW_X + EVENT_WINDOW_WIDTH &&	
		event.getY() > EVENT_WINDOW_Y && 
		event.getY() < EVENT_WINDOW_Y + EVENT_WINDOW_HEIGHT;
}

bool EnigmaApp::menuButtonAreaClicked(MouseEvent event)
{
	return 
		event.getX() > MENUBUTTONS_X && 
		event.getX() < MENUBUTTONS_X + MENUBUTTONS_WIDTH &&	
		event.getY() > MENUBUTTONS_Y && 
		event.getY() < MENUBUTTONS_Y + menuButtons.size() * MENUBUTTONS_HEIGHT;
}

void EnigmaApp::keyDown( KeyEvent event ) 
{
	if( event.getCode() == KeyEvent::KEY_RETURN )
	{
		string cmdString = con.sendLine();
		try {
			gm.parseAndExecuteCommand(cmdString); // currently not checking the return value from this - we should give some kind of feedback to the user "hey, there's another command still running!" if it returns false
												  // also, we are not catching the CommandNotFoundException if the command is invalid - this is very important!
		}
		catch (CommandNotFoundException) {
			con.output("Command not recognized.");
		
		}
	}
	else if (event.getCode() == KeyEvent::KEY_BACKSPACE)
		con.backspace();
	else if (event.getChar() >= ' ' && event.getChar() < '~')
		con.sendChar(event.getChar());
	else if (event.getCode() == KeyEvent::KEY_PAGEUP)
		inv.decrementScrollIndex();
	else if (event.getCode() == KeyEvent::KEY_PAGEDOWN)
		inv.incrementScrollIndex();
}

void EnigmaApp::update()
{
}

void EnigmaApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );  
	con.draw();
	if(gm.lookingAtMap)
		worldmap.draw();
	else
		worldmap.getCurrentArea()->drawBackgroundImage();
	gl::drawSolidRect(Rectf(windowNS::DIVIDER_X, windowNS::DIVIDER_Y, windowNS::DIVIDER_WIDTH + windowNS::DIVIDER_X, windowNS::DIVIDER_HEIGHT + windowNS::DIVIDER_Y));
	for (int i = 0; i < menuButtons.size(); i++)
		menuButtons[i].draw(i, menuButtons.size());
	inv.draw();
}

void EnigmaApp::outputDebugInfo(GameManager* gm, vector<string> args) {
	con.output("Debug info goes here.");
}

CINDER_APP_NATIVE( EnigmaApp, RendererGl )
