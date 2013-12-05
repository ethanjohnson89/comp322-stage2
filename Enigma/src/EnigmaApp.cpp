#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "GameManager.h"
#include "CommandFunctions.h"
#include "globals.h"
#include "EnigmaArea.h"
#include "MenuButton.h"
#include <cstdlib>
#include <string> // for using getline() on a stringstream

using namespace ci;
using namespace ci::app;
using namespace std;

class EnigmaApp : public AppNative {
private:
	GameManager gm;
	Console con;
	Worldmap worldmap;
	bool eventAreaClicked(MouseEvent event);
	bool menuButtonAreaClicked(MouseEvent event);
	EnigmaArea testArea, testArea2;
	vector<MenuButton> menuButtons;
	MenuButton button1, button2, button3, button4;
	Item testItem;
	Inventory inv;
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

	gm.con.setup();
	testArea.initialize("Forest", "hello friend this is the forest", 80.0f, 100.0f, gl::Texture(loadImage(loadAsset("forest.jpg"))), gl::Texture(loadImage(loadAsset("forest.jpg"))));
	testArea2.initialize("Beach", "hey this is the beach", 200.0f, 100.0f, gl::Texture(loadImage(loadAsset("beach.jpg"))), gl::Texture(loadImage(loadAsset("beach.jpg"))));

	gm.setMap(&worldmap);
	worldmap.setBackgroundPicture(gl::Texture(loadImage(loadAsset("worldmap1.jpg"))));
	worldmap.addArea(&testArea);
	worldmap.addArea(&testArea2);

	button1.setImage(gl::Texture(loadImage(loadAsset("button1.jpg"))));
	button2.setImage(gl::Texture(loadImage(loadAsset("button2.jpg"))));
	button3.setImage(gl::Texture(loadImage(loadAsset("button3.jpg"))));
	button4.setImage(gl::Texture(loadImage(loadAsset("button4.jpg"))));
	
	button1.setAssociatedCommand("map");
	button2.setAssociatedCommand("help");
	button3.setAssociatedCommand("dummy3");
	button4.setAssociatedCommand("dummy4");
	menuButtons.push_back(button1);
	menuButtons.push_back(button2);
	menuButtons.push_back(button3);
	menuButtons.push_back(button4);

	gm.addCommand(Command(lookAtMap, "map"));
	gm.addCommand(Command(help, "help"));
	gm.addCommand(Command(dummyCommand, "dummy2"));
	gm.addCommand(Command(dummyCommand, "dummy3"));
	gm.addCommand(Command(dummyCommand, "dummy4"));
	gm.addCommand(Command(goToArea, "go"));
	gm.addCommand(Command(examineItem, "examine"));

	gm.con.output("  -- Welcome! Type \"Help\" for the help menu! --  ");
	gm.con.output(" ");

	gm.setInventory(&inv);
	inv.setup();
	testItem.setDescription("WOOOOOO THIS IS ITEM A YEAHHH!!!!!!!!");
	testItem.setName("itemA");
	inv.addItem(testItem);
	inv.addItem(testItem);
	inv.addItem(testItem);
	testItem.setName("Wooden Mallet");
	testItem.setDescription("This item is 123430932 coins. Smack 'em dead, Willis.");
	inv.addItem(testItem);
	for (int i = 5; i < 30; i++)
	{
		stringstream foo;
		foo << "item" << (char)(i + 0x41);
		testItem.setName(foo.str());
		testItem.setDescription("Hey this is item " + testItem.getName()); 
		for (int x = 0; x < rand() % 10; x++)
			inv.addItem(testItem);
	}
}

void EnigmaApp::mouseDown( MouseEvent event )
{
	if (eventAreaClicked(event)) {
		if (gm.lookingAtMap)
		{
			int oldArea = worldmap.getCurrentAreaIndex();
			int newArea = worldmap.mapClicked(event.getX(), event.getY());
			if (newArea != -1)
			{
				if (newArea != oldArea)
				{
					worldmap.setCurrentArea(newArea);
					gm.con.output("You have entered " + worldmap.getArea(newArea)->getName());
				}
				else					
					gm.con.output("You are already in that area.");
				
				worldmap.setCurrentArea(newArea);
				gm.lookAtArea();
			}
		}
	}
	else if (menuButtonAreaClicked(event))
	{
		int bufferSize = ((EVENT_WINDOW_HEIGHT - MENUBUTTONS_Y) - (MENUBUTTONS_HEIGHT * menuButtons.size())) / (menuButtons.size() - 1); 
		for (unsigned int index = 0; index < menuButtons.size(); index++)
		{
			if (event.getX() > MENUBUTTONS_X  && 
				event.getX() < MENUBUTTONS_X + MENUBUTTONS_WIDTH &&	
				event.getY() > MENUBUTTONS_Y + index * (MENUBUTTONS_HEIGHT+bufferSize) && 
				event.getY() < MENUBUTTONS_Y + index * (MENUBUTTONS_HEIGHT+bufferSize) + MENUBUTTONS_HEIGHT)
			{
				gm.buttonClicked = index;
				gm.con.output(gm.con.getInputLinePrefix() + menuButtons[index].getAssociatedCommand());
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
		event.getY() < CONSOLE_Y;
}

void EnigmaApp::keyDown( KeyEvent event ) 
{
	if( event.getCode() == KeyEvent::KEY_RETURN )
	{
		string cmdString = gm.con.sendLine();
		try {
			gm.parseAndExecuteCommand(cmdString); // currently not checking the return value from this - we should give some kind of feedback to the user "hey, there's another command still running!" if it returns false
												  // also, we are not catching the CommandNotFoundException if the command is invalid - this is very important!
		}
		catch (CommandNotFoundException) {
			gm.con.output("Command not recognized.");
		
		}
	}
	else if (event.getCode() == KeyEvent::KEY_BACKSPACE)
		gm.con.backspace();
	else if (event.getChar() >= ' ' && event.getChar() < '~')
		gm.con.sendChar(event.getChar());
	else if (event.getCode() == KeyEvent::KEY_UP)
		inv.decrementScrollIndex();
	else if (event.getCode() == KeyEvent::KEY_DOWN)
		inv.incrementScrollIndex();
}

void EnigmaApp::update()
{
	string line;
	while(std::getline(gm.textToPrint, line))
		gm.con.output(line);
	gm.textToPrint.clear();
}

void EnigmaApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );  
	gm.con.draw();
	if(gm.lookingAtMap)
		worldmap.draw();
	else
		worldmap.getCurrentArea()->drawBackgroundImage();
	gl::drawSolidRect(Rectf(windowNS::DIVIDER_X, windowNS::DIVIDER_Y, windowNS::DIVIDER_WIDTH + windowNS::DIVIDER_X, windowNS::DIVIDER_HEIGHT + windowNS::DIVIDER_Y));
	for (unsigned int i = 0; i < menuButtons.size(); i++) {
		if (gm.buttonClicked == i) {
			menuButtons[i].draw(i, menuButtons.size(), gm.buttonClicked);
			if (gm.buttonFrames == 2) {gm.buttonClicked = -1; gm.buttonFrames = 0;}
			else gm.buttonFrames++;

			
		}
		else menuButtons[i].draw(i, menuButtons.size());
	}
	inv.draw();
}

void EnigmaApp::outputDebugInfo(GameManager* gm, vector<string> args) {
	gm->con.output("Debug info goes here.");
}

CINDER_APP_NATIVE( EnigmaApp, RendererGl )
