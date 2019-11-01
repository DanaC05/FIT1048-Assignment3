/**************************************************
Project: Mastermind: The Last Of Us Edition
Assignment Num: 3
Author: Dana Casella
Purpose: Scenario Class Header
**************************************************/
#ifndef SCENARIO_H
#define SCENARIO_H

#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class Scenario
{
public:
	// constructors
	Scenario();
	~Scenario();

	// accessor methods
	void lastScenario();
	int getScenario();
	void setScenario();
	string getScenarioInfo();
	string getStartMessage();
	string getGameOverMessage();
	string getGameWonMessage();
	string getEnemy();
	string getObjective();
	string getItem();
	string getItemTextFile();

	// mutator methods
	void loadScenario(int scenarioNum);


private:
	// varialbles
	bool* firstScenarioPlayed;
	bool* playerFree;
	int* scenarioNumber;
	string* start;
	string* endWin;
	string* endLose;
	string* enemy;
	string* objective;
	string* item;
	string* textFileName;
	string* startInfoFile;

	// mutator variables
	void joelInjured();
	void imprisoned();
	void foodShortage();
	void ammoOut();
	void winter();
	void supplyRun();

};

#endif // !SCENARIO_H
