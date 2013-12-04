#include "console.h";


Console::Console()
{
	width = CONSOLE_WIDTH;
	height = CONSOLE_HEIGHT;
	inputLinePrefix = ">";
	inputLine = inputLinePrefix;
	lines.push_back(" ");
	font = "Consolas";
	fontSize = 24;
	textColor = ColorA(0.6f, 1.0f, 0.6f, 1);
	backColor = ColorA(0.35, 0.35, 0.35, 1);
	maxLines = 0;
}

void Console::setup()
{
	mFont = Font( font, fontSize );
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

	for (int i = 0; i < lines.size(); i++)
	{
		txt += lines[i];
		txt += "\n";
	}
	txt += inputLine;

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
	gl::clear( Color( 0, 0, 0 ) );
	Vec2f pos(x, y);

	if( mTextTexture )
		gl::draw( mTextTexture, pos );
}

void Console::sendChar(char a)
{
	if (inputLine.size() < getLineCharsLimit()) 
		inputLine += a;
	render();
}

string Console::sendLine()
{
	if (inputLine.size() == inputLinePrefix.size()) // empty line
		return "";
	if (lines.size() > maxLines)
		lines.erase(lines.begin());

	auto it = inputLine.begin();
	for (int i = 0; i < inputLinePrefix.size(); i++)
		inputLine.erase(it);

	lines.push_back(inputLine);
	string sentLine = inputLine;
	inputLine = inputLinePrefix;

	render();
	return sentLine;
}

void Console::output(string s)
{
	while (s.size() > getLineCharsLimit())
	{
		lines.push_back(s.substr(0, getLineCharsLimit()));
		s = s.substr(getLineCharsLimit(), s.size() - getLineCharsLimit());
	}

	lines.push_back(s);

	while (lines.size() > maxLines + 1)
		lines.erase(lines.begin());

	render();
}

void Console::backspace()
{
	if (inputLine.size() > inputLinePrefix.size())
		inputLine.erase(inputLine.size() - 1);
	render();
}

void Console::adjustMaxLines()
{
	int oldMax = maxLines;
	maxLines = height / (fontSize - 3);
	maxLines--;
	maxLines--;

	lines.clear();
	for (int i = 0; i < maxLines + 1; i++)
		lines.push_back(" ");

	render();
}

void Console::setFontSize(int a)
{
	fontSize = a;
	mFont = Font( font, fontSize ); 
	inputLine = inputLinePrefix; 
	adjustMaxLines();
}

int Console::getLineCharsLimit() // returns max number of characters that can fit on a line 
{
	return (width / (fontSize / 2.3)) + 1; 
}