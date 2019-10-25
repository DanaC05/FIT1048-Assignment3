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
	virtual void displayBoard() = 0;
	virtual void boardSetup() = 0;
	
	// accessor methods
	int getNumAttempts();
	int getMaxAttempts();
	bool maxAttemptsReached();

	// mutator methods
	void addAttempt();
	void setMaxAttempts(int gameSize);

protected:
	// variables
	int* numAttempts;
	int* maxAttempts;
};

#endif //!BOARD_H


