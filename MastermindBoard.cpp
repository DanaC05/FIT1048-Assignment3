/**************************************************
Project: Mastermind: The Last Of Us Edition
Assignment Num: 3
Author: Dana Casella
Purpose: MastermindBoard Class File

This class inherits from the Board class and 
contains all the functionallity for game boards
used in mastermind.
**************************************************/
#include "MastermindBoard.h"

//=======================================================================================
//                                 PUBLIC: DESTRUCTOR
//=======================================================================================
MastermindBoard::~MastermindBoard() {
	delete playerAttempts;
	delete playerHints;
	delete boardFileName;
	delete attemptsFileName;
	delete lastHintGiven;
	delete lastGuessGiven;
}

//=======================================================================================
//                               PUBLIC: ACCESSOR METHODS
//=======================================================================================
void MastermindBoard::displayBoard(bool codeEntered) {
	if (*numAttempts == 0) {
		printEmptyBoard();
	}
	else {
		printBoardWithMoves(codeEntered);
	}
}

void MastermindBoard::displayPlayerAttempts() {
	string playerAttemptsData;
	string playerAttemptsString = "";
	ifstream attemptsTextFile;

	if (*numAttempts == 0) {
		attemptsTextFile.open(*attemptsFileName);
		while (getline(attemptsTextFile, playerAttemptsData)) {
			playerAttemptsString += "\t\t\t\t\t\t" + playerAttemptsData + "\n";
		}
	}
	else {
		playerAttemptsString = generateAttemptsString();
	}

	cout << playerAttemptsString << endl;
	attemptsTextFile.close();
}

void MastermindBoard::endAnimation(string itemFile) {
	string spacing = "\n";
	ifstream itemTextFile(itemFile);
	string itemData;

	for (int i = 0; i < 8; i++) {
		// clear screen
		system("cls");

		// add spcaing before board
		cout << spacing << endl;

		// display board
		printBoardWithMoves(false);

		Sleep(100);
		// increase spacing
		spacing += "\n";
	}

	// clear screen
	system("cls");

	for (int j = 0; j < 3; j++) {
		cout << spacing << endl;

		// display board
		printBoardWithMoves(false);

		Sleep(200);

		system("cls");

		cout << spacing << endl;
		printEmptyBoard();

		Sleep(200);

		system("cls");
	}
	
	if (itemFile != "") {
		cout << spacing << endl;
		// display antibiotics
		while (getline(itemTextFile, itemData)) {
			cout << itemData << endl;
		}
		itemTextFile.close();
	}

	else {
		cout << spacing << endl;
		printBoardWithMoves(false);
	}
}

string MastermindBoard::validBoardCharacters() {
	return *possibleCodeElements;
}

string MastermindBoard::validSymbolGroup() {
	return *validSymbols;
}

string MastermindBoard::lastHint() {
	return *lastHintGiven;
}

string MastermindBoard::lastGuess() {
	return *lastGuessGiven;
}

string MastermindBoard::generateHintData() {
	string hintsData = "";

	for (int i = 0; i < *numAttempts; i++) {
		if (i == *numAttempts - 1) {
			hintsData += playerHints[i];
		}
		hintsData += playerHints[i] + ", ";
	}

	return hintsData;
}

string MastermindBoard::generateAttemptData() {
	string attemptsData = "";

	for (int i = 0; i < *numAttempts; i++) {
		if (i == *numAttempts - 1) {
			attemptsData += playerAttempts[i];
		}
		else {
			attemptsData += playerAttempts[i] + ", ";
		}
	}

	return attemptsData;
}

string MastermindBoard::wordLibraryName() {
	return "";
}

int MastermindBoard::wordLibrarySize() {
	return 0;
}

//=======================================================================================
//                               PUBLIC: MUTATOR METHODS
//=======================================================================================
void MastermindBoard::addTurn(string guess, string hint) {
	addAttempt();
	playerAttempts[int(*numAttempts - 1)] = guess;
	playerHints[int(*numAttempts - 1)] = hint;
	*lastHintGiven = hint;
	*lastGuessGiven = guess;
}

void MastermindBoard::loadGuesses(string guesses) {
	string guess;
	int characterIndex = 0;
	int attemptsIndex = 0;

	while (characterIndex < guesses.size()) {
		guess = guesses[characterIndex];

		for (int i = 1; i < 4; i++) {
			guess += guesses[characterIndex + i];
		}

		// add hint to attempts array
		playerAttempts[attemptsIndex] = guess;
		attemptsIndex += 1;

		// catch up to the index reached in for loop
		characterIndex += 3;

		// add 2 to skip over ', '
		characterIndex += 3;
	}
}

