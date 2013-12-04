#ifndef __EXCEPTIONCLASSES_H
#define __EXCEPTIONCLASSES_H

#include <exception>
using std::exception;

/************  Exception Classes  **************/

class EnigmaException : public std::exception { };
class InvalidIndexException : public EnigmaException { };
class CommandNotFoundException : public EnigmaException { };
class AreaNotFoundException : public EnigmaException { };

/*****************************************/

#endif