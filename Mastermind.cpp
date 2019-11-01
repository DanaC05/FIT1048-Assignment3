/**************************************************
Project: Mastermind: The Last Of Us Edition
Assignment Num: 3
Author: Dana Casella
Purpose: Mastermind Class File

This class runs the game of mastermind. It 
controls all game components.
**************************************************/
#include "Mastermind.h"

//=======================================================================================
//                                 PUBLIC: CONSTRUCTORS
//======================================================================================
Mastermind::Mastermind() {
	// seed randoms
	srand(unsigned(time(NULL)));
	
	// initiate variables
	gameScenario = new Scenario();
	gameWon = new bool(false);
	gameRunning = new bool(true);
	playerQuitGame = new bool(false);
	invalidInput = new string("");
	keycodeElements = new string("");
	secretCode = new string("");
	showDialogue = new bool(true);
}

Mastermind::~Mastermind() {
	delete player;
	delete gameBoard;
	delete gameScenario;
	delete uiFileName;
	delete loadingFileName;
	delete titleFileName;
	delete creditsFileName;
	delete introFileName;
	delete playerFileName;
	delete difficultyFileName;
	delete helpFileName;
	delete enterFileName;
	delete selectFileName;
	delete wouldFileName;
	delete continueFileName;
	delete loadFileName;
	delete saveGameFileName;
	delete quitGameFileName;
	delete congratsFileName;
	delete playerSavesFileName;
	delete keycodeElements;
	delete secretCode;
	delete invalidInput;
	delete gameWon;
	delete gameRunning;
	delete playerQuitGame;
	delete showDialogue;
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

	// display main menu 
	mainMenu();
}

//=======================================================================================
//                              PRIVATE: ACCESSOR METHODS
//=======================================================================================
void Mastermind::mainMenu() {
	// get player choice
	int menuChoice = mainMenuChoice();

	// ask player to start new game, load game (if data), show game credits or quit game()
	switch (menuChoice) {
		// player selects new game
	case 1:
		newGame();
		break;
		// player selects load game or show credits
	case 2:
		if (checkSaveFile()) {
			displaySaveFiles();
			break;
		}
		// player opts to show credits
	case 3:
		// clear screen
		system("cls");

		// show game credits
		rollCredits();

		// return to the menu
		mainMenu();
	}

	// if menuChoice == 4 player has selected to quit game
}

void Mastermind::newGame() {
	// give character information
	displayCharacterInformation();

	// setup game components (player, difficulty, board and secret code, etc)
	setGameAttribtutes();

	// run game with about attributes
	runGame();
}

void Mastermind::loadGame(int saveFile) {
	ifstream savesTextFile(*playerSavesFileName);
	string saveData;
	vector<string> loadOptions;
	bool allDataLoaded = false;
	int lineStart = (saveFile - 1) * 9;
	int currentLine = 0;
	int saveLine = 1;

	// extract data from save text file and set relevant game attributes (stop once all neccessary data has been collected)
	while (getline(savesTextFile, saveData) && !allDataLoaded) {
		// if at the correct line for the selected save file
		if (currentLine >= lineStart + 1) {
			switch (saveLine) {
				// set player
			case 1:
				if (saveData == "Ellie") {
					player = new Ellie();
				}
				else {
					player = new CustomPlayer(saveData);
				}
				saveLine += 1;
				break;
				// set number of games the player has won
			case 2:
				for (int i = 0; i < stoi(saveData); i++) {
					player->addGameWon();
				}
				saveLine += 1;
				break;
				// set scenario
			case 3:
				gameScenario = new Scenario();
				gameScenario->loadScenario(stoi(saveData));
				saveLine += 1;
				break;
				// set player level and game board
			case 4:
				setBoard(stoi(saveData));
				player->setPlayerLevel(stoi(saveData));
				saveLine += 1;
				break;
				// set attempts
			case 5:
				gameBoard->loadGuesses(saveData);
				saveLine += 1;
				break;
				// set hints
			case 6:
				gameBoard->loadHints(saveData);
				saveLine += 1;
				break;
				// set secret code
			case 7:
				secretCode = new string(saveData);
				saveLine += 1;
				break;
				// set number of attempts and indicate all data has been collected
			case 8:
				for (int k = 0; k < stoi(saveData); k++) {
					gameBoard->addAttempt();
				}
				allDataLoaded = true;
				break;
			}
		}

		currentLine += 1;
	}

	// reset game booleans (for when player selects load game after quiting to menu)
	*gameWon = false;
	*playerQuitGame = false;

	runGame();
}

