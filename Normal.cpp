/**************************************************
Project: Mastermind: The Last Of Us Edition
Assignment Num: 3
Author: Dana Casella
Purpose: Normal Class File

This class inherits from the MastermindBoard class
and sets the parameters for the game board when
playing the normal level.
**************************************************/
#include "Normal.h"

//=======================================================================================
//                                 PUBLIC: CONSTRUCTOR
//=======================================================================================
Normal::Normal() {
	maxAttempts = new int(10);
	boardFileName = new string("gameBoards/normalBoard.txt");
	attemptsFileName = new string("previousAttempts/normalAttempts.txt");
	validSymbols = new string("numbers 0-5");
	possibleCodeElements = new string("012345");
	boardSetup();
}


