/**************************************************
Project: Mastermind: The Last Of Us Edition
Assignment Num: 3
Author: Dana Casella
Purpose: CustomPlayer Class Header
**************************************************/
#ifndef CUSTOMPLAYER_H
#define CUSTOMPLAYER_H

#include "Player.h"
class CustomPlayer :
	public Player
{
public:
	// constructor
	CustomPlayer(string name);

	// accessor method
	string getDialogue(int phraseID, string insertInfo);

private:
	// variables
	bool* firstExplanationGiven;
};

#endif // !CUSTOMPLAYER_H

