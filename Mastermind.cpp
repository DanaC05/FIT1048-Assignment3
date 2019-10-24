#include "Mastermind.h"

//=======================================================================================
//                                 PUBLIC: CONSTRUCTORS
//======================================================================================
Mastermind::Mastermind() {
	// seed randoms
	srand(unsigned(time(NULL)));
	
	// initiate variables
	loadGameSelected = new bool(false);
	playerSelected = new bool(false);
	changeDifficulty = new bool(true);
	gameWon = new bool(false);
	saveProgressSelected = new bool(false);
}

Mastermind::~Mastermind() {
	delete uiFileName;
	delete loadingFileName;
	delete titleFileName;
	delete introFileName;
	delete difficultyFileName;
	delete enterFileName;
	delete selectFileName;
	delete wouldFileName;
	delete saveFileDirectory;
	delete loadGameSelected;
	delete gameWon;
	delete keycodeElements;
	delete currentGameDifficulty;
	delete playerSelected;
	delete changeDifficulty;
	delete saveProgressSelected;
	delete keycodeCharacters;
}

//=======================================================================================
//                              PUBLIC: ACCESSOR METHODS
//=======================================================================================
void Mastermind::runGame() {
	// clear screen
	system("cls");

	// display game title
	displayTitleScreen();

	// display loading screen
	displayLoadingScreen();

	// display main menu and start game (based on player choice)////////////////TODO: add choice to ave game (allows to save progress without having to be in game)
	mainMenuChoice();

	///////////////////////////////////////////////////////////////// TODO: add method to play one game - condition for load game as well
	/// start game (based on menu choice
}

void Mastermind::testDisplay() {
	
}


//=======================================================================================
//                                   PLACEMENT TBA
//=======================================================================================




//=======================================================================================
//                              PRIVATE: ACCESSOR METHODS
//=======================================================================================
void Mastermind::displayLoadingScreen() {
	system("cls");
	string loading = "\t\t\t\t\t\t\t    Loading.";

	// loop through 'loading...' three times
	for (int i = 0; i < 9; i++) {
		string fireflyFileData = "";
		ifstream fireflyFile;
		fireflyFile.open(*loadingFileName);

		int lineNumber = 1;
		cout << "\n\n\n" << endl;

		while (getline(fireflyFile, fireflyFileData)) {
			// print loading string
			if (lineNumber == 33) {
				cout << loading << endl;
			}
			// print line from file (firefly symbol)
			else {
				cout << "\t\t" << fireflyFileData << endl;
			}
			lineNumber += 1;
		}

		cout << "\n" << endl;

		// wait 500ms and clear the screen
		Sleep(500);
		system("cls");

		// reset loading string every third time throug loop
		if ((i + 1) % 3 == 0) {
			loading = "\t\t\t\t\t\t\t    Loading.";
		}
		// add '.' to loading string
		else {
			loading += ".";
		}
	}
	// clear screen and add whitespace to center title (to be displayed next)
	system("cls");
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
}

void Mastermind::displayTitleScreen() {
	// clear screen
	system("cls");

	cout << "\n\n\n\n\n\n\n\n\n" << endl;
	cout << "\t\t\t\t\t\t     MasterMind Presents..." << endl;

	// print text file (game title) with a delay of 300ms between each line print
	printTextFile(*titleFileName, 300);
}

void Mastermind::displayGameInfo() {
	// clear screen
	system("cls");

	cout << "\n\n\n" << endl;

	// print text file (game info) with no delay and add '\t\t\t\t 
	// to the start of each line
	printTextFile(*introFileName, 0, "\t\t\t\t");

	cout << "\n\n\n\n" << endl;

	// wait for user to continue
	system("pause");
}

int Mastermind::mainMenuChoice() {
	int numOptions = 2;
	int playerChoice;
	vector<string> gameStart;

	// add options to gamestart vector
	gameStart.push_back("New Game");
	if (checkSaveFile()) {
		gameStart.push_back("Load Game");
		numOptions = 3;
	}
	gameStart.push_back("Quit");

	system("cls");

	playerChoice = windowsSelect(gameStart, numOptions, *titleFileName, "\t ");
	return playerChoice;
}

void Mastermind::displayDifficultyInfo() {
	cout << "\n\n\n\n\n\n\n" << endl;

	// print text file (difficulty info) with no delay and add
	// '\t\t\t\t' to the start of each line
	printTextFile(*difficultyFileName, 0, "\t\t\t\t");

	cout << "\n\n\n\n\n\n\n" << endl;
}

bool Mastermind::checkSaveFile() {
	ifstream saveTextFile(*saveFileDirectory + "mastermindSaveFiles.txt");

	// if save file exits
	if (saveTextFile) {
		saveTextFile.close();
		return true;
	}
	else {
		return false;
	}
}

