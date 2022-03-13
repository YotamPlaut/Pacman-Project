#include "Fruit.h"

int Fruit::_counter;
//int Fruit::deadStepsCounter; 
vector<int> Fruit::stepsVec_fruit; 

Fruit::Fruit():Game_object()
{
	_counter++;
	_timer = 0;

	//deadStepsCounter = 0; // Initialize the dead moves counter every time a fruit is created. 

	//this->stepsVec_fruit.push_back(5); // puts 5 in the vector when fruit is created. 

	
};

Fruit:: ~Fruit()
{
	this->stepsVec_fruit.insert(stepsVec_fruit.end(), _timer, 1); // push to the vector 1 the amount of moves he was alive in. 
	  
	_counter--;
}

int Fruit::SetRandDir()
{
	int arr[] = { 1, 2, 3, 4 };
	int x = rand() % 4;	// Generating random index 
	return arr[x];

}

void Fruit::move(HANDLE corse_for_Board, COORD* arr, int lenght,int TimeToSleep)
{
	int dir = SetRandDir();
	if (dir == 1)
	{
		if (this->xcord == Board::getTOPLEFT().X + 1)
		{
			if (Board::IsCordIninnerWalls(this->xcord + 1, this->ycord))
			{
				Game_object::stayFoot(corse_for_Board,TimeToSleep, 1);
			}
			else
			{
				Game_object::move_Right(corse_for_Board,TimeToSleep, 1, arr, lenght);
			}

		}
		else if (Board::IsCordIninnerWalls(this->xcord - 1, this->ycord))
		{
			Game_object::stayFoot(corse_for_Board, TimeToSleep, 1);
		}
		else
		{
			Game_object::move_Left(corse_for_Board,TimeToSleep, 1, arr, lenght);
		}
	}
	else if (dir == 2)
	{

		if (this->xcord == Board::getTOPRIGHT().X - 1)
		{
			if (Board::IsCordIninnerWalls(this->xcord - 1, this->ycord))
			{
				Game_object::stayFoot(corse_for_Board,TimeToSleep, 1);
			}
			else
			{
				Game_object::move_Left(corse_for_Board,TimeToSleep, 1, arr, lenght);
			}

		}
		else if (Board::IsCordIninnerWalls(this->xcord + 1, this->ycord))
		{
			Game_object::stayFoot(corse_for_Board, TimeToSleep, 1);
		}
		else
		{
			Game_object::move_Right(corse_for_Board,TimeToSleep, 1, arr, lenght);
		}
	}
	else if (dir == 3)
	{
		if (this->ycord == Board::getTOPRIGHT().Y + 1)
		{
			if (Board::IsCordIninnerWalls(this->xcord, this->ycord - 1))
			{
				Game_object::move_Down(corse_for_Board,TimeToSleep, 1, arr, lenght);
			}
			else
			{
				Game_object::stayFoot(corse_for_Board,TimeToSleep, 1);
			}
		}
		else if (Board::IsCordIninnerWalls(this->xcord, this->ycord - 1))
		{
			Game_object::stayFoot(corse_for_Board, TimeToSleep, 1);
		}
		else
		{
			Game_object::move_Up(corse_for_Board,TimeToSleep,1, arr, lenght);
		}
	}
	else if (dir == 4)
	{
		if (this->ycord == Board::getBOTTOMRIGHT().Y - 1)
		{
			if (Board::IsCordIninnerWalls(this->xcord, this->ycord + 1))
			{
				Game_object::stayFoot(corse_for_Board,TimeToSleep, 1);
			}
			else
			{
				Game_object::move_Up(corse_for_Board,TimeToSleep, 1, arr, lenght);
			}
		}
		else if (Board::IsCordIninnerWalls(this->xcord, this->ycord + 1))
		{
			Game_object::stayFoot(corse_for_Board,TimeToSleep, 1);
		}
		else
		{
			Game_object::move_Down(corse_for_Board,TimeToSleep, 1, arr, lenght);
		}
	}
	Game_object::stayFoot(corse_for_Board,TimeToSleep, 1);
	this->_timer++;
}



