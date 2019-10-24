#ifndef MASTERMIND_H
#define MASTERMIND_H

#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include "windows.h"
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <ctime>
#include "Ellie.h"
#include "CustomPlayer.h"
#include "Normal.h"
#include "Hard.h"
#include "Survivor.h"
#include "Grounded.h"
using namespace std;

class Mastermind
{
public:
	// constructors
	Mastermind();
	~Mastermind();

	// accessor methods
	void runGame();
	void testDisplay(); //to be removed when program is complete

private:
	// variables
	Player* player;
	Board* gameBoard;
	const string* uiFileName = new string("gameUI/playerUI.txt");
	const string* loadingFileName = new string("screens/TLOUFireflies.txt");
	const string* titleFileName = new string("screens/TLOUTitle.txt");
	const string* introFileName = new string("gameInfo/mastermindTLOU.txt");
	const string* playerFileName = new string("gameInfo/playerChoiceInfo.txt");
	const string* difficultyFileName = new string("gameInfo/mastermindDifficulty.txt");
	const string* enterFileName = new string("text/enterYourName.txt");
	const string* selectFileName = new string("text/selectDifficulty.txt");
	const string* wouldFileName = new string("text/wouldYouLikeTo.txt");
	const string* saveFileDirectory = new string("saveFiles");
	string* keycodeElements;
	string* secretCode;
	bool* playerSelected;
	bool* changeDifficulty;
	bool* loadGameSelected;
	bool* gameWon;
	enum {
		KEY_ENTER = 13,
		KEY_UP = -32 + 80,
		KEY_DOWN = -32 + 72
	};
	int* currentGameDifficulty;

	// accessor methods
	bool isGameOver();
	void displayLoadingScreen();
	void displayTitleScreen();
	void displayGameInfo();
	int mainMenuChoice();
	void displayDifficultyInfo();
	bool checkSaveFile();
	void displayPlayerUI();
	void newGame();
	void loadGame();
	void returnToMenu();
	void gameOver();
	void quitGame();

	// mutator methods
	void setGameAttribtutes();
	void setPlayer();
	void setDifficulty();
	void setBoard(int difficulty);
	void generateSecretCode();
	void playTurn();

	void executePlayerTurn();
	
	void generateHint();
	string generateSaveData();
	int windowsSelect(vector<string> optionVector, int numOptions, string fileName, string optionsIndent = "");
	void printTextFile(string fileName, int delay = 0, string indent = "");
	void printVector(vector<string> vectorToPrint, int numItems, int insertIndex = -1, string insertElement = "", string elementIndent = "");
};

#endif // !MASTERMIND_H

