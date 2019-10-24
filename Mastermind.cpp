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
	delete saveFileName;
	delete loadGameSelected;
	delete gameWon;
	delete keycodeElements;
	delete currentGameDifficulty;
	delete playerSelected;
	delete changeDifficulty;
	delete saveProgressSelected;
}

//=======================================================================================
//                              PUBLIC: ACCESSOR METHODS
//=======================================================================================
void Mastermind::startGame() {
	// clear screen
	system("cls");

	// display game title
	displayTitleScreen();

	// display loading screen
	displayLoadingScreen();

	// display main menu and start game (based on player choice)////////////////TODO: add choice to save game (allows to save progress without having to be in game)
	int number = mainMenuChoice();

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
	ifstream saveTextFile(*saveFileName);

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

bool Mastermind::checkAttemptValidity(string guess) {
	for (int i = 0; i < guess.size(); i++) {
		if (gameBoard->validBoardSymbols().find(guess[i]) == string::npos) {
			return false;
		}
	}
	
	return true;
}

void Mastermind::displayRelevantDialogue(string hint, string guess) {
	string playerDialogue;
	string allGuesses = gameBoard->generateAttemptData();
	string previousGuesses = allGuesses.substr(0, allGuesses.size() - 4);

	int numberCorrect = 0;
	for (int i = 0; i < 4; i++) {
		if (hint[i] == 'o') {
			numberCorrect += 1;
		}
	}
	
	if (!gameBoard->maxAttemptsReached()) {
		// if no characters in hint are found in secret code
		if (hint == "    ") {
			playerDialogue = player->getDialogue(3);
		}

		// if player has already tried guess before
		else if (previousGuesses.find(guess) != string::npos) {
			playerDialogue = player->getDialogue(5);
		}

		// if player has only one character to go
		else if (numberCorrect == 3) {
			playerDialogue = player->getDialogue(7);
		}

		// if player has only two turns left
		if (gameBoard->getMaxAttempts() - gameBoard->getNumAttempts() == 2) {
			playerDialogue += "\n" + player->getDialogue(8);
		}
	}
	// last attempt was made and code has not been broken
	else {
		playerDialogue = "";
	}

	if (playerDialogue != "") {
		// clear screen
		system("cls");

		// display the board
		gameBoard->displayBoard();

		// display player dialogue
		cout << "\t\t\t" << playerDialogue << "\n\n\n\n\n\n\n\n\n\n\n" << endl;

		// wait for player to continue
		system("pause");
	}

}

string Mastermind::askForString(string prompt) {
	string userInput = "";

	//print question and store cin in userInput;
	while (userInput == "") {
		cout << prompt;
		cin.clear();
		getline(cin, userInput);
	}

	return userInput;
}

string Mastermind::getLineFromFile(string fileName, int lineNumber) {
	ifstream file(fileName);
	string fileData;
	int currentLine = 0;

	while (getline(file, fileData)) {
		if (currentLine == lineNumber) {
			return fileData;
		}
		currentLine += 1;
	}
	
	throw out_of_range("lineNumber is greater than the length of this file.");
}

void Mastermind::newGame() {
	// setup game components (player, difficulty, board and secret code)
	setGameAttribtutes();

	// run game with about attributes
	runGame();
}

void Mastermind::loadGame(int saveFile) {
	ifstream savesTextFile(*saveFileName);
	string saveData;
	bool allDataLoaded = false;
	int lineStart = saveFile * 10;
	int currentLine = 0;
	int saveLine = 1;

	while (getline(savesTextFile, saveData) && !allDataLoaded) {
		if (currentLine >= lineStart + 1) {
			switch (saveLine) {
			case 1:
				if (saveData == "Ellie") {
					player = new Ellie();
				}
				else {
					player = new CustomPlayer(saveData);
				}
				break;
			case 2:
				for (int i = 0; i <= stoi(saveData); i++) {
					player->addGameWon();
				}
				break;
			case 3:
				for (int j = 0; j <= stoi(saveData); j++) {
					player->addGameLossed();
				}
				break;
			case 4:
				player->setPlayerLevel(stoi(saveData));
				break;
			case 5:
				if (saveData == ".") {
					allDataLoaded = true;
				}
				else {
					setBoard(stoi(saveData));
				}
				break;
			case 6:
				gameBoard->loadGuesses(saveData);
				break;
			case 7:
				gameBoard->loadHints(saveData);
				break;
			case 8:
				*secretCode = saveData;
				break;
			case 9:
				for (int k = 0; k <= stoi(saveData); k++) {
					gameBoard->addAttempt();
				}
				break;
			}
		}

		currentLine += 1;
	}

	runGame();
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
	int codeIndex;
	string generatedCode = "";

	if (*currentGameDifficulty != 3) {
		for (int i = 0; i < 4; i++) {
			codeIndex = rand() % gameBoard->validBoardSymbols().size();
			generatedCode += gameBoard->validBoardSymbols()[codeIndex];
		}
	}
	else {
		codeIndex = rand() % *wordLibrarySize;
		generatedCode = getLineFromFile(*wordLibraryName, codeIndex);
	}

	secretCode = new string(generatedCode);
}

void  Mastermind::playTurn() {
	system("cls");

	// display board
	gameBoard->displayBoard();

	// display player choices
	displayPlayerUI();

	// get player choice and execute turn
	executePlayerTurn(askForString("\t\t\t\t\t\t\t       "));
}

string Mastermind::generateHint(string guess) {
	string rightPlace = "";
	string rightCharacter = "";
	string hint;

	// for each part of player guess give hint
	for (int i = 0; i < 4; i++) {
		if (checkAttemptValidity(guess)) {
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
	string guess = "";
	string hint = "";
	if (playerChoice.find(" ") != string::npos) {
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
	else if (playerChoice == "M" || playerChoice == "m") {
		//quitGame();
	}
	else if (checkAttemptValidity(playerChoice)) {
		guess = playerChoice;
		hint = generateHint(guess);
		gameBoard->addTurn(guess, hint);
	}
	else {
		///////////////////////////////////////////////////////////// TODO: format output
		cout << player->getDialogue(6, *keycodeElements) << endl;
	}

	if (hint != "") {
		displayRelevantDialogue(hint, guess);
	}
}

string Mastermind::generateSaveData() {
	string saveData;

	//////////////////////////////////////////////////////TODO - get save file name (default is Save File 1 + (date - dd/mm/yyyy))

	// add player attributes
	saveData = player->name() + "\n";
	saveData += to_string(player->gamesWon()) + "\n";
	saveData += to_string(player->gamesLossed()) + "\n";
	saveData += to_string(player->level()) + "\n";

	// add board type info (difficulty determines board type)
	saveData += to_string(*currentGameDifficulty) + "\n";

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
		saveData += to_string(gameBoard->getNumAttempts());
	}
	return saveData;
}

void Mastermind::saveGame() {
	ofstream gameSaveFile;
	string dataToWrite;

	/////////////////////////////////////////////////////////////// TODO: get save file name from player or set default

	// add all other necessary game data
	dataToWrite += generateSaveData();

	// open mastermindSaveFile.txt
	gameSaveFile.open(*saveFileName, ios::app);

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

