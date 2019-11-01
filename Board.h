/**************************************************
Project: Mastermind: The Last Of Us Edition
Assignment Num: 3
Author: Dana Casella
Purpose: Board Class Header
**************************************************/
#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
using namespace std;

class Board
{
public:
	// destructor
	~Board();

	// abstract methods
	virtual void displayBoard(bool displayDesiredElements) = 0;
	virtual void boardSetup() = 0;
	
	// accessor methods
	int getNumAttempts();
	int getMaxAttempts();
	bool maxAttemptsReached();

	// mutator method
	void addAttempt();

protected:
	// variables
	int* numAttempts;
	int* maxAttempts;
};

#endif //!BOARD_H


