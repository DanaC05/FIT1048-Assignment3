/**************************************************
Project: Mastermind: The Last Of Us Edition
Assignment Num: 3
Author: Dana Casella
Purpose: Survivor Class File

This class inherits from the MastermindBoard class
and sets the parameters for the game board when
playing the survivor level.
**************************************************/
#include "Survivor.h"

//=======================================================================================
//                                 PUBLIC: CONSTRUCTORS
//=======================================================================================
Survivor::Survivor() {
	maxAttempts = new int(14);
	boardFileName = new string("gameBoards/survivorAndGroundedBoard.txt");
	attemptsFileName = new string("previousAttempts/survivorAttempts.txt");
	validSymbols = new string("letters a-z");
	possibleCodeElements = new string("abcdefghijklmnopqrstuvwxyz");
	boardSetup();
}

Survivor::~Survivor() {
	delete libraryFileName;
	delete librarySize;
}

//=======================================================================================
//                                 PUBLIC: ACCESS METHODS
//=======================================================================================
string Survivor::wordLibraryName() {
	return *libraryFileName;
}

int Survivor::wordLibrarySize() {
	return *librarySize;
}