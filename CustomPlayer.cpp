#include "CustomPlayer.h"

//=======================================================================================
//                                 PUBLIC: CONSTRUCTORS
//=======================================================================================
CustomPlayer::CustomPlayer(string name) {
	playerName = new string(name);
	setPlayerVariables();
}



string CustomPlayer::getDialogue(int phraseID, string insertInfo = "") {
	string dialogueOutput = "";
	switch (phraseID) {
	case 1:
		dialogueOutput = "The guards have left. I'll have " + insertInfo + " attempts at the door until they come back.";
		break;
	case 2:
		dialogueOutput = "I haven't made any attempts yet...";
		break;
	case 3:
		dialogueOutput = "I think the question marks mean a character is correct but in the wrong place and the circles indicate it's in the right place.";
		break;
	case 4:
		dialogueOutput = "Whoops, I've already tried that one.";
		break;
	case 5:
		dialogueOutput = "Uh oh, the code won't have those, I can only use " + insertInfo;
		break;
	case 6:
		dialogueOutput = "I can hear the guards walking around downstairs. I better hurry, I might be able to try two more times.";
		break;
	case 7:
		dialogueOutput = "Oh no! The guards are coming. Maybe Joel will be okay without the medicine.... or maybe not";
		break;
	case 8:
		dialogueOutput = "YES! I did it! I better get the antibotics and get out of here.";
		break;
	case 9:
		dialogueOutput = "YES! I did it! And with time to spare. I can grab a few other things whilst I'm here";
	case 10:
		dialogueOutput = "YES! I got it! They've got so much stuff in here! We'll be set for ages!";
	}

	return dialogueOutput;
}
