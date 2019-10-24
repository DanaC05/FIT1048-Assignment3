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
};

#endif // !CUSTOMPLAYER_H

