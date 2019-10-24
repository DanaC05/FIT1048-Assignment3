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
	MastermindBoard::mastermindSetup();
}