void Mastermind::runGame() {
	bool gameRunning = true;

	// display scenraio info
	displayScenarioInfo();

	// display game start message
	displayGameStartMessage();

	// run game until player wins, looses or quits
	while (gameRunning) {
		// play turn
		playTurn();

		// check for game over
		gameRunning = !isGameOver();
	}

	if (*gameWon) {
		// show game won ending
		gameOver(true);
	}
	else if (gameBoard->maxAttemptsReached()) {
		// show game lossed ending
		gameOver(false);
	}
}

void Mastermind::saveGame() {
	ofstream gameSaveFile;
	string dataToWrite;

	// add all necessary game data
	dataToWrite = generateSaveData();

	// open mastermindSaveFile.txt
	gameSaveFile.open(*playerSavesFileName, ios::app);

	// save game data
	gameSaveFile << dataToWrite;

	// clear screen
	system("cls");

	// close file
	gameSaveFile.close();
}

void Mastermind::quitGame() {
	int quitChoice;
	vector<string> quitOptions;

	// add options to vector
	quitOptions.push_back("Main Menu");
	quitOptions.push_back("Back to game");

	// clear screen
	system("cls");

	// get choice (player confirmation to return to the menu)
	quitChoice = windowsSelect(quitOptions, 2, *quitGameFileName, "\t\t\t\t    ");

	// player chooses to quit to menu
	if (quitChoice == 1) {
		*playerQuitGame = true;
		mainMenu();
	}

	// player chooses to return to game
	else {
		*playerQuitGame = false;
	}
}

void Mastermind::continueGame() {
	vector<string> continueOptions;
	int continueChoice;

	// clear screen
	system("cls");

	// add options
	continueOptions.push_back("Continue");
	continueOptions.push_back("Main Menu");

	// display continue title and get player choice
	continueChoice = windowsSelect(continueOptions, 2, *continueFileName, "\t\t\t\t       ");

	// if player chooses to contine reset elements and start the next game
	if (continueChoice == 1) {
		resetGameAssets();
		runGame();
	}
	else {
		// set booleans so program will end
		*playerQuitGame = true;
		*gameWon = false;

		// go to the main menu
		mainMenu();
	}
}

void Mastermind::gameOver(bool playerWon) {
	string endMessage;

	// disable player dialogue
	*showDialogue = false;

	if (playerWon) {
		// show door/safe open
		gameBoard->endAnimation(gameScenario->getItemTextFile());

		// calculate player score
		int playerScore = gameBoard->getMaxAttempts() - gameBoard->getNumAttempts();
		player->increaseScore(playerScore);

		// display end character dialogue depending on score
		if (player->score() == 0 || gameScenario->getScenario() == 2) {
			cout << player->getDialogue(10, gameScenario->getItem()) << endl;
		}
		else if (player->score() == 1) {
			cout << player->getDialogue(11) << endl;
		}
		else {
			cout << player->getDialogue(12) << endl;
		}

		// set end message
		endMessage = gameScenario->getGameWonMessage();
	}
	else {
		// display door/safe lock
		gameBoard->endAnimation();

		// player end dialogue
		cout << player->getDialogue(9);

		// set end message
		endMessage = gameScenario->getGameOverMessage();
	}

	cout << "\n\n\n\n\n\n\n\n" << endl;

	// wait for player to continue
	system("pause");

	// clear screen
	system("cls");

	// give end context
	cout << endMessage << endl;
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;

	// wait for player to continue
	system("pause");

	// ask player if the would like to continue playing and act accordingly
	if (playerWon && gameScenario->getScenario() == 3) {
		gameComplete();
	}
	else {
		continueGame();
	}
}

