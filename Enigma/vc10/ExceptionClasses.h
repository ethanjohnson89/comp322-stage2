#ifdef __EXCEPTIONCLASSES_H
#define __EXCEPTIONCLASSES_H

#include <exception>
using std::exception;

/************  Exception Classes  **************/

class EnigmaException : public std::exception { };
class GameManagerException : public EnigmaException { };
class InvalidIndexException : public EnigmaException { };
class CommandNotFoundException : public GameManagerException { };

/*****************************************/

#endif