/**************************************************
Project: Mastermind: The Last Of Us Edition
Assignment Num: 3
Author: Dana Casella
Purpose: Ellie Class File

This class inherits from the Player class and
allows the user to play as the character Ellie.
It has all the basic functionallities of Player but
also allows for the output of dialogue. This 
dialogue is a lot more varied than that of 
CustomPlayer.
**************************************************/
#include "Ellie.h"

//=======================================================================================
//                                 PUBLIC: CONSTRUCTORS
//=======================================================================================
Ellie::Ellie() {
	// set name (name is always 'Ellie')
	playerName = new string("Ellie");

	// seed randoms
	srand(unsigned(time(NULL)));

	// initialise variables
	firstZero = new bool(true);
	firstExplanationGiven = new bool(false);
}

Ellie::~Ellie() {
	delete firstZero;
	delete firstExplanationGiven;
}

//=======================================================================================
//                               PUBLIC: ACCESSOR METHOD
//=======================================================================================
string Ellie::getDialogue(int phraseID, string insertInfo = "") {
	// outputs dialogue depending on phraseID
	string dialogueOutput = "";
	switch (phraseID) {
	// first phrase (to be displayed at the start of each game)
	case 1:
		dialogueOutput = "Okay, they're gone. I think I've got about " + insertInfo + " tries at this until one of them comes back.\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\tLet's do this.";
		break;
	// to be displayed when player selects 'show attempts' an no attempts have been made
	case 2:
		dialogueOutput = "I should really start working on this " + insertInfo + "...";
		break;
	// to be displayed when player gets 0 characters right
	case 3:
		int zeroIndex;

		// to ensure only one of three phrases is used first (so it makes sense)
		if (*firstZero) {
			zeroIndex = rand() % 3;
			*firstZero = false;
		}
		// selects a random phrase from zeroPhrases
		else {
			zeroIndex = rand() % 7;
			
		}
		dialogueOutput = zeroPhrases[zeroIndex];
		break;
	// to be displayed when the first hint of the game is given
	case 4:
		// ensures this phrase is only used once
		if (!*firstExplanationGiven) {
			dialogueOutput = "\t\t\t\t\t\t   Hmm, it looks like the question marks mean I've got something right but in the wrong place... \n\t\t\t\t\t\tand the circles mean I've got it in the right place! This should make things easier... slightly.\n\t\t\t\t\t\t\t\t\t\t    I better write this down.";

			*firstExplanationGiven = true;
		}
		break;
	// to be displayed if the player enters a combination they've already tried before
	case 5:
		int repeatIndex;

		// selects a random phrase from repeatPhrases
		repeatIndex = rand() % 3;
		dialogueOutput = repeatPhrases[repeatIndex];
		break;
	// to be displayed in the event of an invalid entry
	case 6:
		dialogueOutput = "\t\t\t\t\t\t\t      The code definitely doesn't have those, pretty sure I can only use " + insertInfo + ".";
		break;
	// to be displayed when player has three characters correct and in the right position
	case 7:
		dialogueOutput = "\t\t\t\t\t\t\t\t\tAlright! Just one more to go. I can do this.";
		break;
	// to be displayed when player has two attempts left
	case 8:
		dialogueOutput = "\n\n\n\t\t\t\t\t\t\tCrap! I can hear " + insertInfo + ". I better hurry but I think I can try two more times.";
		break;
	// final phrase (to be displayed when the player looses the game)
	case 9:
		dialogueOutput = "\t\t\t\t\t\t\t\t\t\tWhat the-? Get the hell off me!\n\n\n";
		break;
	// final phrase (to be displayed if player guesses the code on their last attempt)
	case 10:
		dialogueOutput = "\t\t\t\t\t\tYES! Hell yeah! I did it! I actually did it! I better " + insertInfo;
		break;
	// final phrase (to be displayed if player guesses the code on their second last attempt)
	case 11:
		dialogueOutput = "\t\t\t\t\t\tYES! Hell yeah access granted! There's even weapons in here!";
		break;
	// final phrase (to be displayed if the player guesses the code with more than two attempts left)
	case 12:
		dialogueOutput = "\t\t\t\t\t\t\t   ACCESS GRANTED! Hell YES! Jackpot!! We're going to be set for weeks!";
		break;
	// to be displayed if player enters less than 4 characters
	case 13:
		dialogueOutput = "\t\t\t\t\t\t\tWell this isn't going to get me anywhere if I don't enter exactly 4 keys...";
		break;
	// to be displayed when player selects 'help'
	case 14:
		dialogueOutput = "\t\t\t\t\t\tI'm not getting anywhere on my own. I think I still have the manual Joel gave me... Here it is!";
		break;
	}
	
	return dialogueOutput;
}
	
		
	

	
	
	
	

	

	