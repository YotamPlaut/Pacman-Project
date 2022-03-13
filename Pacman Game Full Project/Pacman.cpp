#include "Pacman.h"

Pacman::Pacman(char indexator,short score, short lives,short extraScore):Game_object(indexator, Board::getPacmanStartLocation().X, Board::getPacmanStartLocation().Y)
{
	this->set_Lives(lives);
	this->set_Score(score);
	this->Set_ExtraScore(extraScore);
	this->Set_NumOfSteps(0);
}

void Pacman::set_Score(short i)
{
	this->Score = i;
}
short Pacman::get_Score()const
{
	return this->Score;
}
void Pacman::set_Lives(short i)
{
	this->Lives = i;
}
short Pacman::get_Lives()const
{
	return this->Lives;
}

vector<int> Pacman::get_stepsVector()
{
	return this->pacman_stepsVec;
}

short Pacman::Get_ExtraScore()const
{
	return this->ExtraScore;
}

void Pacman::Set_ExtraScore(short i)
{
	this->ExtraScore = i;
}

void Pacman::Set_NumOfSteps(short i)
{
	this->NumOfStemps = i;
}
short Pacman::Get_NumOfSteps()const
{
	return this->NumOfStemps;
}




void Pacman::move(int dir,HANDLE corse_for_Board,int timeToSleep)
{
	this->pacman_stepsVec.push_back(dir); 
	this->NumOfStemps++;
	bool IsInSecretDoor = this->checkIfPackmenInSecredDoor(dir);
	if (dir == 0)
	{
		Game_object::stayFoot(corse_for_Board,timeToSleep,0);
	}
	else if (dir == 1)
	{
		if (this->xcord == Board::getTOPLEFT().X + 1 && !IsInSecretDoor)
		{
			Game_object::stayFoot(corse_for_Board,timeToSleep,0);
		}
		else if(Board::IsCordIninnerWalls(this->xcord-1,this->ycord))
		{
			Game_object::stayFoot(corse_for_Board,timeToSleep, 0);
		}
		else
		{
			Game_object::move_Left(corse_for_Board,timeToSleep,0);
		}

	}
	else if (dir == 2)
	{
		if (this->xcord == Board::getTOPRIGHT().X - 1 && !IsInSecretDoor)
		{
			Game_object::stayFoot(corse_for_Board,timeToSleep,0);
		}
		else if(Board::IsCordIninnerWalls(this->xcord+1,this->ycord))
		{
			Game_object::stayFoot(corse_for_Board,timeToSleep, 0);
		}
		else
		{
			Game_object::move_Right(corse_for_Board,timeToSleep,0);
		}
	}
	else if (dir == 3)
	{
		if (this->ycord == Board::getTOPRIGHT().Y + 1 && !IsInSecretDoor)
		{
			Game_object::stayFoot(corse_for_Board,timeToSleep,0);
		}
		else if(Board::IsCordIninnerWalls(this->xcord,this->ycord-1))
		{
			Game_object::stayFoot(corse_for_Board,timeToSleep, 0);
		}
		else
		{
			Game_object::move_Up(corse_for_Board,timeToSleep,0);
		}
	}
	else if (dir == 4)
	{
		if (this->ycord == Board::getBOTTOMRIGHT().Y - 1 && !IsInSecretDoor)
		{
			Game_object::stayFoot(corse_for_Board, timeToSleep,0);
		}
		else if(Board::IsCordIninnerWalls(this->xcord,this->ycord +1))
		{
			Game_object::stayFoot(corse_for_Board,timeToSleep, 0);
		}
		else
		{
			Game_object::move_Down(corse_for_Board,timeToSleep,0);
		}
	}
	/*else if (dir == 0)
	{
		Game_object::stayFoot(corse_for_Board,timeToSleep,0);
	}*/
	Game_object::stayFoot(corse_for_Board, timeToSleep/5,0);
}

bool Pacman::checkIfPackmenInSecredDoor(int dir)
{
	if(dir==0)
	{
		return false;
	}
	//int Xcord = this->GetXcord();
	//int Ycord = this->GetYcord();
	COORD* SecretDoorsArr = Board::getSecterDoors();
	for (int i = 0; i < Board::getSecretDoorsArrSize(); i++)
	{
		if (dir == 1)
		{
			if (this->xcord == SecretDoorsArr[i].X + 1 && this->ycord == SecretDoorsArr[i].Y)
			{
				return true;
			}
		}
		if (dir == 2)
		{
			if (this->xcord == SecretDoorsArr[i].X - 1 && this->ycord == SecretDoorsArr[i].Y)
			{
				return true;
			}
		}
		else if (dir == 3)
		{
			if (this->xcord == SecretDoorsArr[i].X && this->ycord == SecretDoorsArr[i].Y + 1)
			{
				return true;
			}
		}
		else if (dir == 4)
		{
			if (this->xcord == SecretDoorsArr[i].X && this->ycord == SecretDoorsArr[i].Y - 1)
			{
				return true;
			}
		}
	}
	return false;
}


Pacman& Pacman:: operator+=(int x)
{
	this->ExtraScore = this->ExtraScore + x; // (ch - '0');
	//this->Set_ExtraScore(this->ExtraScore+short((ch - '0')));
	return *this;
}

Pacman& Pacman:: operator=(const Pacman& P)
{
	this->Lives = P.get_Lives();
	this->Score = P.get_Score();
	this->ExtraScore = P.Get_ExtraScore();
	//this->Set_NumOfSteps(P.Get_NumOfSteps());
	this->Set_NumOfSteps(0);

	return *this;
}

void Pacman:: AddFruitScore(char score)
{

	this->ExtraScore=this->ExtraScore+(score-'0');

}


void Pacman::PrintPacmanToFile(bool WinLoose)//1 for win 0 to loose
{
	string FileName;
	FileName += Board::GetBoardName();
	FileName += ".result.txt";
	ofstream myfile(FileName);
	if (myfile.is_open())
	{
		if (WinLoose)
		{
			myfile << "Win" << endl;
		}
		else
		{
			myfile<<"Lose"<<endl;
		}
		myfile << "Num_Of_Steps: " << this->NumOfStemps << endl;
		myfile << "Location: " << "{" << this->xcord << "," << this->ycord << "}";
		myfile.close();
	}
	else cout << "\n\nIWhsn't able to open result file\n\n";
}



