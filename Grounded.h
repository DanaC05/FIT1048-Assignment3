#ifndef GROUNDED_H
#define GROUNDED_H

#include "MastermindBoard.h"

class Grounded :
	public MastermindBoard
{
public:
	// constructors
	Grounded();
	~Grounded();

	// accessor methods
	string wordLibraryName();
	int wordLibrarySize();

private:
	// variables
	const string* libraryFileName = new string("wordLibraries/secretCodeLibrary.txt");
	const int* librarySize = new int(167);
};

#endif // !GROUNDED_H
