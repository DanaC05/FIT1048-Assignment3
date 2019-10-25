#include "Survivor.h"

//=======================================================================================
//                                 PUBLIC: CONSTRUCTOR
//=======================================================================================
Survivor::Survivor() {
	maxAttempts = new int(14);
	boardFileName = new string("gameBoards/survivorAndGroundedBoard.txt");
	attemptsFileName = new string("previousAttempts/survivorAttempts.txt");
	validSymbols = new string("letters a-z");
	symbolGroup = new string("letter");
	boardSetup();
}

//=======================================================================================
//                                 PUBLIC: MUTATOR METHOD
//=======================================================================================
void Survivor::resetBoard() {
	numAttempts = 0;
	fill_n(playerAttempts, *maxAttempts, "");
	fill_n(playerHints, *maxAttempts, "");
}