void Mastermind::displayPlayerUI() {
	printTextFile(*uiFileName, 0, "\t\t\t\t");
}

bool Mastermind::isGameOver() {
	// check if player has won or run out of attempts
	return gameWon || gameBoard->maxAttemptsReached();
}

//=======================================================================================
//                              PRIVATE: MUTATOR METHODS
//=======================================================================================
void Mastermind::setGameAttribtutes() {
	// set player (if not set already)
	if (!playerSelected) {
		setPlayer();
	}

	// set difficulty (if not set already)
	/////////////////////////////////////////////////////////////// TODO: rewrite game difficultyInfo.txt - encoding is broken
	if (changeDifficulty) {
		setDifficulty();
	}

	// set board
	setBoard(*currentGameDifficulty);

	// generate secret code
	generateSecretCode();
}

void Mastermind::setPlayer() {

	system("cls");

	if (!loadGameSelected) {
		string playerName;
		int playerChoice;
		vector<string> nameOptions;

		// add options to nameOptions vector
		nameOptions.push_back("Play as Ellie (recommended)");
		nameOptions.push_back("Play as yourself");

		// get player selection 
		playerChoice = windowsSelect(nameOptions, 2, "text/wouldYouLikeTo.txt");

		// if player chooses to choose new name
		if (playerChoice == 2) {
			system("cls");

			// print screen title
			printTextFile("text/enterYourName.txt");

			///////////////////////////////////////////////////////////////////////// TODO: ask player for name
			//playerName = player.askForString("\n\n\n\n\t\t\t\t\t\t\tName: ");

			// give feedback
			cout << "\n\n\n\n\t\t\t\t\t     Your name has been set to: " << playerName << "\n\n\n\n\n\n" << endl;

			// set player name
			player = new CustomPlayer(playerName);

			// wait for player to continue
			system("pause");
		}
		else {
			player = new Ellie();
		}

		*playerSelected = true;
	}
}

void Mastermind::setBoard(int difficulty) {
	// set game board type
	switch (difficulty)
	{
	case 1:
		gameBoard = new Normal();
		break;
	case 2:
		gameBoard = new Hard();
		break;
	case 3:
		gameBoard = new Survivor();
		break;
	case 4:
		gameBoard = new Grounded();
		break;
	}
}

void Mastermind::setDifficulty() {
	vector<string> difficulties;
	bool difficultySelected = false;
	int difficulty = 1;

	// add options to difficulties vector
	difficulties.push_back("Normal");
	difficulties.push_back("Hard");
	difficulties.push_back("Survivor");
	difficulties.push_back("Grounded");
	difficulties.push_back("Difficulty Information");

	// loop until player selects valid option
	while (!difficultySelected) {
		system("cls");

		// get player selection
		difficulty = windowsSelect(difficulties, 5, *selectFileName, "       ");

// if selection is not 5 ('show game info')
if (difficulty != 5) {
	difficultySelected = true;

	// set game difficulty
	currentGameDifficulty = new int(difficulty);

	// give feedback
	cout << "\n\n\n\n\n\t\t\t\t\t\t    Game is set to: " << difficulties[*currentGameDifficulty - 1] << "\n\n\n\n\n\n" << endl;

	// wait for player to continue
	system("pause");
}
else {
	system("cls");

	// display difficulty info
	displayDifficultyInfo();

	// wait for player to continue
	system("pause");
}
	}
}

void Mastermind::generateSecretCode() {
	switch (*currentGameDifficulty) {
	case 1:
		keycodeCharacters = new string("012345");
		break;
	case 2:
		keycodeCharacters = new string("!@#$%^&*?");
		break;
	case 3:
	case 4:
		keycodeCharacters = new string("abcdefghijklmnopqrstuvwxyz");
	}

	int codeIndex;
	string generatedCode = "";
	for (int i = 0; i < 4; i++) {
		codeIndex = rand() % keycodeCharacters->size();
		generatedCode += keycodeCharacters[codeIndex];
	}

	secretCode = new string(generatedCode);
}

void  Mastermind::playTurn() {
	system("cls");

	// display board
	gameBoard->displayBoard();

	// display player choices
	displayPlayerUI();

	// get player choice

}

string Mastermind::generateHint(string guess) {
	string rightPlace = "";
	string rightCharacter = "";
	string hint;

	// for each part of player guess give hint
	for (int i = 0; i < 4; i++) {
		if (secretCode->find(guess) != string::npos) {
			if (secretCode[i] == to_string(guess[i])) {
				rightPlace += "o";
			}
			else {
				rightCharacter += "?";
			}
		}
	}

	hint = rightPlace + rightCharacter;

	// pad hint to make sure length is 4
	if (hint.length() < 4) {
		for (int j = 0; j <= 4 - hint.length(); j++) {
			hint += " ";
		}
	}

	return hint;
}

