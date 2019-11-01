/**************************************************
Project: Mastermind: The Last Of Us Edition
Assignment Num: 3
Author: Dana Casella
Purpose: Survivor Class Header
**************************************************/
#ifndef SURVIVOR_H
#define SURVIVOR_H

#include "MastermindBoard.h"

class Survivor :
	public MastermindBoard
{
public:
	// constructor
	Survivor();
	~Survivor();

	// accessor methods
	string wordLibraryName();
	int wordLibrarySize();

private:
	// variables
	const string* libraryFileName = new string("wordLibraries/secretCodeLibrary.txt");
	const int* librarySize = new int(167);
};

#endif // !SURVIVOR_H

