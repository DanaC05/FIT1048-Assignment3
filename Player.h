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

	// mutator methods
	void increaseScore(int points);
	void addGameWon();
	void addGameLossed();
	void resetGameStats();
	void resetScore();
	void promotePlayer();

	// accessor methods
	string name();
	int score();
	int gamesWon();
	int gamesLossed();
	int level();
	bool playerPromoted();
	void setPlayerLevel(int level);

protected:
	// variables
	int* numGamesWon;
	int* numGamesLossed;
	int* playerScore;
	int* playerLevel;
	string* playerName;
	bool* promotion;

	// mutator methods
	void setPlayerVariables();
};

#endif // !PLAYER_H