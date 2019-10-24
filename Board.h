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
	virtual void displayBoard(string boardString = "");
	virtual void boardSetup();
	
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


