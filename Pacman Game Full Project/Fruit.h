#pragma once
#include "Game_object.h"
#include "Board.h"

class Fruit:public Game_object
{
private:
	static int _counter;
	int SetRandDir();
	int _timer;
	//static int deadStepsCounter; 
	static std::vector<int> stepsVec_fruit;

public:

	static void pushDeadStepToVec() { stepsVec_fruit.push_back(0); }
	static std::vector<int> get_FruitstepsVector() { return stepsVec_fruit; } // getter for steps vector for file
	static void clearFruitStepsVec() { stepsVec_fruit.clear(); }
	static int GetCounter(){return _counter; };
	int GetTimer() { return _timer;};
	void move(HANDLE corse_for_Board, COORD* arr, int lenght,int TimeToSleep);
	Fruit();
	~Fruit();
};

