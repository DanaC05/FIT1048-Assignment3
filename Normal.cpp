#include "Normal.h"

//=======================================================================================
//                                 PUBLIC: CONSTRUCTOR
//=======================================================================================
Normal::Normal() {
	maxAttempts = new int(10);
	boardFileName = new string("gameBoards/normalBoard.txt");
	attemptsFileName = new string("previousAttempts/normalAttempts.txt");
	validSymbols = new string("numbers 0-5");
	symbolGroup = new string("number");
	boardSetup();
}

//=======================================================================================
//                                 PUBLIC: MUTATOR METHOD
//=======================================================================================
void Normal::resetBoard() {
	numAttempts = 0;
	fill_n(playerAttempts, *maxAttempts, "");
	fill_n(playerHints, *maxAttempts, "");
}


