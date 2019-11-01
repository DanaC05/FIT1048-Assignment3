/**************************************************
Project: Mastermind: The Last Of Us Edition
Assignment Num: 3
Author: Dana Casella
Purpose: Mastermind Class Header
**************************************************/
#ifndef MASTERMIND_H
#define MASTERMIND_H

#include <conio.h>
#include <stdio.h>
#include "windows.h"
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <array>
#include <set>
#include <vector>
#include <ctime>
#include <stdexcept>
#include "Ellie.h"
#include "CustomPlayer.h"
#include "Normal.h"
#include "Hard.h"
#include "Survivor.h"
#include "Grounded.h"
#include "Scenario.h";
using namespace std;

class Mastermind
{
public:
	// constructors
	Mastermind();
	~Mastermind();

	// accessor methods
	void startGame();

private:
	// variables
	Player* player;
	MastermindBoard* gameBoard;
	Scenario* gameScenario;
	const string* uiFileName = new string("gameUI/playerUI.txt");
	const string* loadingFileName = new string("screens/TLOUFireflies.txt");
	const string* titleFileName = new string("screens/TLOUTitle.txt");
	const string* creditsFileName = new string("screens/credits.txt");
	const string* introFileName = new string("gameInfo/mastermindTLOU.txt");
	const string* playerFileName = new string("gameInfo/playerChoiceInfo.txt");
	const string* difficultyFileName = new string("gameInfo/mastermindDifficulty.txt");
	const string* helpFileName = new string("gameInfo/mastermindHelp.txt");
	const string* enterFileName = new string("text/enterYourName.txt");
	const string* selectFileName = new string("text/selectDifficulty.txt");
	const string* wouldFileName = new string("text/wouldYouLikeTo.txt");
	const string* continueFileName = new string("text/continue.txt");
	const string* loadFileName = new string("text/loadGame.txt");
	const string* saveGameFileName = new string("text/saveGame.txt");
	const string* quitGameFileName = new string("text/quitGame.txt");
	const string* congratsFileName = new string("text/congratulations.txt");
	const string* playerSavesFileName = new string("saveFiles/mastermindSaveFiles.txt");
	string* keycodeElements;
	string* secretCode;
	string* invalidInput;
	bool* gameWon;
	bool* gameRunning;
	bool* playerQuitGame;
	bool* showDialogue;
	enum {
		KEY_ENTER = 13,
		KEY_UP = -32 + 72,
		KEY_DOWN = -32 + 80
	};

	// accessor methods
	void mainMenu();
	void newGame();
	void loadGame(int saveFile);
	void runGame();
	void saveGame();
	void quitGame();
	void continueGame();
	void gameOver(bool playerWon);
	void gameComplete();
	void rollCredits();
	int mainMenuChoice();
	bool isGameOver();
	bool checkAttemptValidity(string guess);
	bool checkSaveFile();
	string askForString(string prompt);
	string getLineFromFile(string fileName, int lineNumber);
	int getLineCount(string fileName);
	string getCurrentDate();
	void displayLoadingScreen();
	void displayTitleScreen();
	void displaySaveFiles();
	void displayCharacterInformation();
	void displayScenarioInfo();
	void displayGameStartMessage();
	void displayHelpInformation();
	void displayRelevantDialogue(string hint, string guess);
		
	// mutator methods
	void setGameAttribtutes();
	void setPlayer();
	void setDifficulty();
	void setBoard(int difficulty);
	void generateSecretCode();
	void playTurn();
	void executePlayerTurn(string playerChoice);
	string generateHint(string guess);
	string generateSaveData();
	void resetGameAssets();
	int windowsSelect(vector<string> optionVector, int numOptions, string fileName, string optionsIndent = "", bool extraItemToPrint = false);
	void printVector(vector<string> vectorToPrint, int numItems, int insertIndex = -1, string insertElement = "", string elementIndent = "", bool extraItemToPrint = false);
	void printTextFile(string fileName, int delay = 0, string indent = "");
};

#endif // !MASTERMIND_H

