#include "console.h";


Console::Console()
{
	width = 600;
	height = 500;
	inputLinePrefix = ">";
	inputLine = inputLinePrefix;
	lines.push_back(" ");
	maxLines = 10;
	font = "Consolas";
	fontSize = 28;
	textColor = Color(0.7f, 1.0f, 0.7f);
	backColor = ColorA(0.15, 0.15, 0.15, 1);
}

void Console::setup()
{
	mFont = Font( font, fontSize );
	mSize = Vec2f( width, height );

	for (int i = 0; i < maxLines; i++)
		lines.push_back(" ");

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

	TextBox tbox = TextBox().alignment( TextBox::LEFT ).font( mFont ).size( Vec2i( mSize.x, TextBox::GROW ) ).text( txt );
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
	
	if( mTextTexture )
		gl::draw( mTextTexture );
}

void Console::sendChar(char a)
{
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
	if (lines.size() > maxLines)
		lines.erase(lines.begin());
	lines.push_back(s);
	render();
}

void Console::backspace()
{
	if (inputLine.size() > inputLinePrefix.size())
		inputLine.erase(inputLine.size() - 1);
	render();
}