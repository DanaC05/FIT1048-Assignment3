#include "Hard.h"

//=======================================================================================
//                                 PUBLIC: CONSTRUCTOR
//=======================================================================================
Hard::Hard() {
	maxAttempts = new int(12);
	boardFileName = new string("gameBoards/hardBoard.txt");
	attemptsFileName = new string("previousAttempts/hardAttempts.txt");
	validSymbols = new string("!@#$%&*~?");
	symbolGroup = new string("symbol");
	boardSetup();
}
