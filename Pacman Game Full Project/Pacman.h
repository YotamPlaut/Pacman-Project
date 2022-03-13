#pragma once
#include"Game_object.h"
#include "Board.h"



using namespace std;


class Pacman : public Game_object
{
private:

	short Lives;
	short Score;
	short ExtraScore;
	int NumOfStemps;

	std::vector<int> pacman_stepsVec;

public:
	Pacman(const Pacman& object) : Game_object(object) { Lives = object.Lives, Score = object.Score,NumOfStemps=object.NumOfStemps,ExtraScore = object.ExtraScore; } // Copy C'tor.
	Pacman(char indexator = '@', short score = 0, short lives = 3, short extraScore = 0); // C'tor
	bool checkIfPackmenInSecredDoor(int dir); // a function to confirm if the pacman is in a secret door.
	// Getters.
	short get_Score()const;
	short get_Lives()const;
	short Get_ExtraScore()const;
	short Get_NumOfSteps()const;
	std::vector<int> get_stepsVector();
	//std::vector<int> get_stepsVector() { return this->stepsVec; }

	// Setters.
	void set_Score(short i);
	void set_Lives(short i);
	void Set_ExtraScore(short i);
	void Set_NumOfSteps(short i);
	
	//move function
	void move(int dir,HANDLE corse_for_Board,int timeToSleep); // move function for the pacman (uses the moving functions from Game_object).
	void AddFruitScore(char score);

	Pacman& operator+=(int x);
	Pacman& operator=(const Pacman &P); 

	void PrintPacmanToFile(bool WinLoose);


};

