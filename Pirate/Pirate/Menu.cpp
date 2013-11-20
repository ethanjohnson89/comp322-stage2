#include "Menu.h"

int menu(string prompt,vector<string>& items)
{
	int numOfItems = items.size()+1;
	wout << prompt << endl;
	
	for (unsigned int i = 0; i < items.size(); i++)
	{
		wout << "["; 

		if (i < 9)
			wout << i+1;
		else
			wout << static_cast<char>(i + 88);
		
		wout << "] " << items[i] << endl;
		
	}

	char c = ' ';

	while (c < 49 || (c > 57 && c < 97) ||
		  (numOfItems < 10 && (c-48) > numOfItems-1) || 
		  (numOfItems >= 10 && (c-87) > numOfItems-1))
		c = getch();

	if (c >= 97)
		c -= 87;
	else
		c -= 48;

	if (c < 10) // they chose 1-9
		wout << static_cast<char>(c + 48) << endl;
	else // they chose a letter
		wout << static_cast<char>(c + 87) << endl;

	return c;
}

int menu(string prompt,int numOfChoices,...)
{
	va_list args;
	va_start(args,prompt);

	wout << prompt << endl;
	char* s;
	for (int i = 0; i < numOfChoices; i++)
	{
		s = va_arg(args,char*);
		cout << "[" << i+1 << "] " << s << endl;
	}
	va_end(args);

	char c = ' ';
	while ((c-48) < 1 || (c-48) > (numOfChoices))
	{
		c = getch();
	}
	wout << c-48 << endl;
	return c-48;
}