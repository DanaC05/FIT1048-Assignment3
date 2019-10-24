#ifndef MASTERMINDBOARD_H
#define MASTERMINDBOARD_H

#include <fstream>
#include <array>
#include "Board.h"
class MastermindBoard :
	public Board
{
public:
	// destructor
    ~MastermindBoard();

	// abstract methods 
	//virtual void resetBoard() = 0;

	// accessor methods
	void displayPlayerAttempts();
	string generateBoardString();
	string generateAttemptsString();

	// mutator methods
	void addTurn(string guess, string hint);
	void mastermindSetup();

protected:
	// variables
	string* playerAttempts;
	string* playerHints;
	string* boardFileName;
	string* attemptsFileName;
	string* validSymbols;
	string* symbolGroup;
};

#endif // !MASTERMINDBOARD_H

