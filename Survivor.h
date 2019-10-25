#ifndef SURVIVOR_H
#define SURVIVOR_H

#include "MastermindBoard.h"

class Survivor :
	public MastermindBoard
{
public:
	// constructor
	Survivor();

	// mutator methods
	void resetBoard();
};

#endif // !SURVIVOR_H

