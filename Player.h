/**************************************************
Project: Mastermind: The Last Of Us Edition
Assignment Num: 3
Author: Dana Casella
Purpose: Player Class Header
**************************************************/
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
using namespace std;

class Player
{
public:
	// construtors
	Player();
	Player(string name);
	~Player();

	// accessor methods
	string name();
	int score();
	int gamesWon();
	int level();
	virtual string getDialogue(int phraseID, string insertInfo = "") = 0;
	
	// mutator methods
	void increaseScore(int points);
	void addGameWon();
	void resetGameStats();
	void resetScore();
	void promotePlayer();
	void setPlayerLevel(int level);

protected:
	// variables
	int* numGamesWon;
	int* playerScore;
	int* playerLevel;
	string* playerName;
};

#endif // !PLAYER_H