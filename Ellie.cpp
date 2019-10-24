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
	setPlayerVariables();
	setEllieVariables();
}

Ellie::~Ellie() {
	delete firstZero;
	delete zeroOptions;
	delete repeatOptions;
	delete zeroSize;
	delete repeatSize;
}

//=======================================================================================
//                               PUBLIC: ACCESSOR METHODS
//=======================================================================================
string Ellie::getDialogue(int phraseID, string insertInfo = "") {
	string dialogueOutput = "";
	switch (phraseID) {
	case 1:
		dialogueOutput = "Okay, they're gone. I think I've got about " + insertInfo + " tries at this door until one of them comes back.\nLet's do this";
		break;
	case 2:
		dialogueOutput = "I should really start working on this door...";
		break;
	case 3:
		int zeroIndex;
		if (*firstZero) {
			zeroIndex = rand() % 3;
		}
		else {
			zeroIndex = rand() % 7;
			*firstZero = false;
		}
		dialogueOutput = zeroOptions[zeroIndex];
		break;
	case 4:
		dialogueOutput = "Hmm, it looks like the question marks mean I've got a " + insertInfo + " right but the wrong place... "
			+ "and the circles mean I've got it in the right place! This should make things easier... "
			+ "slightly.\n I better write this down.";
		break;
	case 5:
		int repeatIndex;
		repeatIndex = rand() % 3;
		dialogueOutput = repeatOptions[repeatIndex];
		break;
	case 6:
		dialogueOutput = "The code definitely doesn't have those, I can only use " + insertInfo;
		break;
	case 7:
		dialogueOutput = "Alright! Just one more to go. I can do this.";
		break;
	case 8:
		dialogueOutput = "Crap! I can hear the guards downstairs. I better hurry, I think I can try two more times.";
		break;
	case 9:
		dialogueOutput = "Crap! If I stay any longer they'll catch me. I better get back to Joel, I hope he's okay...";
		break;
	case 10:
		dialogueOutput = "YES! Hell yeah! I did it! I actually did it! I better grab those antibiotics.";
		break;
	case 11:
		dialogueOutput = "YES! Hell yeah access granted! \nAnd I think I have time to swipe some other supplies too!";
	case 12:
		dialogueOutput = "ACCESS GRANTED! Hell YES! There's even food in here! We'll be set for weeks!";
	}

	return dialogueOutput;
}


//=======================================================================================
//                               PRIVATE: MUTATOR METHODS
//=======================================================================================
	void Ellie::setEllieVariables() {
		*firstZero = new bool(true);
		
		string phrasesZero[7] = {"Ugh, not even close.", "Nope, that's for sure not it.", "Annnnnd.... A whole lot of nada.",
			"Yep... still a big fat zero.", "At this rate, I'm going to need a flame thrower to get in here.",
			"C'mon, " + *playerName + "! \nI got this. \nEndure and Survive.",
			"Why don't people write their keycodes on paper and leave them lying around anymore." };

		zeroOptions = new string[int(zeroSize)];
		zeroOptions = phrasesZero;

		
		string phrasesRepeat[3] = { "Dammit, I've already tried that one. I need to think about this more carefully.",
			"I think I already... \nYep, already tried it. C'mon " + *playerName + ", think!",
			"Well if it didn't work the last time I don't know why it would now..." };

		repeatOptions = new string[int(repeatSize)];
		repeatOptions = phrasesRepeat;
	}

	void Ellie::resetEllieValues() {
		*firstZero = new bool(true);
		resetScore();
	}
	
		
	

	
	
	
	

	

	