/**************************************************
Project: Mastermind: The Last Of Us Edition
Assignment Num: 3
Author: Dana Casella
Purpose: CustomPlayer Class File

This class inherits from the Player class and 
allows the user to play as themselves. CustomPlayer
has all the basic functionallities of Player but
also allows for the output of dialogue.
**************************************************/
#include "CustomPlayer.h"

//=======================================================================================
//                                 PUBLIC: CONSTRUCTORS
//=======================================================================================
CustomPlayer::CustomPlayer(string name) {
	playerName = new string(name);
	firstExplanationGiven = new bool(false);
}



string CustomPlayer::getDialogue(int phraseID, string insertInfo = "") {
	string dialogueOutput = "";

	// set output dialogue depending on phraseID
	switch (phraseID) {
	// first phrase (to be displayed at the start of each game)
	case 1:
		dialogueOutput = "\t\tThey're gone. I'll have " + insertInfo + " attempts until they come back.\n\n\n\n\n\n\n\n\n";
		break;
	// to be displayed when player selects 'show attempts' an no attempts have been made
	case 2:
		dialogueOutput = "\tI haven't made any attempts yet...";
		break;
	// to be displayed when the first hint of the game is given
	case 4:
		// ensures this phrase is only used once
		if (!*firstExplanationGiven) {
			dialogueOutput = "\t\t\t\tI think the question marks mean a character is correct but in the wrong place and the circles indicate it's in the right place.";
			*firstExplanationGiven = true;
		}
		break;
	// to be displayed if the player enters a combination they've already tried before
	case 5:
		dialogueOutput = "\t\t\t\t\t\t\t\t\t    Whoops, I've already tried that one.";
		break;
	// to be displayed in the event of an invalid entry
	case 6:
		dialogueOutput = "\t\t\t\t\t\t\t\t   Uh oh, the code won't have those, I can only use " + insertInfo + ".";
		break;
	// to be displayed when player has two attempts left
	case 8:
		dialogueOutput = "\n\n\n\t\t\t\t\t\t\t  I can hear " + insertInfo + ". I better hurry, I might be able to try two more times.";
		break;
	// final phrase (to be displayed when the player looses the game)
	case 9:
		dialogueOutput = "\t\t\t\t\t\t\t\t\t\tWait! Please let me go!\n\n\n";
		break;
	// final phrase (to be displayed if player guesses the code on their last attempt)
	case 10:
		dialogueOutput = "\t\t\t\t\t\t\t\t\t\tYES! I did it! I better " + insertInfo;
		break;
	// final phrase (to be displayed if player guesses the code on their second last attempt)
	case 11:
		dialogueOutput = "\t\t\t\t\t\t\tYES! I did it! And with time to spare. I can grab a few other things whilst I'm here.";
		break;
	// final phrase (to be displayed if the player guesses the code with more than two attempts left)
	case 12:
		dialogueOutput = "\t\t\t\t\t\t\t     YES! I got it! They've got so much stuff in here! We'll be set for ages!";
		break;
	// to be displayed if player enters less than 4 characters
	case 13:
		dialogueOutput = "\t\t\t\t\t\t\t\t\t\tI need to enter exactly 4 keys...";
		break;
	// to be displayed when player selects 'help'
	case 14:
		dialogueOutput = "\t\t\t\t\t\t\t\tI think I still have the code breakers manual... Here it is!";
		break;
	}

	return dialogueOutput;
}
