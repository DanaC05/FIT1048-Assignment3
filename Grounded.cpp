#include "Grounded.h"

//=======================================================================================
//                                 PUBLIC: CONSTRUCTORS
//=======================================================================================
Grounded::Grounded() {
	maxAttempts = new int(16);
	boardFileName = new string("gameBoards/survivorAndGroundedBoard.txt");
	attemptsFileName = new string("previousAttempts/groundedAttempts.txt");
	validSymbols = new string("letters a-z");
	symbolGroup = new string("letter");
	boardSetup();
}

Grounded::~Grounded() {
	delete libraryFileName;
	delete librarySize;
}

//=======================================================================================
//                                 PUBLIC: MUTATOR METHOD
//=======================================================================================
string Grounded::wordLibraryName() {
	return *libraryFileName;
}

int Grounded::wordLibrarySize() {
	return *librarySize;
}

//=======================================================================================
//                                 PUBLIC: MUTATOR METHOD
//=======================================================================================
void Grounded::resetBoard() {
	numAttempts = 0;
	fill_n(playerAttempts, *maxAttempts, "");
	fill_n(playerHints, *maxAttempts, "");
}