/****************************************
Group #: 2
Members: Steve Patterson, James Mart, Nick Halvorsen, Ethan Johnson
Course: Comp 322
Date: 12/4/13
****************************************/

#include "GameManager.h"

Command GameManager::getCommand(string cmdName) {
	if(commands.find(cmdName) != commands.end())
		return commands[cmdName];
	throw CommandNotFoundException();
}

bool GameManager::parseAndExecuteCommand(string commandLine)
{
	string cmdName;
	vector<string> args;

	boost::char_separator<char> sep(" ", "", boost::drop_empty_tokens);
	boost::tokenizer<boost::char_separator<char> > tok(commandLine, sep);
	auto token_iter = tok.begin();
	if(token_iter == tok.end()) // trivial case - empty line or line containing only spaces
		return true; // we'll consider this a successful execution since there's nothing to do
	cmdName = *token_iter;
	for(token_iter++; token_iter != tok.end(); token_iter++)
		args.push_back(*token_iter);
	std::transform(cmdName.begin(), cmdName.end(), cmdName.begin(), ::tolower);
	Command cmd = getCommand(cmdName);

	// This function "shouldn't" be called when another function is already being executed (since the UI is designed to not let the user
	// type another command until the last one's finished executing). If somehow this does happen, we can't proceed.
	if(processingCommand)
		return false;

	processingCommand = true;
	activeCommandThread = boost::thread(threadLauncher, *cmd.getAssociatedFunction(), this, args);

	return true;
}

void threadLauncher(CommandFunction function, GameManager *gm, vector<string> args)
{
	function(gm, args);
	gm->processingCommand = false;
}