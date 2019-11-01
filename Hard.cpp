/**************************************************
Project: Mastermind: The Last Of Us Edition
Assignment Num: 3
Author: Dana Casella
Purpose: Hard Class File

This class inherits from the MastermindBoard class 
and sets the parameters for the game board when
playing the hard level.
**************************************************/
#include "Hard.h"

//=======================================================================================
//                                 PUBLIC: CONSTRUCTOR
//=======================================================================================
Hard::Hard() {
	maxAttempts = new int(12);
	boardFileName = new string("gameBoards/hardBoard.txt");
	attemptsFileName = new string("previousAttempts/hardAttempts.txt");
	validSymbols = new string("! @ # $ % & * ~ ?");
	possibleCodeElements = new string("!@#$%&*~?");
	boardSetup();
}
