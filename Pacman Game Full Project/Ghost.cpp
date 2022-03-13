#include "Ghost.h"


int Ghost::ghostCounter = 0;

Ghost::Ghost(int Level,char indexator) :Game_object(indexator, Board::getGhostsStartLocation()[ghostCounter].X, Board::getGhostsStartLocation()[ghostCounter].Y)
{
	ghostCounter++;
	dir = setRandDir();
	this->gameLvl = Level;
}

Ghost::~Ghost()
{
	ghostCounter = 0;

}


int Ghost::setRandDir()const
{
	
	int arr[] = { 1, 2, 3, 4 };
	int x = rand() % 4;	// Generating random index 
	return arr[x];
}

void Ghost::move(HANDLE corse_for_Board, COORD* arr, int lenght, COORD target, int TimeToSleep,int dirParam)
{
	switch (this->gameLvl)
	{
	case(1): moveNOVICE(corse_for_Board, arr, lenght,TimeToSleep);
		break;
	case(2): moveGOOD(corse_for_Board, arr, lenght, target,TimeToSleep);
		break;
	case(3): moveBEST(corse_for_Board, arr, lenght, target,TimeToSleep);
		break;
	default: moveNOVICE(corse_for_Board, arr, lenght,TimeToSleep);
	}

}

void Ghost::moveNOVICE(HANDLE corse_for_Board, COORD* arr, int lenght,int TimeToSleep,int dirParam)
{
	if (dirParam == -1)
	{
		this->movesCounter++;
		if (movesCounter % 20 == 0)
		{
			int tempDir = dir;
			this->dir = setRandDir();
			while (tempDir == dir)
			{
				dir = setRandDir();
			}
		}

	}
	else
	{
		this->dir = dirParam;
	}

	if (this->dir == 1)
	{
		if (this->xcord == Board::getTOPLEFT().X + 1)
		{
			Game_object::stayFoot(corse_for_Board, TimeToSleep, 1, true);
		}
		else if (Board::IsCordIninnerWalls(this->xcord - 1,this->ycord))
		{
			Game_object::stayFoot(corse_for_Board,TimeToSleep, 1, true);
		}
		else
		{
			Game_object::move_Left(corse_for_Board,TimeToSleep, 1, arr, lenght);
		}
	}
	else if (this->dir == 2)
	{

		if (this->xcord == Board::getTOPRIGHT().X - 1)
		{
			Game_object::stayFoot(corse_for_Board,TimeToSleep, 1, true);
		}
		else if (Board::IsCordIninnerWalls(this->xcord+1,this->ycord))
		{
			Game_object::stayFoot(corse_for_Board,TimeToSleep, 1, true);
		}
		else
		{
			Game_object::move_Right(corse_for_Board,TimeToSleep, 1, arr, lenght);
		}
	}
	else if (this->dir == 3)
	{
		if (this->ycord == Board::getTOPRIGHT().Y + 1)
		{
			Game_object::stayFoot(corse_for_Board,TimeToSleep, 1, true);
		}
		else if (Board::IsCordIninnerWalls(this->xcord,this->ycord-1))
		{
			Game_object::stayFoot(corse_for_Board,TimeToSleep, 1, true);
		}
		else
		{
			Game_object::move_Up(corse_for_Board,TimeToSleep, 1, arr, lenght);
		}
	}
	else if (this->dir == 4)
	{
		if (this->ycord == Board::getBOTTOMRIGHT().Y - 1)
		{
			Game_object::stayFoot(corse_for_Board,TimeToSleep, 1, true);
		}
		else if (Board::IsCordIninnerWalls(this->xcord,this->ycord+1))
		{
			Game_object::stayFoot(corse_for_Board, TimeToSleep, 1, true);
		}
		else
		{
			Game_object::move_Down(corse_for_Board,TimeToSleep, 1, arr, lenght);
		}
	}
	Game_object::stayFoot(corse_for_Board,TimeToSleep/5, 1);
}

