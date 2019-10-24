#include "Player.h"

//=======================================================================================
//                                 PUBLIC: CONSTRUCTORS
//=======================================================================================
Player::Player() {
	setPlayerVariables();
}

Player::Player(string name) {
	playerName = new string(name);
	setPlayerVariables();
}

Player::~Player() {
	delete playerName;
	delete playerScore;
	delete numGamesWon;
	delete numGamesLossed;
	delete promotion;
}

//=======================================================================================
//                               PUBLIC: MUTATOR METHODS
//=======================================================================================
void Player::increaseScore(int points) {
	*playerScore += points;
}

void Player::addGameWon() {
	*numGamesWon += 1;
}

void Player::addGameLossed() {
	*numGamesLossed += 1;
}

void Player::resetGameStats() {
	*numGamesWon = 0;
	*numGamesLossed = 0;
}

void Player::resetScore() {
	*playerScore = 0;
	*promotion = false;
}

void Player::promotePlayer() {
	if (*playerLevel < 5) {
		*playerLevel += 1;
		resetGameStats();
		*promotion = true;
	}
}

void Player::setPlayerLevel(int level) {
	*playerLevel = level;
}

//=======================================================================================
//                               PUBLIC: ACCESSOR METHODS
//=======================================================================================
string Player::name() {
	return *playerName;
}

int Player::score() {
	return *playerScore;
}

int Player::gamesWon() {
	return *numGamesWon;
}

int Player::gamesLossed() {
	return *numGamesLossed;
}

int Player::level() {
	return *playerLevel;
}

bool Player::playerPromoted() {
	return *promotion;
}

//=======================================================================================
//                               PRIVATE: MUTATOR METHODS
//=======================================================================================
void Player::setPlayerVariables() {
	playerScore = new int(0);
	playerLevel = new int(0);
	numGamesWon = new int(0);
	numGamesLossed = new int(0);
	promotion = new bool(false);
}