void Mastermind::gameComplete() {
	// clear screen
	system("cls");

	// show credits
	rollCredits();

	// clear screen
	system("cls");

	// show congrats screen
	printTextFile(*congratsFileName);

	// wait for player to continue
	system("pause");

	// return to the menu
	mainMenu();
}

void Mastermind::rollCredits() {
	int currentLine = 0;
	int startIndex = 0;
	int endIndex = 57;


	// print credits.txt to roll up the screen
	for (int i = 0; i < 145; i++) {
		ifstream credits(*creditsFileName);
		string creditsData;
		currentLine = 0;

		// prints the text file one page/terminal window size at a time moving down by one line
		while (getline(credits, creditsData)) {
			if (startIndex < currentLine && currentLine < endIndex) {
				cout << creditsData << endl;
			}
			currentLine += 1;
		}

		// close text file
		credits.close();

		// wait for 150ms
		Sleep(150);

		// clear screen
		system("cls");

		// move 'down' in text file
		startIndex += 1;
		endIndex += 1;
	}

	// wait for 200ms
	Sleep(200);
}

int Mastermind::mainMenuChoice() {
	int playerChoice;
	vector<string> gameStart;

	// add options to gamestart vector
	gameStart.push_back("New Game");
	if (checkSaveFile()) {
		gameStart.push_back("Load Game");
	}
	gameStart.push_back("Credits");
	gameStart.push_back("Quit");

	system("cls");

	playerChoice = windowsSelect(gameStart, gameStart.size(), *titleFileName, "\t\t\t\t\t");

	// make sure 'quit' choice is always 4
	if (playerChoice == gameStart.size()) {
		playerChoice = 4;
	}

	return playerChoice;
}

bool Mastermind::isGameOver() {
	// check if player has won, run out of attempts or quit to the menu
	return *playerQuitGame || *gameWon || gameBoard->maxAttemptsReached();
}

bool Mastermind::checkAttemptValidity(string guess) {

	// check if any character in guess is not in valid characters or the keycode
	for (int i = 0; i < guess.size(); i++) {
		if (gameBoard->validBoardCharacters().find(guess[i]) == string::npos) {
			return false;
		}
	}
	return true;
}

