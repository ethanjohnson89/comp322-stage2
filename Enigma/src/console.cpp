/****************************************
Group #: 2
Members: Steve Patterson, James Mart, Nick Halvorsen, Ethan Johnson
Course: Comp 322
Date: 12/4/13
****************************************/

#include "console.h"

Console::Console()
{
	width = CONSOLE_WIDTH;
	height = CONSOLE_HEIGHT;
	inputLinePrefix = "-> ";
	inputLine = inputLinePrefix;
	lines.push_back(" ");
	font = CONSOLE_FONT;
	fontSize = CONSOLE_FONT_SIZE;
	textColor = CONSOLE_TEXT_COLOR;
	backColor = CONSOLE_BACK_COLOR;
	maxLines = 0;
}

//___________________________________________________________________________________
//---------------------------------------------------------------------------------
//		standard functions: setup(), render(), draw(), update()
//===============================================================================

void Console::setup()
{
	mFont = Font( CONSOLE_FONT, static_cast<float>(CONSOLE_FONT_SIZE) );
	width = CONSOLE_WIDTH;
	height = CONSOLE_HEIGHT;
	x = CONSOLE_X;
	y = CONSOLE_Y;
	adjustMaxLines();

	render();
}


void Console::render()
{
	string txt = "";
	
	// Get mutex lock on lines while we're reading from it
	{ // the braces are so that the lock is released as soon as the for-loop is over - we don't need to keep it throughout the whole rendering process (which could be relatively lengthy)
		boost::lock_guard<boost::mutex> render_mutexLock(lineBufferMutex);

		for (unsigned int i = 0; i < lines.size(); i++)
		{
			txt += lines[i];
			txt += "\n";
		}
		txt += inputLine;
	}

	TextBox tbox = TextBox().alignment( TextBox::LEFT ).font( mFont ).size( Vec2i( width, height ) ).text( txt );
	tbox.setColor(textColor);
	tbox.setBackgroundColor(backColor);
	Vec2i sz = tbox.measure();
	mTextTexture = gl::Texture( tbox.render() );
}

void Console::update()
{
}

void Console::draw()
{
	gl::setMatricesWindow( getWindowSize() );
	gl::enableAlphaBlending();
	Vec2f pos(static_cast<float>(x), static_cast<float>(y));

	if( mTextTexture )
		gl::draw( mTextTexture, pos );
}


//___________________________________________________________________________________
//---------------------------------------------------------------------------------
//		Member functions
//===============================================================================

//___________________________________________________________________________________
//-----------------------------------------------------------------------------
//		sendChar

void Console::sendChar(char a)
{
	if (inputLine.size() < (unsigned)getLineCharsLimit()) 
		inputLine += a;
	render();
}

//___________________________________________________________________________________
//---------------------------------------------------------------------------------
//		sendLine

string Console::sendLine()
{
	string sentLine;

	// Get mutex lock on lines while we're reading/writing it
	{ // lock needs to be released before the call to render(), which needs to grab the lock itself
		boost::lock_guard<boost::mutex> sendLine_mutexLock(lineBufferMutex);

		if (inputLine.size() == inputLinePrefix.size()) // empty line
			return "";
		if (lines.size() > (unsigned)maxLines)
			lines.erase(lines.begin());

		auto it = inputLine.begin();
		for (unsigned int i = 0; i < inputLinePrefix.size(); i++)
			inputLine.erase(it);

		lines.push_back(inputLinePrefix + inputLine);
		sentLine = inputLine;
		inputLine = inputLinePrefix;
	}

	render();
	return sentLine;
}

//___________________________________________________________________________________
//-----------------------------------------------------------------------------
//		output

void Console::output(string s)
{
	// Get mutex lock on lines while we're writing to it
	{ // lock needs to be released before the call to render(), which needs to grab the lock itself
		boost::lock_guard<boost::mutex> output_mutexLock(lineBufferMutex);

		while (s.size() > (unsigned)getLineCharsLimit())
		{
			lines.push_back(s.substr(0, getLineCharsLimit()));
			s = s.substr(getLineCharsLimit(), s.size() - getLineCharsLimit());
		}

		lines.push_back(s);

		while (lines.size() > (unsigned)(maxLines + 1))
			lines.erase(lines.begin());
	}

	render();
}

//___________________________________________________________________________________
//-----------------------------------------------------------------------------
//		backspace

void Console::backspace()
{
	if (inputLine.size() > inputLinePrefix.size())
		inputLine.erase(inputLine.size() - 1);
	render();
}

//___________________________________________________________________________________
//-----------------------------------------------------------------------------
//		adjustMaxLines

void Console::adjustMaxLines()
{
	// Get mutex lock on lines while we're writing to it
	{ // lock needs to be released before the call to render(), which needs to grab the lock itself
		boost::lock_guard<boost::mutex> adjustMaxLinesmutexLock(lineBufferMutex);

		int oldMax = maxLines;
		maxLines = height / (fontSize - 3);
		maxLines--;
		maxLines--;

		lines.clear();
		for (int i = 0; i < maxLines + 1; i++)
			lines.push_back(" ");
	}

	render();
}

//___________________________________________________________________________________
//-----------------------------------------------------------------------------
//		setFontSize

void Console::setFontSize(int a)
{
	fontSize = a; // WAHOO!! YEAH!!! CHANGE THE FONT SIZE!!! WOOOOOOOOOOOO!!!!!!! ALRIGHT!!! 3 CHEERS FOR FONT SIZE! HIP HIP HOORAY!! HIP HIP HOORAY!! HIP HIP HOORAY!! GO TEAM GO! SCORE THE GOAL WITH THE BALL AND GET POINTS FOR YOUR TEAM
	mFont = Font( font, static_cast<float>(fontSize)); 
	inputLine = inputLinePrefix; 
	adjustMaxLines();
}

//___________________________________________________________________________________
//-----------------------------------------------------------------------------
//		getLineCharsLimit

int Console::getLineCharsLimit() // returns max number of characters that can fit on a line 
{
	return static_cast<int>((width / (fontSize / 2.3)) + 1.0); 
}