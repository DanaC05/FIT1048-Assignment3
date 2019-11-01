/**************************************************
Project: Mastermind: The Last Of Us Edition
Assignment Num: 3
Author: Dana Casella
Purpose: Scenario Class File

This class holds all parameters for the various
scenarios used in mastermind.
**************************************************/
#include "Scenario.h"

//=======================================================================================
//                                 PUBLIC: CONSTRUCTORS
//=======================================================================================
Scenario::Scenario() {
	firstScenarioPlayed = new bool(false);
	playerFree = new bool(true);
	scenarioNumber = new int(0);
	start = new string("");
	endWin = new string("");
	endLose = new string("");
	enemy = new string("");
	objective = new string("");
	item = new string("");
	textFileName = new string("");
	startInfoFile = new string("");

	// seed randoms
	srand(unsigned(time(NULL)));
}

Scenario::~Scenario() {
	delete firstScenarioPlayed;
	delete playerFree;
	delete scenarioNumber;
	delete start;
	delete endWin;
	delete endLose;
	delete enemy;
	delete objective;
	delete item;
	delete textFileName;
	delete startInfoFile;
}

//=======================================================================================
//                               PUBLIC: ACCESSOR METHODS
//=======================================================================================
void Scenario::lastScenario() {
	// scenario for the final game
	*playerFree = true;
	*firstScenarioPlayed = true;
	*start = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t[You are standing in front of the safe containing the information you need. You check one last time to see if the coast is clear.\n\n\n\n\n\n]";
	*endWin = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t[You read the documents and finally have the whereabouts of the fireflies. You leave the facility with Joel, ready for whatever comes next.]";
	*endLose = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t[Just before you're able to escape the building a soldier grabs you. You are taken back to their nearest outpost and imprisoned for being in a restricted area.]";
	*enemy = "soldiers";
	*objective = "safe";
	*item = "grab those documents.";
	*textFileName = "screens/winScreenDocuments.txt";
	*startInfoFile = "scenarios/mastermindScenario3.txt";
	*scenarioNumber = 3;
}

void Scenario::setScenario() {
	// sets the appropriate scenario for the game
	if (*playerFree) {
		if (*firstScenarioPlayed) {
			int scenarioIndex = rand() % 4 + 4;

			switch (scenarioIndex) {
			case 4:
				foodShortage();
				break;
			case 5:
				ammoOut();
				break;
			case 6:
				winter();
				break;
			case 7:
				supplyRun();
				break;
			}
		}
		else {
			joelInjured();
		}
	}
	else {
		imprisoned();
	}
}

string Scenario::getScenarioInfo() {
	return *startInfoFile;
}

int Scenario::getScenario() {
	return *scenarioNumber;
}

string Scenario::getStartMessage() {
	return *start;
}

string Scenario::getGameOverMessage() {
	*playerFree = false;
	return *endLose;
}

string Scenario::getGameWonMessage() {
	*playerFree = true;
	*firstScenarioPlayed = true;
	return *endWin;
}

string Scenario::getEnemy() {
	return *enemy;
}

string Scenario::getObjective() {
	return *objective;
}

string Scenario::getItem() {
	return *item;
}

string Scenario::getItemTextFile() {
	return *textFileName;
}

//=======================================================================================
//                               PUBLIC: MUTATOR METHODS
//=======================================================================================
void Scenario::loadScenario(int scenarioNum) {
	// allows for scenario to be loaded when player loads a game
	switch (scenarioNum) {
	case 1:
		joelInjured();
		break;
	case 2:
		imprisoned();
		break;
	case 3:
		lastScenario();
		break;
	case 4:
		foodShortage();
		break;
	case 5:
		ammoOut();
		break;
	case 6:
		winter();
		break;
	case 7:
		supplyRun();
		break;
	}

	if (scenarioNum > 1) {
		*firstScenarioPlayed = true;
	}
}

//=======================================================================================
//                               PRIVATE: MUTATOR METHODS
//=======================================================================================
void Scenario::joelInjured() {
	// first scenario to be played
	*start = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t[You are standing just outside the office containing the medical supplies, you check one last time to see if the coast is clear.]\n\n\n\n\n\n";
	*endWin = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t[You manage to sneak out of the building without being spotted and return to Joel with the antibiotics in hand.]";
	*endLose = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t[Just before you're able to escape the building a soldier grabs you. You are taken back to their nearest outpost and imprisoned for being in a restricted area.]";
	*enemy = "guards";
	*objective = "door";
	*item = "grab those antibiotics.";
	*textFileName = "screens/winScreenMeds.txt";
	*startInfoFile = "scenarios/mastermindScenario1.txt";
	*scenarioNumber = 1;
}

void Scenario::imprisoned() {
	// scenario after player looses a game
	*firstScenarioPlayed = true;
	*playerFree = false;
	*start = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t[You are in your cell, the guards have finally left on another patrol.]\n\n\n\n\n\n]";
	*endWin = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t[You manage to sneak out of the cell without alerting any guards and head back to your camp with Joel.]";
	*endLose = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t[The soldiers return before you were able to decipher the combination. You sit in your cell and wait for the next opportunity.]";
	*enemy = "guards";
	*objective = "door";
	*item = "get out of here.";
	*textFileName = "screens/winScreenFree.txt";
	*startInfoFile = "scenarios/mastermindScenario2.txt";
	*scenarioNumber = 2;
}

void Scenario::foodShortage() {
	// food shortage scenario
	*firstScenarioPlayed = true;
	*start = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t     [You hear clickers moving downstairs but are sure none are nearby.... For now.]\n\n\n\n\n\n";
	*endWin = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t[You manage to sneak past the clickers and head back to Joel with much needed food in hand.]";
	*endLose = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t[You disturb the clickers and have to shoot your way out. Just as you run out of the building a soldier grabs you. You are taken back to their nearest outpost and imprisoned for being in a restricted area.]";
	*enemy = "clickers";
	*objective = "door";
	*item = "grab all this food.";
	*textFileName = "screens/winScreenFood.txt";
	*startInfoFile = "scenarios/mastermindScenario4.txt";
	*scenarioNumber = 4;
}

void Scenario::ammoOut() {
	// ammo shortage scenario
	*firstScenarioPlayed = true;
	*start = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t     [You are in the back room of the warehouse, you check one last time to see if the coast is clear.]\n\n\n\n\n\n";
	*endWin = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t  [You manage to sneak out without being spotted and return to Joel with a bag full of ammo.]";
	*endLose = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t[Just before you're able to escape the building a soldier grabs you. You are taken back to their nearest outpost and imprisoned for being in a restricted area.]";
	*enemy = "soldiers";
	*objective = "safe";
	*item = "grab all that ammo.";
	*textFileName = "screens/winScreenAmmo.txt";
	*startInfoFile = "scenarios/mastermindScenario5.txt";
	*scenarioNumber = 5;
}

void Scenario::winter() {
	// in need of warm cloting scenario
	*firstScenarioPlayed = true;
	*start = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t    [You are standing just outside the bunker door, you check one last time to see if the coast is clear.]\n\n\n\n\n\n";
	*endWin = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t[You manage to make it through the area without being spotted and return to Joel with an armful of warm clothes.]";
	*endLose = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t[Just before you're able to escape the area a soldier grabs you. You are taken back to their nearest outpost and imprisoned for being in a restricted area.]";
	*enemy = "soldiers";
	*objective = "door";
	*item = "grab those coats";
	*textFileName = "screens/winScreenWinter.txt";
	*startInfoFile = "scenarios/mastermindScenario6.txt";
	*scenarioNumber = 6;
}

void Scenario::supplyRun() {
	// supply shortage scenario
	*firstScenarioPlayed = true;
	*start = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t     [You hear clickers moving downstairs but are sure none are nearby.... For now.]\n\n\n\n\n\n";
	*endWin = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t[You manage to sneak past the clickers and head back to Joel with much needed supplies in hand.]";
	*endLose = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t[You disturb the clickers and have to shoot your way out. Just as you run out of the building a soldier grabs you. You are taken back to their nearest outpost and imprisoned for being in a restricted area.]";
	*enemy = "clickers";
	*objective = "safe";
	*item = "grab these suppies";
	*textFileName = "screens/winScreenSupplies.txt";
	*startInfoFile = "scenarios/mastermindScenario7.txt";
	*scenarioNumber = 7;
}