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
//                               PUBLIC: MUTATOR METHODS
//=======================================================================================
void Board::setMaxAttempts(int gameSize) {
	maxAttempts = new int(gameSize);
}

void Board::addAttempt() {
	*numAttempts += 1;
}

