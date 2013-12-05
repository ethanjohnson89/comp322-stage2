/****************************************
Group #: 2
Members: Steve Patterson, James Mart, Nick Halvorsen, Ethan Johnson
Course: Comp 322
Date: 12/4/13
****************************************/

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