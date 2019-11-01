/**************************************************
Project: Mastermind: The Last Of Us Edition
Assignment Num: 3
Author: Dana Casella
Purpose: Grounded Class File

This class inherits from the MastermindBoard class 
and sets the parameters for the game board when
playing on level grounded.
**************************************************/
#include "Grounded.h"

//=======================================================================================
//                                 PUBLIC: CONSTRUCTORS
//=======================================================================================
Grounded::Grounded() {
	maxAttempts = new int(16);
	boardFileName = new string("gameBoards/survivorAndGroundedBoard.txt");
	attemptsFileName = new string("previousAttempts/groundedAttempts.txt");
	validSymbols = new string("letters a-z");
	possibleCodeElements = new string("abcdefghijklmnopqrstuvwxyz");
	boardSetup();
}