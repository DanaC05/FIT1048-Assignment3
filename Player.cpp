/**************************************************
Project: Mastermind: The Last Of Us Edition
Assignment Num: 3
Author: Dana Casella
Purpose: Player Class File

This is an abstract class that acts as a generic
template for it's subclasses (players).
**************************************************/
#include "Player.h"

//=======================================================================================
//                                 PUBLIC: CONSTRUCTORS
//=======================================================================================
Player::Player() {
	playerName = new string("");
	playerScore = new int(0);
	playerLevel = new int(1);
	numGamesWon = new int(0);
}

Player::Player(string name) {
	playerName = new string(name);
	playerScore = new int(0);
	playerLevel = new int(1);
	numGamesWon = new int(0);
}

Player::~Player() {
	delete playerName;
	delete playerScore;
	delete playerLevel;
	delete numGamesWon;
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

void Player::resetGameStats() {
	*numGamesWon = 0;
}

void Player::resetScore() {
	*playerScore = 0;
}

void Player::promotePlayer() {
	*playerLevel += 1;
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

int Player::level() {
	return *playerLevel;
}