void Ghost::moveBEST(HANDLE corse_for_Board, COORD* arr, int lenght, COORD target,int TimeToSleep)
{
	if (target.X >= this->xcord && target.Y <this->ycord) // if the pacman location in up right from the ghost. ( move either up or right)
	{
		if (calcDisFromTarget(target, this->xcord + 1, this->ycord) < calcDisFromTarget(target, this->xcord,this->ycord-1))
		{
			if (this->xcord == Board::getTOPRIGHT().X - 1)
			{
				Game_object::move_Left(corse_for_Board, TimeToSleep, 1, arr, lenght);
			}
			else if (Board::IsCordIninnerWalls(this->xcord + 1,this->ycord))
			{
				if (Board::IsCordIninnerWalls(this->xcord, this->ycord-1)) 
				{
					Game_object::move_Left(corse_for_Board, TimeToSleep, 1, arr, lenght);
				}
				else
					Game_object::move_Up(corse_for_Board, TimeToSleep, 1, arr, lenght);
			}
			else
				Game_object::move_Right(corse_for_Board, TimeToSleep, 1, arr, lenght);
		}
		else if (calcDisFromTarget(target, this->xcord + 1, this->ycord) > calcDisFromTarget(target, this->xcord, this->ycord - 1))
		{
			if (this->ycord == Board::getTOPRIGHT().Y + 1)
			{
				Game_object::move_Down(corse_for_Board, TimeToSleep, 1, arr, lenght);
			}
			else if (Board::IsCordIninnerWalls(this->xcord,this->ycord-1))
			{
				if (Board::IsCordIninnerWalls(this->xcord+1, this->ycord))
				{
					Game_object::move_Down(corse_for_Board, TimeToSleep, 1, arr, lenght);
				}
				else
					Game_object::move_Right(corse_for_Board, TimeToSleep, 1, arr, lenght);
			}
			else
				Game_object::move_Up(corse_for_Board, TimeToSleep, 1, arr, lenght);
		}
		else
		{
			if (Board::IsCordIninnerWalls(this->xcord + 1, this->ycord))
			{
				if (Board::IsCordIninnerWalls(this->xcord, this->ycord - 1))
				{
					Game_object::move_Left(corse_for_Board, TimeToSleep, 1, arr, lenght);
				}
				else
					Game_object::move_Up(corse_for_Board, TimeToSleep, 1, arr, lenght);
			}
			else if (Board::IsCordIninnerWalls(this->xcord, this->ycord - 1))
			{
				if (Board::IsCordIninnerWalls(this->xcord+1, this->ycord))
				{
					Game_object::move_Left(corse_for_Board, TimeToSleep, 1, arr, lenght);
				}
				else
					Game_object::move_Right(corse_for_Board, TimeToSleep, 1, arr, lenght);
			}
			else
				Game_object::move_Up(corse_for_Board, 100, 1, arr, lenght);
		}
	}
	//-----------------------
	else if (target.X <= this->xcord && target.Y < this->ycord) // if the pacman location in up left from the ghost. ( move either up or left)
	{
		if (calcDisFromTarget(target, this->xcord - 1,this->ycord) < calcDisFromTarget(target, this->xcord,this->ycord-1))
		{
			if (this->xcord == Board::getTOPLEFT().X - 1)
			{
				Game_object::move_Right(corse_for_Board, TimeToSleep, 1, arr, lenght);
			}
			else if (Board::IsCordIninnerWalls(this->xcord - 1,this->ycord))
			{
				if (Board::IsCordIninnerWalls(this->xcord, this->ycord-1))
				{
					Game_object::move_Right(corse_for_Board, TimeToSleep, 1, arr, lenght);
				}
				else
					Game_object::move_Up(corse_for_Board, TimeToSleep, 1, arr, lenght);
			}
			else
				Game_object::move_Left(corse_for_Board, TimeToSleep, 1, arr, lenght);
		}
		else if (calcDisFromTarget(target, this->xcord - 1, this->ycord) > calcDisFromTarget(target, this->xcord, this->ycord - 1))
		{
			if (this->ycord == Board::getTOPRIGHT().Y + 1)
			{
				Game_object::move_Down(corse_for_Board, TimeToSleep, 1, arr, lenght);
			}
			else if (Board::IsCordIninnerWalls(this->xcord,this->ycord - 1 ))
			{
				if (Board::IsCordIninnerWalls(this->xcord-1, this->ycord))
				{
					Game_object::move_Down(corse_for_Board, TimeToSleep, 1, arr, lenght);
				}
				else
					Game_object::move_Left(corse_for_Board, TimeToSleep, 1, arr, lenght);
			}
			else
				Game_object::move_Up(corse_for_Board, TimeToSleep, 1, arr, lenght);
		}
		else
		{
			if (Board::IsCordIninnerWalls(this->xcord - 1, this->ycord))
			{
				if (Board::IsCordIninnerWalls(this->xcord, this->ycord-1))
				{
					Game_object::move_Right(corse_for_Board, TimeToSleep, 1, arr, lenght);
				}
				else
					Game_object::move_Up(corse_for_Board, TimeToSleep, 1, arr, lenght);
			}
			else if (Board::IsCordIninnerWalls(this->xcord, this->ycord-1))
			{
				if (Board::IsCordIninnerWalls(this->xcord - 1, this->ycord))
				{
					Game_object::move_Right(corse_for_Board, TimeToSleep, 1, arr, lenght);
				}
				else
					Game_object::move_Left(corse_for_Board, TimeToSleep, 1, arr, lenght);
			}
			else
				Game_object::move_Up(corse_for_Board, TimeToSleep, 1, arr, lenght);
		}
	}
	//-----------------
	else if (target.X < this->xcord && target.Y >= this->ycord) // if the pacman location in bottom left from the ghost. ( move either down or left)
	{

		if (calcDisFromTarget(target, this->xcord - 1, this->ycord) < calcDisFromTarget(target, this->xcord, this->ycord + 1))
		{
			if (this->xcord == Board::getTOPLEFT().X - 1)
			{
				Game_object::move_Right(corse_for_Board, TimeToSleep, 1, arr, lenght);
			}
			else if (Board::IsCordIninnerWalls(this->xcord - 1,this->ycord))
			{
				if (Board::IsCordIninnerWalls(this->xcord, this->ycord+1))
				{
					Game_object::move_Right(corse_for_Board, TimeToSleep, 1, arr, lenght);
				}
				else
					Game_object::move_Down(corse_for_Board, TimeToSleep, 1, arr, lenght);
			}
			else
				Game_object::move_Left(corse_for_Board, TimeToSleep, 1, arr, lenght);
		}
		else if (calcDisFromTarget(target, this->xcord - 1, this->ycord) > calcDisFromTarget(target, this->xcord, this->ycord + 1))
		{
			if (this->ycord == Board::getBOTTOMRIGHT().Y + 1)
			{
				Game_object::move_Up(corse_for_Board, TimeToSleep, 1, arr, lenght);
			}
			else if (Board::IsCordIninnerWalls(this->xcord,this->ycord + 1))
			{
				if (Board::IsCordIninnerWalls(this->xcord-1, this->ycord))
				{
					Game_object::move_Up(corse_for_Board, TimeToSleep, 1, arr, lenght);
				}
				else
					Game_object::move_Left(corse_for_Board, TimeToSleep, 1, arr, lenght);
			}
			else
				Game_object::move_Down(corse_for_Board, TimeToSleep, 1, arr, lenght);
		}
		else
		{
			if (Board::IsCordIninnerWalls(this->xcord, this->ycord + 1))
			{
				if (Board::IsCordIninnerWalls(this->xcord-1, this->ycord))
				{
					Game_object::move_Right(corse_for_Board, TimeToSleep, 1, arr, lenght);
				}
				else
					Game_object::move_Left(corse_for_Board, TimeToSleep, 1, arr, lenght);
			}
			else if (Board::IsCordIninnerWalls(this->xcord - 1, this->ycord))
			{
				if (Board::IsCordIninnerWalls(this->xcord, this->ycord+1))
				{
					Game_object::move_Right(corse_for_Board, TimeToSleep, 1, arr, lenght);
				}
				else
					Game_object::move_Down(corse_for_Board, TimeToSleep, 1, arr, lenght);
			}
			else
				Game_object::move_Down(corse_for_Board, TimeToSleep, 1, arr, lenght);
		}
	}
	//------------
	else if (target.X > this->xcord && target.Y >= this->ycord) // if the pacman location in bottom right from the ghost. ( move either down or right)
	{

		if (calcDisFromTarget(target, this->xcord + 1, this->ycord) < calcDisFromTarget(target, this->xcord, this->ycord + 1))
		{
			if (this->xcord == Board::getTOPRIGHT().X + 1)
			{
				Game_object::move_Left(corse_for_Board, TimeToSleep, 1, arr, lenght);
			}
			else if (Board::IsCordIninnerWalls(this->xcord + 1,this->ycord))
			{
				if (Board::IsCordIninnerWalls(this->xcord, this->ycord + 1))
				{
					Game_object::move_Left(corse_for_Board, TimeToSleep, 1, arr, lenght);
				}
				else
					Game_object::move_Down(corse_for_Board, TimeToSleep, 1, arr, lenght);
			}
			else
				Game_object::move_Right(corse_for_Board, TimeToSleep, 1, arr, lenght);
		}
		else if (calcDisFromTarget(target, this->xcord + 1, this->ycord) > calcDisFromTarget(target, this->xcord, this->ycord + 1))
		{
			if (this->ycord == Board::getBOTTOMRIGHT().Y + 1)
			{
				Game_object::move_Up(corse_for_Board, TimeToSleep, 1, arr, lenght);
			}
			else if (Board::IsCordIninnerWalls(this->xcord,this->ycord + 1))
			{
				if (Board::IsCordIninnerWalls(this->xcord + 1, this->ycord))
				{
					Game_object::move_Up(corse_for_Board, TimeToSleep, 1, arr, lenght);
				}
				else
					Game_object::move_Right(corse_for_Board, TimeToSleep, 1, arr, lenght);
			}
			else
				Game_object::move_Down(corse_for_Board, TimeToSleep, 1, arr, lenght);
		}
		else
		{
			if (Board::IsCordIninnerWalls(this->xcord, this->ycord + 1))
			{
				if (Board::IsCordIninnerWalls(this->xcord + 1, this->ycord))
				{
					Game_object::move_Left(corse_for_Board, TimeToSleep, 1, arr, lenght);
				}
				else
					Game_object::move_Right(corse_for_Board, TimeToSleep, 1, arr, lenght);
			}
			else if (Board::IsCordIninnerWalls(this->xcord + 1, this->ycord))
			{
				if (Board::IsCordIninnerWalls(this->xcord, this->ycord + 1))
				{
					Game_object::move_Left(corse_for_Board, TimeToSleep, 1, arr, lenght);
				}
				else
					Game_object::move_Down(corse_for_Board, TimeToSleep, 1, arr, lenght);
			}
			else
				Game_object::move_Down(corse_for_Board, TimeToSleep, 1, arr, lenght);
		}
	}
		Game_object::stayFoot(corse_for_Board, 1, 1);
}

