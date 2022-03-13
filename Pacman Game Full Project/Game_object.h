#pragma once
#include <iostream>
#include <windows.h>
#include "Board.h"
#include <vector>

// A parent calss for the pacman and ghosts including moving functions. 

class Game_object
{
protected:
	char indicator;
	short xcord;
	short ycord;
	short StartXcor;
	short StartYcord;
	

	// A function to check wether a breadcrumb is on the board. 
	friend int isCoordInArr(COORD c, COORD* BC, int length);
	friend void gotoxy(HANDLE hConsoleOutput, short x, short y);
	COORD SetRandomCoord();
	
	std::vector<int> stepsVec; 

public:
	Game_object(char indexator, short Sx, short Sy); // C'tor
	Game_object();//second C'tor

	Game_object(const Game_object &other); // Copy C'tor
	
	// Moving functions.
	void move_Left(HANDLE corse_for_Board,int timeToSleep, int indicator, COORD* arr = nullptr, int lenght = 0);
	void move_Right(HANDLE corse_for_Board, int timeToSleep, int indicator, COORD* arr = nullptr, int lenght = 0);
	void move_Down(HANDLE corse_for_Board,int timeToSleep, int indicator, COORD* arr = nullptr, int lenght = 0);
	void move_Up(HANDLE corse_for_Board,int timeToSleep, int indicator, COORD* arr = nullptr, int lenght = 0);
	void stayFoot(HANDLE corse_for_Board,int timeToSleep, int indicator, bool status = false);

	// Getters
	int GetXcord()const;
	int GetYcord()const;
	char Getindicator()const;
	virtual std::vector<int> get_stepsVector() { return this->stepsVec; } // getter for steps vector for file

	//Setters 
	void setStartCoords(COORD data);



	// Resets the object location whenever a ghost catches the pacman.
	void ResetStartLocation(HANDLE corsor_for_Board, bool silenceMode = false);


};

int isCoordInArr(COORD c, COORD* BC, int length);
void gotoxy(HANDLE hConsoleOutput, short x, short y);