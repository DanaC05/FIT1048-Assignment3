/**************************************************
Project: Mastermind: The Last Of Us Edition
Assignment Num: 3
Author: Dana Casella
Purpose: MastermindBoard Class Header
**************************************************/
#ifndef MASTERMINDBOARD_H
#define MASTERMINDBOARD_H

#include <fstream>
#include <array>
#include "windows.h."
#include "Board.h"
class MastermindBoard :
	public Board
{
public:
	// destructor
    ~MastermindBoard();

	// accessor methods
	void displayBoard(bool codeEntered);
	void displayPlayerAttempts();
	void endAnimation(string item="");
	string validBoardCharacters();
	string validSymbolGroup();
	string lastHint();
	string lastGuess();
	string generateHintData();
	string generateAttemptData();
	virtual string wordLibraryName();
	virtual int wordLibrarySize();

	// mutator methods
	void addTurn(string guess, string hint);
	void loadGuesses(string guesses);
	void loadHints(string hints);

protected:
	// variables
	string* playerAttempts;
	string* playerHints;
	string* boardFileName;
	string* attemptsFileName;
	string* validSymbols;
	string* possibleCodeElements;
	string* lastHintGiven;
	string* lastGuessGiven;

	// mutator methods
	void boardSetup();
	void printEmptyBoard();
	void printBoardWithMoves(bool flash);
	string generateAttemptsString();
};

#endif // !MASTERMINDBOARD_H

