#include "Game_object.h"

using namespace std;

void Game_object::setStartCoords(COORD data)
{
	this->StartXcor =this->xcord =data.X; 

	this->StartYcord = this->ycord = data.Y;
}

Game_object::Game_object(const Game_object& other)
{
	this->StartXcor = other.StartXcor;
	this->xcord = other.xcord;
	this->ycord = other.ycord;
	this->StartYcord = other.StartYcord;
	this->indicator = other.indicator;
}

Game_object::Game_object(char indexator, short Sx, short Sy)
{
	this->StartXcor = Sx;
	this->xcord = Sx;
	this->ycord = Sy;
	this->StartYcord = Sy;
	this->indicator = indexator;
}

//this constractor is for the Fruit objects;
Game_object::Game_object()
{
	
	COORD Location = SetRandomCoord();

	this->StartXcor = Location.X;
	this->StartYcord = Location.Y;
	
	this->xcord = this->StartXcor;
	this->ycord = StartYcord;
	int arr[] = {5,6,7,8,9};
	int x = rand() % 5;
	this->indicator = arr[x] + '0';
}

COORD Game_object::SetRandomCoord()
{
	COORD* Arr = Board::GetFruitPossileLocations();
	int num = Board::GetFruitPossileLocationsArrSize();

	int random = rand() % num;
	return Arr[random];
}



void Game_object::move_Left(HANDLE corse_for_Board,int timeToSleep, int indicator, COORD* arr, int lenght)
{
	gotoxy(corse_for_Board, this->xcord, this->ycord);
	if(timeToSleep>0){
		cout << this->indicator << endl;
	}
	Sleep(timeToSleep);
	gotoxy(corse_for_Board, this->xcord, this->ycord);
	this->stepsVec.push_back(1);

	if(timeToSleep >0)
	{
		if (indicator == 0)//for pacman
		{
			cout << " " << endl;
		}
		else//for ghost or Fruit
		{
			if (isCoordInArr({ this->xcord,this->ycord }, arr, lenght) != -1)
			{
				cout << char(249) << endl;
			}
			else
			{
				cout << " " << endl;
			}

		}
	}
	
	--this->xcord;
	if (this->xcord < Board::getTOPLEFT().X + 1)
	{
		this->xcord = Board::getTOPRIGHT().X - 1;
	}
}
void Game_object::move_Right(HANDLE corse_for_Board,int timeToSleep, int indicator, COORD* arr, int lenght)
{
	
	gotoxy(corse_for_Board, this->xcord, this->ycord);
	if (timeToSleep > 0){ cout << this->indicator << endl; }
	Sleep(timeToSleep);
	gotoxy(corse_for_Board, this->xcord, this->ycord);
	this->stepsVec.push_back(2);

	if (timeToSleep > 0)
	{
		if (indicator == 0)//for packem
		{
			cout << " " << endl;
		}
		else//for gost
		{
			if (isCoordInArr({ this->xcord,this->ycord }, arr, lenght) != -1)
			{
				cout << char(249) << endl;
			}
			else
			{
				cout << " " << endl;
			}

		}
	}
	
	++this->xcord;
	if (this->xcord > Board::getTOPRIGHT().X - 1)
	{
		this->xcord = Board::getTOPLEFT().X + 1;
	}
}
void Game_object::move_Down(HANDLE corse_for_Board,int timeToSleep, int indicator, COORD* arr, int lenght)
{
	
	gotoxy(corse_for_Board, this->xcord, this->ycord);
	if (timeToSleep > 0) { cout << this->indicator << endl; }
	Sleep(timeToSleep);
	gotoxy(corse_for_Board, this->xcord, this->ycord);

	this->stepsVec.push_back(4);
	if (timeToSleep > 0)
	{
		if (indicator == 0)//for packem
		{
			cout << " " << endl;
		}
		else//for gost of Fruits
		{
			if (isCoordInArr({ this->xcord,this->ycord }, arr, lenght) != -1)
			{
				cout << char(249) << endl;
			}
			else
			{
				cout << " " << endl;
			}
		}
	}
	
	++this->ycord;
	if (this->ycord > Board::getBOTTOMLEFT().Y - 1)
	{
		this->ycord = Board::getTOPLEFT().Y + 1;
	}
}
void Game_object::move_Up(HANDLE corse_for_Board,int timeToSleep, int indicator, COORD* arr, int lenght)
{
	
	gotoxy(corse_for_Board, this->xcord, this->ycord);
	if (timeToSleep > 0) { cout << this->indicator << endl; }
	Sleep(timeToSleep);
	gotoxy(corse_for_Board, this->xcord, this->ycord);
	this->stepsVec.push_back(3);

	if (timeToSleep > 0)
	{
		if (indicator == 0)//for packem
		{
			cout << " " << endl;
		}
		else//for gost
		{
			if (isCoordInArr({ this->xcord,this->ycord }, arr, lenght) != -1)
			{
				cout << char(249) << endl;
			}
			else
			{
				cout << " " << endl;
			}
		}
		
	}
	--this->ycord;
	if (this->ycord < Board::getTOPRIGHT().Y + 1)
	{
		this->ycord = Board::getBOTTOMLEFT().Y - 1;
	}
	
}
void Game_object::stayFoot(HANDLE corse_for_Board,int timeToSleep, int indicator, bool status)
{
	if (status)
	{
		this->stepsVec.push_back(0);
	}

	gotoxy(corse_for_Board, this->xcord, this->ycord);
	if (timeToSleep > 0) { cout << this->indicator << endl; }
	Sleep(timeToSleep);

	
}

int Game_object::GetXcord()const
{
	return this->xcord;
}
int Game_object::GetYcord()const
{
	return this->ycord;
}

char Game_object::Getindicator()const
{

	return this->indicator;
}

void Game_object::ResetStartLocation(HANDLE corsor_for_Board, bool silenceMode)
{
	COORD dwCursorPosition;
	dwCursorPosition = { this->xcord,this->ycord };
	SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
	if (!silenceMode)
	{
		cout << " ";
	}
	short x = this->StartXcor;
	this->xcord = x;
	short y = this->StartYcord;
	this->ycord = y;
	
}





int isCoordInArr(COORD c, COORD* BC, int length)
{
	for (short i = 0; i < length; i++)
	{
		if (BC[i].X == c.X && BC[i].Y == c.Y)
		{
			return i;
		}
	}
	return -1;
}

void gotoxy(HANDLE hConsoleOutput, short x, short y)
{
	COORD dwCursorPosition = { x, y };
	cout.flush();
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}