void MastermindBoard::loadHints(string hints) {
	string hint;
	int characterIndex = 0;
	int hintsIndex = 0;

	while (characterIndex < hints.size()) {
		hint = hints[characterIndex];

		for (int i = 1; i < 4; i++) {
			hint += hints[int(characterIndex) + i];
		}

		// add hint to hints array
		playerHints[hintsIndex] = hint;
		hintsIndex += 1;

		// catch up to the index reached in for loop
		characterIndex += 3;

		// add 2 to skip over ', '
		characterIndex += 3;
	}
}

//=======================================================================================
//                               PROTECTED: ACCESSOR METHODS
//=======================================================================================
void MastermindBoard::boardSetup() {
	numAttempts = new int(0);
	playerAttempts = new string[int(*maxAttempts)];
	playerHints = new string[int(*maxAttempts)];
	lastHintGiven = new string("");
	lastGuessGiven = new string("");
}

void MastermindBoard::printEmptyBoard() {
	string boardDataString;
	ifstream boardTextFile;
	boardTextFile.open(*boardFileName);

	cout << "\n\n" << endl;

	while (getline(boardTextFile, boardDataString)) {
		cout << "\t\t\t\t\t     " << boardDataString << endl;
	}

	boardTextFile.close();
}

void MastermindBoard::printBoardWithMoves(bool flash) {
	string boardString = "";
	string boardDataString;
	ifstream boardTextFile(*boardFileName);
	string dataToAdd;
	string lineToAdd;
	int currentLine = 0;

	while (getline(boardTextFile, boardDataString)) {
		dataToAdd = "";
		lineToAdd = boardDataString;
	
		if (currentLine == 8) {
			int numCharacters = 13;

			if (playerHints[int(*numAttempts - 1)] == "won") {
				dataToAdd = "ACCESS GRANTED";
				numCharacters = 14;
			}
			else {
				dataToAdd = "ACCESS DENIED";
			}

			lineToAdd.replace(65, numCharacters, dataToAdd);
			boardString += "\t\t\t\t\t     " + lineToAdd + "\n";
		}
		else if (currentLine == 9) {
			dataToAdd = playerHints[int(*numAttempts - 1)];

			if (dataToAdd == "won") {
				dataToAdd = "    ";
			}

			lineToAdd.replace(69, 4, dataToAdd);
			boardString += "\t\t\t\t\t     " + lineToAdd + "\n";
		}
		else if (currentLine == 13) {
			for (int i = 0; i < 4; i++) {
				char guessElement = playerAttempts[int(*numAttempts - 1)][i];
				lineToAdd.replace((i + 1)*10, 1, string(1, guessElement));
			}

			boardString += "\t\t\t\t\t     " + lineToAdd + "\n";
		}
		else {
			boardString += "\t\t\t\t\t     " + boardDataString + "\n";
		}

		currentLine += 1;
	}

	if (flash) {
		for (int i = 0; i < 2; i++) {
			system("cls");

			cout << "\n\n\n" << boardString << endl;

			Sleep(150);

			system("cls");

			printEmptyBoard();

			Sleep(150);
		}

		system("cls");
	}

	
	
	cout << "\n\n\n" << boardString << endl;
	boardTextFile.close();
}

string MastermindBoard::generateAttemptsString() {
	string playerAttemptsData;
	string playerAttemptsString = "";
	string currentLineAttemptInfo;
	ifstream attemptsTextFile;
	int currentIndex = 0;
	int currentLine = 0;


	attemptsTextFile.open(*attemptsFileName);

	// iterate through attempt display template text file
	while (getline(attemptsTextFile, playerAttemptsData)) {
		if (currentIndex < *numAttempts && currentLine > 3 && currentLine % 2 == 0) {
			string stringToAdd = playerAttemptsData;

			// add
			if (currentIndex < 8) {
				currentLineAttemptInfo = playerAttempts[int(currentIndex)] + "   " + playerHints[int(currentIndex)];
				stringToAdd.replace(22, 11, currentLineAttemptInfo);
			}

			if (*numAttempts > 8 && (currentIndex + 8) < *numAttempts) {
				currentLineAttemptInfo = this->playerAttempts[currentIndex + 8] + "   " + playerHints[int(currentIndex + 8)];
				stringToAdd.replace(43, 11, currentLineAttemptInfo);
			}

			playerAttemptsString += "\t\t\t\t\t\t" + stringToAdd + "\n";
			currentIndex += 1;
		}
		else {
			playerAttemptsString += "\t\t\t\t\t\t" + playerAttemptsData + "\n";
		}

		currentLine += 1;
	}

	attemptsTextFile.close();
	return playerAttemptsString + "\n\n\n\n\n\n\n\n\n\n\n\n\n";
}