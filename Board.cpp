/**************************************************
Project: Mastermind: The Last Of Us Edition
Assignment Num: 3
Author: Dana Casella
Purpose: Board Class File

This is an abstract class that acts as a generic 
template for it's subclasses (game boards).
**************************************************/
#include "Board.h"

//=======================================================================================
//                                 PUBLIC: DESTRUCTOR
//=======================================================================================
Board::~Board() {
	delete numAttempts;
	delete maxAttempts;
}

//=======================================================================================
//                               PUBLIC: ACCESSOR METHODS
//=======================================================================================
int Board::getMaxAttempts() {
	return *maxAttempts;
}

int Board::getNumAttempts() {
	return *numAttempts;
}

bool Board::maxAttemptsReached() {
	return *numAttempts >= *maxAttempts;
}

//=======================================================================================
//                               PUBLIC: MUTATOR METHOD
//=======================================================================================
void Board::addAttempt() {
	*numAttempts += 1;
}