bool Mastermind::checkSaveFile() {
	ifstream saveTextFile(*playerSavesFileName);

	// if save file exits
	if (saveTextFile) {
		saveTextFile.close();
		return true;
	}
	else {
		return false;
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
	int fileLines = getLineCount(fileName);
	int currentLine = 0;

	// make sure line selected is within the scope of the file
	if (lineNumber < fileLines) {
		// get selected line
		while (getline(file, fileData)) {
			if (currentLine == lineNumber) {
				file.close();
				return fileData;
			}
			currentLine += 1;
		}
	}
	else {
		file.close();
		throw out_of_range("lineNumber is greater than the length of this file.");
	}

	return "";
}

int Mastermind::getLineCount(string fileName) {
	ifstream file(fileName);
	string fileData;
	int lineCount = 0;

	// count each line in file
	while (getline(file, fileData)) {
		lineCount += 1;
	}

	file.close();
	return lineCount;
}

string Mastermind::getCurrentDate() {
	tm timeStruct;
	time_t currentTime = time(0);

	// get current date in the form (dd-mm-yyyy)
	localtime_s(&timeStruct, &currentTime);
	string currentDate = to_string((timeStruct.tm_mday)) + "-" + to_string((timeStruct.tm_mon + 1)) + "-" + to_string((timeStruct.tm_year + 1900));

	return currentDate;
}

void Mastermind::displayLoadingScreen() {
	system("cls");
	string loading = "\t\t\t\t\t\t\t\t\t\t\t    Loading.";

	// loop through 'loading...' three times
	for (int i = 0; i < 9; i++) {
		string fireflyFileData = "";
		ifstream fireflyFile;
		fireflyFile.open(*loadingFileName);
		int lineNumber = 1;

		while (getline(fireflyFile, fireflyFileData)) {
			// print loading string
			if (lineNumber == 36) {
				cout << loading << endl;
			}
			else {
				cout << fireflyFileData << endl;
			}
			lineNumber += 1;
		}

		cout << "\n" << endl;

		// wait 500ms and clear the screen
		Sleep(500);
		system("cls");

		// reset loading string every third time through loop
		if ((i + 1) % 3 == 0) {
			loading = "\t\t\t\t\t\t\t\t\t\t\t    Loading.";
		}
		// add '.' to loading string
		else {
			loading += ".";
		}
	}
}

void Mastermind::displayTitleScreen() {
	// clear screen
	system("cls");

	cout << "\n\n\n\n\n\n\n\n\n" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t     MasterMind Presents..." << endl;

	// print text file (game title) with a delay of 300ms between each line print
	printTextFile(*titleFileName, 300);
}



void Mastermind::displaySaveFiles() {
	vector<string> saveFileOptions;
	ifstream saveFile(*playerSavesFileName);
	string saveFileData;
	int saveFileLine = 0;
	int saveFileCount = 1;
	string playerDetails;
	int loadChoice;
	int spaceNumber;
	string spacing = "";

	// print save file data (save name, player name, player level)
	while (getline(saveFile, saveFileData)) {
		if (saveFileLine == 9) {
			saveFileLine = 0;
			saveFileCount += 1;
		}
		switch (saveFileLine) {
		// get save file name
		case 0:
			saveFileOptions.push_back(saveFileData);
			break;
		// get player name
		case 1:
			// format so that save files line up when displayed
			spaceNumber = 19 - saveFileData.size();
			for (int i = 0; i < spaceNumber; i++) {
				spacing += " ";
			}

			playerDetails = saveFileData + spacing;

			// reset spacing
			spacing = "";
			break;
		// get player level
		case 4:
			playerDetails += "Level: " + saveFileData;
			saveFileOptions.push_back(playerDetails);
			break;
		}
		saveFileLine += 1;
	}

	// allow player the choice to return to the main menu
	saveFileOptions.push_back("Back");
	saveFileOptions.push_back("");
	saveFileCount += 1;
	
	loadChoice = windowsSelect(saveFileOptions, saveFileCount*2, *loadFileName, "\t\t\t\t", true);

	// return to main menu
	if ((loadChoice + 1)/2 == (saveFileCount)) {
		mainMenu();
	}
	// load selected save file
	else {
		loadGame((loadChoice + 1)/2);
	}
}

void Mastermind::displayCharacterInformation() {
	// clear screen
	system("cls");

	// display text file
	printTextFile(*playerFileName);

	// wait for player to continue
	system("pause");
}

void Mastermind::displayScenarioInfo() {
	// clear screen
	system("cls");

	// print scenario text file
	printTextFile(gameScenario->getScenarioInfo());

	// wait for player to continue
	system("pause");
}

void Mastermind::displayGameStartMessage() {
	// clear screen
	system("cls");

	// give context/scenario
	cout << gameScenario->getStartMessage() << endl;

	// display player dialogue
	cout << "\n\n\n\n\n\n\t\t\t\t\t\t" << player->getDialogue(1, to_string(gameBoard->getMaxAttempts())) << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;

	// wait for player to continue
	system("pause");
}

void Mastermind::displayHelpInformation() {
	// clear screen
	system("cls");

	// display player dialogue
	cout << "\n\n\n\n" << player->getDialogue(14) << "\n\n\n" << endl;

	// display help info
	printTextFile(*helpFileName);

	// wait for player to continue
	cout << "\n\n\n\n\n" << endl;
	system("pause");
}

void Mastermind::displayRelevantDialogue(string hint, string guess) {
	string playerDialogue = "";
	string allGuesses = gameBoard->generateAttemptData();
	string previousGuesses = allGuesses.substr(0, allGuesses.size() - 4);
	int numberCorrect = 0;
	
	// if player has entered an invalid option
	if (guess == "" && hint == "") {
		if (*invalidInput == "short") {
			playerDialogue = player->getDialogue(13);
		}
		else if (*invalidInput == "invalid") {
			playerDialogue = player->getDialogue(6, gameBoard->validSymbolGroup());
		}
	}
	else if (!gameBoard->maxAttemptsReached() && !*gameWon) {
		for (int i = 0; i < 4; i++) {
			if (hint[i] == 'o') {
				numberCorrect += 1;
			}
		}

		// if player has entered too few characters (that don't match with any menu options)
		if (*invalidInput == "short") {
			playerDialogue = player->getDialogue(13);
		}

		// if player has entered characters not in valid code symbols (that also don't match menu options)
		else if (*invalidInput == "invalid") {
			playerDialogue = player->getDialogue(6, gameBoard->validBoardCharacters());
		}

		else {
			// gives information about feedback symbols on first (non empty) hint (this only occurs once)
			if (gameBoard->lastHint() != "    ") {
				playerDialogue = player->getDialogue(4);
			}

			// make sure to not overwrite dialogue when symbols feedback is displayed
			if (playerDialogue == "") {
				// if player has already tried guess before
				if (previousGuesses.find(guess) != string::npos) {
					playerDialogue = player->getDialogue(5);
				}
				// if no characters in hint are found in secret code
				else if (hint == "    ") {
					playerDialogue = player->getDialogue(3);
				}

				// if player has only one character to go (three already in correct place)
				else if (numberCorrect == 3) {
					playerDialogue = player->getDialogue(7);
				}
			}
		}
		// if player has only two turns left
		if (gameBoard->getMaxAttempts() - gameBoard->getNumAttempts() == 2) {
			playerDialogue += player->getDialogue(8, gameScenario->getEnemy());
		}
	}

	if (playerDialogue != "") {
		// display player dialogue
		cout << playerDialogue << endl;
	}
}

//=======================================================================================
//                              PRIVATE: MUTATOR METHODS
//=======================================================================================
void Mastermind::setGameAttribtutes() {
	// reset quit boolean (for when player quits to menu and selects to start a new game)
	*playerQuitGame = false;

	// set player
	setPlayer();

	// set difficulty
	setDifficulty();

	// set scenario
	gameScenario->setScenario();
	
	// set board
	setBoard(player->level());

	// generate secret code
	generateSecretCode();
}

void Mastermind::setPlayer() {
	string playerName;
	int playerChoice;
	vector<string> nameOptions;
	bool invalidPlayerName = true;

    // clear screen
	system("cls");

	// add options to nameOptions vector
	nameOptions.push_back("Play as Ellie (recommended)");
	nameOptions.push_back("Play as yourself");

	// get player selection 
	playerChoice = windowsSelect(nameOptions, 2, "text/wouldYouLikeTo.txt", "\t\t\t\t");

	// if player chooses to choose new name
	if (playerChoice == 2) {

		while (invalidPlayerName) {
			system("cls");

			// print screen title
			printTextFile("text/enterYourName.txt");

			// ask player for name
			playerName = askForString("\n\n\n\n\t\t\t\t\t\t\t\t\t\t       Name: ");

			// make sure player name isn't too long (for save file formatting if player saves game)
			if (playerName.size() > 15) {
				cout << "\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tYour name is too long! Please enter a name of 15 characters or less.\n\n\n\n\n\n" << endl;
				system("pause");
			}
			else {
				invalidPlayerName = false;
			}
		}

		// give feedback
		cout << "\n\n\n\n\t\t\t\t\t\t\t\t\t     Your name has been set to: " << playerName << "\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
		
		// set player name
		player = new CustomPlayer(playerName);

		// wait for player to continue
		system("pause");
	}
	else {
		player = new Ellie();
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
		difficulty = windowsSelect(difficulties, 5, *selectFileName, "\t\t\t\t\t");

		// if selection is not 5 ('show game info')
		if (difficulty != 5) {
			difficultySelected = true;

			// set player level
			player->setPlayerLevel(difficulty);
			
			// display page title
			printTextFile(*selectFileName);

			// give feedback
			cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t     Game is set to: " << difficulties[difficulty - 1] << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;

			// wait for player to continue
			system("pause");
		}
		else {
			system("cls");

			// display difficulty info
			printTextFile(*difficultyFileName);

			// wait for player to continue
			system("pause");
		}
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

void Mastermind::generateSecretCode() {
	int codeIndex;
	string generatedCode = "";

	// select 4 random elements from keycode characters
	if (player->level() != 3) {
		for (int i = 0; i < 4; i++) {
			codeIndex = rand() % gameBoard->validBoardCharacters().size();
			generatedCode += gameBoard->validBoardCharacters()[codeIndex];
		}
	}
	// select a random word (line) from word library text file (level three only)
	else {
		codeIndex = rand() % gameBoard->wordLibrarySize();
		generatedCode = getLineFromFile(gameBoard->wordLibraryName(), codeIndex);
	}

	*secretCode = generatedCode;
}

void  Mastermind::playTurn() {
	system("cls");

	// display board (will flash when code is entered and not when a menu option is selected)
	gameBoard->displayBoard(*showDialogue);

	// display dialogue
	if (*showDialogue) {
		if (gameBoard->getNumAttempts() > 0) {
			displayRelevantDialogue(gameBoard->lastHint(), gameBoard->lastGuess());
		}
		else {
			displayRelevantDialogue("", "");
		}
	}
	cout << "\n" << *secretCode << "\n" << endl; ///////////////////////////// to be removed on relese - testing purposes only

	// display player UI
	printTextFile(*uiFileName);

	// get player choice and execute turn
	executePlayerTurn(askForString("\t\t\t\t\t\t\t\t\t\t\t     "));
}

void Mastermind::executePlayerTurn(string playerChoice) {
	string guess = "";
	string hint = "";
	
	// reset invalidInput and showDialogue
	*invalidInput = "";
	*showDialogue = true;

	// remove spaces (if any) in player input
	if (playerChoice.find(" ") != string::npos) {
		playerChoice.erase(remove(playerChoice.begin(), playerChoice.end(), ' '), playerChoice.end());
	}

	// if player chooses 'show attempts'
	if (playerChoice == "S" || playerChoice == "s") {
		// disable dialogue
		*showDialogue = false;

		// clear screen
		system("cls");

		// give context
		cout << "\n\n\n\n\t\t\t\t\t\t\t\t\t  [You pull a torn piece of paper from your pocket]\n\n\n\n\n\n" << endl;

		// display attempts
		gameBoard->displayPlayerAttempts();

		// display dialogue if no attempts have been made yet
		if (gameBoard->getNumAttempts() == 0) {
			cout << "\n\n\n\n\t\t\t\t\t\t\t\t\t  " << player->getDialogue(2, gameScenario->getObjective()) << "\n\n\n\n\n\n\n\n\n\n" << endl;
		}

		// wait for player to continue
		system("pause");	
	}

	// player chooses 'save game'
	else if (playerChoice == "SA" || playerChoice == "sa" || playerChoice == "Sa" || playerChoice == "sA") {
		// disable dialogue
		*showDialogue = false;

		// save current game data
		saveGame();
	}

	// if player chooses 'help'
	else if (playerChoice == "H" || playerChoice == "h") {
		// disable dialogue
		*showDialogue = false;

		// display text file with help info
		displayHelpInformation();
	}

	// if player chooses 'main menu'
	else if (playerChoice == "M" || playerChoice == "m") {
		// disable dialogue
		*showDialogue = false;

		// quit game (player will be asked to confirm)
		quitGame();
	}

	// if input conatins valid keycode characters (no menu option was selected)
	else if (checkAttemptValidity(playerChoice)) {
		// if player has entered valid code guess
		if (playerChoice.size() == 4) {
			guess = playerChoice;
			hint = generateHint(guess);
			gameBoard->addTurn(guess, hint);
		}
		// player has entered too few characters
		else {
			*invalidInput = "short";
		}
	}

	// player has not entered anything valid
	else {
		*invalidInput = "invalid";
	}
}

string Mastermind::generateHint(string guess) {
	string rightPlace = "";
	string rightCharacter = "";
	string hint;
	string codeCopy = *secretCode;
	string guessCopy = guess;

	// check for correct character in correct place
	for (int i = 0; i < 4; i++) {
		if (checkAttemptValidity(guess)) {
			if (codeCopy[i] == guessCopy[i]) {
				rightPlace += "o";
				codeCopy[i] = ' ';
				guessCopy[i] = ' ';
			}
		}
	}

	// check if remaining characters in guess are also in the keycode
	for (int j = 0; j < 4; j++) {
		if (guessCopy[j] != ' ' && codeCopy.find(guessCopy[j]) != string::npos) {
			rightCharacter += "?";
			codeCopy[codeCopy.find(guessCopy[j])] = ' ';
		}
	}

	// if all charaters are correct and in the right position
	if (rightPlace == "oooo") {
		*gameWon = true;
		hint = "won";
	}
	else {
		hint = rightPlace + rightCharacter;

		// pad hint to make sure length is 4 (for printing on board)
		if (hint.size() < 4) {
			int length = 4 - hint.size();

			for (int j = 0; j < length; j++) {
				hint += " ";
			}
		}
	}

	return hint;
}

string Mastermind::generateSaveData() {
	string saveData = "";
	string playerSaveName = "";
	string errorMessage = "";
	string nameCopy;
	bool invalidNameSelected = true;

	// make sure save name is valid
	while (invalidNameSelected) {
		// clear screen
		system("cls");

		// print save title
		printTextFile(*saveGameFileName);

		// ask player for save file name
		playerSaveName = askForString("\n\n\t\t\t\t\t\t\t\t\t    Save File Name: ");

		// make sure save name is no more than 15 characters
		if (playerSaveName.size() > 15) {
			// give error feedback
			cout << "\n\n\n\n\n\n\n\t\t\t\t\t\t\tSave file name is too long! Please enter a name of less than 16 characters.\n\n\n\n\n\n\n\n\n\n\n\n" << endl;

			// wait for player to continue
			system("pause");
		}
		// player has entered a valid name
		else {
			invalidNameSelected = false;
		}
	}

	// check if player has opted to have default save name (just entered spaces)
	nameCopy = playerSaveName;
	nameCopy.erase(remove(nameCopy.begin(), nameCopy.end(), ' '), nameCopy.end());
	if (nameCopy == "") {
		int numSaveFiles = getLineCount(*playerSavesFileName) / 9;
		playerSaveName = "SAVE FILE " + to_string(numSaveFiles + 1);
	}

	// format name with spacing to save to text file
	int nameLength = playerSaveName.size();
	int spacingNumber = 19 - nameLength;
	saveData += "\n" + playerSaveName;
	string spacing(spacingNumber, ' ');

	// add current date
	saveData += spacing + getCurrentDate() + "\n";

	// add player attributes
	saveData += player->name() + "\n";
	saveData += to_string(player->gamesWon()) + "\n";
	saveData += to_string(gameScenario->getScenario()) + "\n";
	saveData += to_string(player->level()) + "\n";
		
	// add player guesses
	saveData += gameBoard->generateAttemptData() + "\n";

	// add code hints
	saveData += gameBoard->generateHintData() + "\n";

	// add game attributes
	saveData += *secretCode + "\n";
	saveData += to_string(gameBoard->getNumAttempts());

	// clear screen
	system("cls");

	// give feedback
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t  Game saved successfully!" << endl;
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;

	// wait for player to continue
	system("pause");


	return saveData;
}

void Mastermind::resetGameAssets() {
	// reset game boolean variables
	*gameWon = false;
	*playerQuitGame = false;

	// if player has won 5 games promote player to the next level
	if (player->gamesWon() == 5) {
		// if player is up to the final level set to the last scenario
		if (player->level() + 1 == 4) {
			gameScenario->lastScenario();
		}
		else {
			gameScenario->setScenario();
		}

		// set board, player level and reset player stats
		setBoard(player->level() + 1);
		player->resetGameStats();
		player->promotePlayer();
	}
	// if player has initially selected to play grounded level, set to last scenario
	else if (player->level() == 4 && gameScenario->getScenario() == 1) {
		gameScenario->lastScenario();
		setBoard(player->level());
	}
	// otherwise set attributes
	else {
		// set board
		setBoard(player->level());

		// add game won to player
		player->addGameWon();

		// set random scenario
		gameScenario->setScenario();
	}
	
	// generate new keycode
	*keycodeElements = gameBoard->validBoardCharacters();
	generateSecretCode();
}

int Mastermind::windowsSelect(vector<string> optionArray, int numOptions, string fileName, string optionsIndent, bool extraItemToPrint) {
	bool optionSelected = false;
	int optionIndex = 0;

	// loop until selection is made
	while (!optionSelected) {

		// if a title screen is given
		if (fileName != "") {
			printTextFile(fileName);
		}

		// print options
		if (extraItemToPrint) {
			printVector(optionArray, numOptions, optionIndex, "> ", optionsIndent, true);

		}
		else {
			printVector(optionArray, numOptions, optionIndex, "> ", optionsIndent);
		}

		// get keyboard press
		char key = _getch();
		system("cls");

		// if arrow key is pressed
		if (key == -32) {
			switch (-32 + _getch()) {
			case KEY_UP:
				// move selection up
				if (optionIndex != 0) {
					if (extraItemToPrint) {
						optionIndex -= 2;
					}
					else {
						optionIndex -= 1;
					}
				}
				// move selection to bottom
				else {
					if (extraItemToPrint) {
						optionIndex = numOptions - 2;
					}
					else {
						optionIndex = numOptions - 1;
					}
				}
				break;
			case KEY_DOWN:
				// move selection down
				if (extraItemToPrint) {
					if (optionIndex != numOptions - 2) {
						optionIndex += 2;
					}
					else {
						optionIndex = 0;
					}
				}
				else if (optionIndex != numOptions - 1) {
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

void Mastermind::printVector(vector<string> vectorToPrint, int numItems, int insertIndex, string insertElement, string elementIndent, bool extraItemToPrint) {
	int incrementAdjustment = 1;
	int stopIndex = numItems;
	if (extraItemToPrint) {
		incrementAdjustment = 2;
		stopIndex = numItems - 1;
	}
	// if extra element given at non defauly (-1) index
	if (insertIndex != -1) {
		for (int i = 0; i < stopIndex; i += incrementAdjustment) {
			// add insert element at given index
			if (i == insertIndex) {
				// add brackets to highlight element
				cout << "\t\t\t\t\t\t" << elementIndent << insertElement << "[" << vectorToPrint[i] << "]\n" << endl;
				if (extraItemToPrint) {
					cout << "\t\t\t\t\t\t" << elementIndent << "   " << vectorToPrint[i + 1] << "\n\n" << endl;
				}
			}
			else {
				// add whitespace to align vector elements
				cout << "\t\t\t\t\t\t" << elementIndent << "   " << vectorToPrint[i] << "\n" << endl;
				if (extraItemToPrint) {
					cout << "\t\t\t\t\t\t" << elementIndent << "   " << vectorToPrint[i + 1] << "\n\n" << endl;
				}
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
