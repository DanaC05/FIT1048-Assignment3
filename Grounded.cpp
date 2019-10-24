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