#ifndef ELLIE_H
#define ELLIE_H

#include <fstream>
#include <algorithm>
#include <vector>
#include <ctime>
#include "Player.h"

class Ellie :
	public Player
{
public:
	// constructors
	Ellie();
	~Ellie();

	// mutator methods
	void resetEllieValues();

	// accessor method
	string getDialogue(int phraseID, string insertInfo);

private:
	// variables
	bool* firstZero;
	string* zeroOptions;
	string* repeatOptions;
	const int* zeroSize = new int(7);
	const int* repeatSize = new int(3);

	// mutator methods
	void setEllieVariables();	
};

#endif // !ELLIE_H