void Ghost::moveGOOD(HANDLE corse_for_Board, COORD* arr, int lenght, COORD target,int TimeToSleep)
{
	if (movesCounter == 25)
	{
		movesCounter = 0;
	}

	this->movesCounter++;
	if (movesCounter >= 0 && movesCounter < 20)
	{
		moveBEST(corse_for_Board, arr, lenght, target,TimeToSleep);
		return;
	}
	else
	{
		if (movesCounter == 20)
		{
			dir = setRandDir();
		}

		if (this->dir == 1)
		{
			if (this->xcord == Board::getTOPLEFT().X + 1)
			{
				Game_object::stayFoot(corse_for_Board, TimeToSleep, 1, true);
			}
			else if (Board::IsCordIninnerWalls(this->xcord - 1,this->ycord))
			{
				Game_object::stayFoot(corse_for_Board, TimeToSleep, 1, true);
			}
			else
			{
				Game_object::move_Left(corse_for_Board, TimeToSleep, 1, arr, lenght);
			}
		}
		else if (this->dir == 2)
		{

			if (this->xcord == Board::getTOPRIGHT().X - 1)
			{
				Game_object::stayFoot(corse_for_Board, TimeToSleep, 1, true);
			}
			else if (Board::IsCordIninnerWalls(this->xcord + 1,this->ycord))
			{
				Game_object::stayFoot(corse_for_Board, TimeToSleep, 1, true);
			}
			else
			{
				Game_object::move_Right(corse_for_Board, TimeToSleep, 1, arr, lenght);
			}
		}
		else if (this->dir == 3)
		{
			if (this->ycord == Board::getTOPRIGHT().Y + 1)
			{
				Game_object::stayFoot(corse_for_Board, TimeToSleep, 1, true);
			}
			else if (Board::IsCordIninnerWalls(this->xcord,this->ycord - 1))
			{
				Game_object::stayFoot(corse_for_Board, TimeToSleep, 1, true);
			}
			else
			{
				Game_object::move_Up(corse_for_Board, TimeToSleep, 1, arr, lenght);
			}
		}
		else if (this->dir == 4)
		{
			if (this->ycord == Board::getBOTTOMRIGHT().Y - 1)
			{
				Game_object::stayFoot(corse_for_Board, TimeToSleep, 1, true);
			}
			else if (Board::IsCordIninnerWalls(this->xcord,this->ycord + 1))
			{
				Game_object::stayFoot(corse_for_Board, TimeToSleep, 1, true);
			}
			else
			{
				Game_object::move_Down(corse_for_Board, TimeToSleep, 1, arr, lenght);
			}
		}
		Game_object::stayFoot(corse_for_Board, TimeToSleep/5, 1);
	}
}

int Ghost::calcDisFromTarget(COORD target, short x, short y) const
{
	double xDis = abs(target.X - x);
	double yDis = abs(target.Y - y);
	return (int)(sqrt(pow(xDis, 2) + pow(yDis, 2)));
}