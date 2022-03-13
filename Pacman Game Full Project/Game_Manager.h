#pragma once
#include "Board.h"
#include "Bread_Crumbs.h"
#include "Ghost.h"
#include "Pacman.h"
#include "Fruit.h"
#include "FileHandler.h"
#include "AutoMoves.h"
#include "OutPutSteps.h"
#include <vector>


// This class contains the data of everything related to the gameplay. 

class Game_Manager
{
private:
	Board* board;
	Pacman* pacman;
	Ghost** GhostArr;
	
	Bread_Crumbs* BreadCrumbsArr;
	Fruit* FruitPtr;
	int NumOfMovesOfFruitPtr=20;
	
	//------------------------------------------------------------

	void print_game_Board()const;// Print the game board. 
	void PrintPackmenStat()const; // Prints the pacman stats on every move. 
	void WinGame(bool SaveMood)const; // Checks if the game won (all breadcrumbs are eaten).
	
	void checkForInput(int* dir)const; // collects input from the user for next object direction. 
	void pauseGame()const; // pauses the game. 
	bool IsPacmenInGhostLocation()const; // checks if a collision happense. 
	bool ResetGame(bool SaveMood,bool silanceMood=false); // resets the game. 
	static void printInstructions(); // prints the instructions for the game. 
	bool ShouldCreateFruit();
	void RemoveFruit(bool SilencMode=false);
	static void printLevelOptions(COORD dwCursorPosition, int& Level); // gets the input regarding the game level from the user. 
	static void printPlayingOptions(COORD dwCursorPosition, int& playOption); // gets the input from the user regarding playing with a certain board. 
	static string getBoardNameFromUser(COORD dwCursorPosition, FileHandler &files);
	

public:

	static HANDLE corsor_for_Board;
	Game_Manager(string file, int Game_Level = 3);
	Game_Manager(int Game_Level = 3); // C'tor for default board. 
	Game_Manager(string file, const Pacman &P, int Game_Level = 3); // C'tor for Pacman --> for mulripule boards gameplay.  
	~Game_Manager();

	bool PlayGame(bool SaveMood); // Function managing the game while running. 
	
	int PlayAutoGame(AutoMoves AutoMovesObj, bool SilenceMode);//1 for win 0 for losse -1 for runOutOfMoves


	static bool mainMenu(int& Level,int& playOption, string& boardName, FileHandler &filesHandle); // Function to print the mainMenu and receive the user input.
	static bool printChooseToContinue();
	const Pacman& getPacman(); // Getter for Pacman data. 

	const bool CheckResultFile(const string ResFile,bool WinLose);//1 for win 0 for lose;

};

