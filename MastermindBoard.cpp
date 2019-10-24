#include "MastermindBoard.h"

//=======================================================================================
//                                 PUBLIC: DESTRUCTOR
//=======================================================================================

MastermindBoard::~MastermindBoard() {
	delete playerAttempts;
	delete playerHints;
	delete boardFileName;
	delete attemptsFileName;
}

//=======================================================================================
//                               PUBLIC: ACCESSOR METHODS
//=======================================================================================
void Board::displayBoard(string boardString) {
	cout << boardString << endl;
}

void MastermindBoard::displayPlayerAttempts() {
	string playerAttemptsData;
	string playerAttemptsString = "";
	ifstream attemptsTextFile;

	if (*maxAttempts == 0) {
		attemptsTextFile.open(*attemptsFileName);
		while (getline(attemptsTextFile, playerAttemptsData)) {
			playerAttemptsString += playerAttemptsData + "\n";
		}
	}
	else {
		playerAttemptsString = generateAttemptsString();
	}

	cout << playerAttemptsString << endl;
	attemptsTextFile.close();
}

//=======================================================================================
//                               PUBLIC: MUTATOR METHODS
//=======================================================================================
void MastermindBoard::addTurn(string guess, string hint) {
	addAttempt();
	playerAttempts[int(numAttempts - 1)] = guess;
	playerHints[int(numAttempts - 1)] = hint;
}

//=======================================================================================
//                               PRIVATE: ACCESSOR METHODS
//=======================================================================================
string MastermindBoard::generateBoardString() {
	string boardString = "";
	string boardDataString;
	ifstream boardTextFile;

	if (*numAttempts == 0) {
		boardTextFile.open(*boardFileName);
		while (getline(boardTextFile, boardDataString)) {
			boardString += boardDataString + "\n";
		}
	}
	else {
		string dataToAdd;
		string lineToAdd;
		int currentLine = 0;

		while (getline(boardTextFile, boardDataString)) {
			dataToAdd = "";
			lineToAdd = boardDataString;
			if (currentLine == 8) {
				int numCharacters = 13;

				if (playerHints[int(numAttempts - 1)] == "won") {
					dataToAdd = "ACCESS GRANTED";
					numCharacters = 14;
				}
				else {
					dataToAdd = "ACCESS DENIED";
				}

				lineToAdd.replace(65, numCharacters, dataToAdd);
				boardString += lineToAdd + "\n";
			}
			else if (currentLine == 9) {
				dataToAdd = playerHints[int(numAttempts - 1)];

				if (dataToAdd == "won") {
					dataToAdd = "    ";
				}

				lineToAdd.replace(69, 4, dataToAdd);
				boardString += lineToAdd + "\n";
			}
			else if (currentLine == 13) {
				for (int i = 0; i < 4; i++) {
					char guessElement = playerAttempts[int(numAttempts - 1)][i];
					lineToAdd.replace((i + 1) * 10, 1, string(1, guessElement));
				}

				boardString += lineToAdd + "\n";
			}
			else {
				boardString += boardDataString + "\n";
			}

			currentLine += 1;
		}

		boardTextFile.close();
		return boardString;
	}
	boardTextFile.close();
	return boardString;
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
				currentLineAttemptInfo = this->playerAttempts[currentIndex + 8] + "   " + playerAttempts[int(currentIndex + 8)];
				stringToAdd.replace(43, 11, currentLineAttemptInfo);
			}

			playerAttemptsString += stringToAdd + "\n";
			currentIndex += 1;
		}
		else {
			playerAttemptsString += playerAttemptsData + "\n";
		}

		currentLine += 1;
	}

	attemptsTextFile.close();
	return playerAttemptsString;
}

//=======================================================================================
//                               PRIVATE: MUTATOR METHODS
//=======================================================================================
void MastermindBoard::mastermindSetup() {
	boardSetup();
	playerAttempts = new string[int(*maxAttempts)];
	playerHints = new string[int(*maxAttempts)];
}

void Board::boardSetup() {
	numAttempts = new int(0);
}

