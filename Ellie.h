/**************************************************
Project: Mastermind: The Last Of Us Edition
Assignment Num: 3
Author: Dana Casella
Purpose: Ellie Class Header
**************************************************/
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

	// accessor method
	string getDialogue(int phraseID, string insertInfo);

private:
	// variables
	bool* firstZero;
	bool* firstExplanationGiven;
	const string zeroPhrases[7] = { "\t\t\t\t\t\t\t\t\t\t     Ugh, not even close.",
								    "\t\t\t\t\t\t\t\t\t\tNope, that's for sure not it.",
									"\t\t\t\t\t\t\t\t\t\tAnnnnnd.... A whole lot of nada.",
									"\t\t\t\t\t\t\t\t\t\t  Yep... still a big fat zero.",
									"\t\t\t\t\t\t\t\tAt this rate, I'm going to need a flame thrower to get in here.",
									"\t\t\t\t\t\t\t\t\t\t\tUGH, c'mon, Ellie! \n\t\t\t\t\t\t\t\t\t\tI got this. Endure and Survive.",
									"\t\t\t\t\t\t\tWhy don't people write keycodes on paper and leave them lying around anymore." };

	const string repeatPhrases[3] = { "\t\t\t\t\t\t\tDammit, I've already tried that one. I need to think about this more carefully.",
									  "\t\t\t\t\t\t\t\t\t\t     I think I already...\n\t\t\t\t\t\t\t\t\t  Yep, already tried it. C'mon Ellie, think!",
									  "\t\t\t\t\t\t\t      Well if it didn't work the last time I don't know why it would now..." };
};

#endif // !ELLIE_H