void Mastermind::executePlayerTurn(string playerChoice) {
	if (playerChoice.find(" ")) {
		playerChoice.erase(remove(playerChoice.begin(), playerChoice.end(), ' '), playerChoice.end());
	}

	if (playerChoice == "S" || playerChoice == "s") {
		///////////////////////////////////////////////////////// TODO: output player dialogue (add to ellie pulling out torn paper)
		gameBoard->displayPlayerAttempts();
		
	}
	else if (playerChoice == "SA" || playerChoice == "sa" || playerChoice == "Sa" || playerChoice == "sA") {
		saveGame();
		//displayPlayerFeedback("Game saved successfully!");
	}
	else if (playerChoice == "H" || playerChoice == "h") {
	//displayHelpInformation();
	}
	else if (playerChoice == "M" || playerChoice == "") {
		quitGame();
	}
	else if (playerChoice.find(*keycodeElements))
}

string Mastermind::generateSaveData() {
	string saveData;

	//////////////////////////////////////////////////////TODO - get save file name (default is Save File 1 + (date - dd/mm/yyyy))

	// add player attributes
	saveData = player->name() + "\n";
	saveData += to_string(player->gamesWon()) + "\n";
	saveData += to_string(player->gamesLossed()) + "\n";
	saveData += to_string(player->level()) + "\n";

	if (*saveProgressSelected) {
		for (int i = 0; i < 5; i++) {
			if (i == 4) {
				saveData += ".";
			}
			else {
				saveData = ".\n";
			}
		}
	}
	else {
		// add player guesses
		saveData += gameBoard->generateAttemptData();

		// add line break
		saveData += "\n";

		// add code hints
		saveData += gameBoard->generateHintData();

		// add game attributes
		saveData += *secretCode + "\n";
		saveData += to_string(*currentGameDifficulty) + "\n";
		saveData += to_string(gameBoard->getNumAttempts());
	}
	return saveData;
}

void Mastermind::saveGame() {
	ofstream gameSaveFile;
	string dataToWrite;

	// add all other necessary game data
	dataToWrite += generateSaveData();

	// open mastermindSaveFile.txt
	gameSaveFile.open("saveFiles/mastermindSaveFile.txt", ios::app);

	// save game data
	gameSaveFile << dataToWrite;

	// close file
	gameSaveFile.close();
}

void Mastermind::saveProgress() {
	*saveProgressSelected = true;
	saveGame();
	*saveProgressSelected = false;
}

int Mastermind::windowsSelect(vector<string> optionArray, int numOptions, string fileName, string optionsIndent) {
	bool optionSelected = false;
	int optionIndex = 0;

	// loop until selection is made
	while (!optionSelected) {

		// if a title screen is given
		if (fileName != "") {
			printTextFile(fileName);
		}

		// print options
		printVector(optionArray, numOptions, optionIndex, "> ", optionsIndent);

		// get keyboard press
		char key = _getch();
		system("cls");

		// if arrow key is pressed
		if (key == -32) {
			switch (-32 + _getch()) {
			case KEY_UP:
				// move selection up
				if (optionIndex != 0) {
					optionIndex -= 1;
				}
				// move selection to bottom
				else {
					optionIndex = numOptions - 1;
				}
				break;
			case KEY_DOWN:
				// move selection down
				if (optionIndex != numOptions - 1) {
					optionIndex += 1;
				}
				//move selection to top
				else {
					optionIndex = 0;
				}
				break;
			}
		}
		// selection is made
		else if (key == KEY_ENTER) {
			optionSelected = true;
			printTextFile(fileName);
			printVector(optionArray, numOptions, optionIndex, "> ", optionsIndent);
		}
	}

	return optionIndex + 1;
}

void Mastermind::printTextFile(string fileName, int delay, string indent) {
	string textFileData;
	ifstream textFile;

	// open text file
	textFile.open(fileName);

	// print out each line
	while (getline(textFile, textFileData)) {
		cout << indent << textFileData << endl;
		Sleep(delay);
	}

	textFile.close();
}

void Mastermind::printVector(vector<string> vectorToPrint, int numItems, int insertIndex, string insertElement, string elementIndent) {
	// if extra element given at non defaul (-1) index
	if (insertIndex != -1) {
		for (int i = 0; i < numItems; i++) {
			// add insert element at given index
			if (i == insertIndex) {
				// add brackets to highlight element
				cout << "\t\t\t\t\t\t" << elementIndent << insertElement << "[" << vectorToPrint[i] << "]\n" << endl;
			}
			else {
				// add whitespace to align vector elements
				cout << "\t\t\t\t\t\t" << elementIndent << "   " << vectorToPrint[i] << "\n" << endl;
			}
		}
	}
	// print vector
	else {
		for (int i = 0; i < numItems; i++) {
			cout << vectorToPrint[i] << endl;
		}
	}
}

