#include "Game_Manager.h"
#include <conio.h>
#include <Windows.h>

HANDLE Game_Manager::corsor_for_Board = GetStdHandle(STD_OUTPUT_HANDLE);

Game_Manager::Game_Manager(int Game_Level) // C'tor for default board. 
{
	this->board = new Board(); // --->for defualt Board
	



	this->pacman = new Pacman();
	this->GhostArr = new Ghost * [Board::getNumOfGhost()];
	for (int i = 0; i < Board::getNumOfGhost(); i++)
	{
		this->GhostArr[i] = new Ghost(Game_Level);
	}
	this->BreadCrumbsArr = new Bread_Crumbs();
	FruitPtr = nullptr;
}

Game_Manager::Game_Manager(string file, int Game_Level)
{
	//this->board = new Board();--->for defualt Board.
	this->board = new Board(file);//for reading file.



	this->pacman = new Pacman();
	this->GhostArr = new Ghost * [Board::getNumOfGhost()];
	for(int i=0;i<Board::getNumOfGhost();i++)
	{
		this->GhostArr[i] = new Ghost(Game_Level);
	}
	this->BreadCrumbsArr=new Bread_Crumbs();
	FruitPtr = nullptr;
};

Game_Manager::Game_Manager(string file, const Pacman &P, int Game_Level)
{
	
	//this->board = new Board();--->for defualt Board.
	this->board = new Board(file);//for reading file.



	this->pacman = new Pacman(P);
	this->pacman->setStartCoords(Board::getPacmanStartLocation());
	this->GhostArr = new Ghost * [Board::getNumOfGhost()];
	for (int i = 0; i < Board::getNumOfGhost(); i++)
	{
		this->GhostArr[i] = new Ghost(Game_Level);
	}
	this->BreadCrumbsArr = new Bread_Crumbs();
	FruitPtr = nullptr;
}

Game_Manager::~Game_Manager()
{
	

	for(int i=0 ; i<Board::getNumOfGhost() ; i++)
	{
		delete this->GhostArr[i];
	}
	delete GhostArr;
	delete pacman;
	delete BreadCrumbsArr;
	if(FruitPtr)
	{
		delete FruitPtr;
	}
}

bool Game_Manager::PlayGame(bool SaveMood)
{
	Fruit::clearFruitStepsVec(); 
	print_game_Board();
	bool play = true;
	int dir = 0;
	short Index_ForBread_Crumbs;



	while (play)
	{

		if (this->BreadCrumbsArr->GetCurrntlength() == 0)
		{
			this->WinGame(SaveMood);
			return true;
		}
		this->pacman->move(dir, this->corsor_for_Board,50);
		Index_ForBread_Crumbs = isCoordInArr({ short(this->pacman->GetXcord()),short(this->pacman->GetYcord()) }, this->BreadCrumbsArr->GetArr(), this->BreadCrumbsArr->GetCurrntlength());
		if (dir != 0 && Index_ForBread_Crumbs != -1)
		{
			this->pacman->set_Score(this->pacman->get_Score() + 1);
			this->BreadCrumbsArr->RemoveCordFromArr(Index_ForBread_Crumbs);
			this->PrintPackmenStat();
		}
		if (BreadCrumbsArr->GetCurrntlength() == 0)
		{
			this->WinGame(SaveMood);
			return true;
		}
		if (this->FruitPtr != nullptr)
		{
			if (this->pacman->GetXcord() == this->FruitPtr->GetXcord() && this->pacman->GetYcord() == this->FruitPtr->GetYcord())
			{
				this->pacman->AddFruitScore(FruitPtr->Getindicator());
				this->RemoveFruit();
				this->PrintPackmenStat();
			}
		}
		this->checkForInput(&dir);
		if (this->IsPacmenInGhostLocation())
		{
			play = ResetGame(SaveMood);
			if (play == false)
			{
				return false;
			}
			Sleep(600);
		}


		if (Board::getNumOfGhost() >= 1)
		{
			this->GhostArr[0]->move(this->corsor_for_Board, this->BreadCrumbsArr->GetArr(), this->BreadCrumbsArr->GetCurrntlength(),{(short)pacman->GetXcord(),(short)pacman->GetYcord()},100);
			if (IsPacmenInGhostLocation())
			{
				play = ResetGame(SaveMood);
				if (play == false)
				{
					return false;
				}
				Sleep(600);
			}
			if (this->FruitPtr != nullptr)
			{
				if (this->GhostArr[0]->GetXcord() == this->FruitPtr->GetXcord() && this->GhostArr[0]->GetYcord() == this->FruitPtr->GetYcord())
				{
					this->RemoveFruit();
				}
			}

			this->pacman->move(dir, this->corsor_for_Board,50);
			Index_ForBread_Crumbs = isCoordInArr({ short(this->pacman->GetXcord()),short(this->pacman->GetYcord()) }, this->BreadCrumbsArr->GetArr(), this->BreadCrumbsArr->GetCurrntlength());
			if (dir != 0 && Index_ForBread_Crumbs != -1)
			{
				this->pacman->set_Score(this->pacman->get_Score() + 1);
				this->BreadCrumbsArr->RemoveCordFromArr(Index_ForBread_Crumbs);
				PrintPackmenStat();
			}
			if (this->FruitPtr != nullptr)
			{
				if (this->pacman->GetXcord() == this->FruitPtr->GetXcord() && this->pacman->GetYcord() == this->FruitPtr->GetYcord())
				{
					this->pacman->AddFruitScore(FruitPtr->Getindicator());
					this->RemoveFruit();
					this->PrintPackmenStat();

				}
			}

			if (BreadCrumbsArr->GetCurrntlength() == 0)
			{
				WinGame(SaveMood);
				return true;
			}
			this->checkForInput(&dir);
			if (IsPacmenInGhostLocation())
			{
				play = ResetGame(SaveMood);
				std::cout.flush();
				if (play == false)
				{
					return false;
				}

				Sleep(600);
			}

		}
		if (Board::getNumOfGhost() >= 2)
		{
			this->GhostArr[1]->move(this->corsor_for_Board, this->BreadCrumbsArr->GetArr(), this->BreadCrumbsArr->GetCurrntlength(), { (short)pacman->GetXcord(),(short)pacman->GetYcord()},100);
			if (IsPacmenInGhostLocation())
			{
				play = ResetGame(SaveMood);
				if (play == false)
				{
					return false;
				}
				Sleep(600);
			}
			if (this->FruitPtr != nullptr)
			{
				if (this->GhostArr[1]->GetXcord() == this->FruitPtr->GetXcord() && this->GhostArr[1]->GetYcord() == this->FruitPtr->GetYcord())
				{
					this->RemoveFruit();
				}
			}
			this->pacman->move(dir, this->corsor_for_Board,50);
			Index_ForBread_Crumbs = isCoordInArr({ short(this->pacman->GetXcord()),short(this->pacman->GetYcord()) }, this->BreadCrumbsArr->GetArr(), this->BreadCrumbsArr->GetCurrntlength());
			if (dir != 0 && Index_ForBread_Crumbs != -1)
			{
				this->pacman->set_Score(this->pacman->get_Score() + 1);
				this->BreadCrumbsArr->RemoveCordFromArr(Index_ForBread_Crumbs);
				PrintPackmenStat();
			}
			if (this->FruitPtr != nullptr)
			{
				if (this->pacman->GetXcord() == this->FruitPtr->GetXcord() && this->pacman->GetYcord() == this->FruitPtr->GetYcord())
				{
					this->pacman->AddFruitScore(FruitPtr->Getindicator());
					this->RemoveFruit();
					this->PrintPackmenStat();

				}
			}

			if (BreadCrumbsArr->GetCurrntlength() == 0)
			{
				WinGame(SaveMood);
				return true;
			}
			this->checkForInput(&dir);
			if (IsPacmenInGhostLocation())
			{
				play = ResetGame(SaveMood);
				std::cout.flush();
				if (play == false)
				{
					return false;
				}

				Sleep(600);
			}

		}
		if (Board::getNumOfGhost() >= 3)
		{
			this->GhostArr[2]->move(this->corsor_for_Board, this->BreadCrumbsArr->GetArr(), this->BreadCrumbsArr->GetCurrntlength(), { (short)pacman->GetXcord(),(short)pacman->GetYcord()},100);
			if (IsPacmenInGhostLocation())
			{
				play = ResetGame(SaveMood);
				if (play == false)
				{
					return false;
				}
				Sleep(600);
			}
			if (this->FruitPtr != nullptr)
			{
				if (this->GhostArr[0]->GetXcord() == this->FruitPtr->GetXcord() && this->GhostArr[0]->GetYcord() == this->FruitPtr->GetYcord())
				{
					this->RemoveFruit();
				}
			}
			this->pacman->move(dir, this->corsor_for_Board,50);
			Index_ForBread_Crumbs = isCoordInArr({ short(this->pacman->GetXcord()),short(this->pacman->GetYcord()) }, this->BreadCrumbsArr->GetArr(), this->BreadCrumbsArr->GetCurrntlength());
			if (dir != 0 && Index_ForBread_Crumbs != -1)
			{
				this->pacman->set_Score(this->pacman->get_Score() + 1);
				this->BreadCrumbsArr->RemoveCordFromArr(Index_ForBread_Crumbs);
				PrintPackmenStat();
			}
			if (this->FruitPtr != nullptr)
			{
				if (this->pacman->GetXcord() == this->FruitPtr->GetXcord() && this->pacman->GetYcord() == this->FruitPtr->GetYcord())
				{
					this->pacman->AddFruitScore(FruitPtr->Getindicator());
					this->RemoveFruit();
					this->PrintPackmenStat();

				}
			}

			if (BreadCrumbsArr->GetCurrntlength() == 0)
			{
				WinGame(SaveMood);
				return true;
			}
			this->checkForInput(&dir);
			if (IsPacmenInGhostLocation())
			{
				play = ResetGame(SaveMood);
				std::cout.flush();
				if (play == false)
				{
					return false;
				}

				Sleep(600);
			}

		}
		if (Board::getNumOfGhost() >= 4)
		{
			this->GhostArr[3]->move(this->corsor_for_Board, this->BreadCrumbsArr->GetArr(), this->BreadCrumbsArr->GetCurrntlength(), { (short)pacman->GetXcord(),(short)pacman->GetYcord()},100);
			if (IsPacmenInGhostLocation())
			{
				play = ResetGame(SaveMood);
				if (play == false)
				{
					return false;
				}
				Sleep(600);
			}
			if (this->FruitPtr != nullptr)
			{
				if (this->GhostArr[0]->GetXcord() == this->FruitPtr->GetXcord() && this->GhostArr[0]->GetYcord() == this->FruitPtr->GetYcord())
				{
					this->RemoveFruit();
				}
			}
			this->pacman->move(dir, this->corsor_for_Board,50);
			Index_ForBread_Crumbs = isCoordInArr({ short(this->pacman->GetXcord()),short(this->pacman->GetYcord()) }, this->BreadCrumbsArr->GetArr(), this->BreadCrumbsArr->GetCurrntlength());
			if (dir != 0 && Index_ForBread_Crumbs != -1)
			{
				this->pacman->set_Score(this->pacman->get_Score() + 1);
				this->BreadCrumbsArr->RemoveCordFromArr(Index_ForBread_Crumbs);
				PrintPackmenStat();
			}
			if (this->FruitPtr != nullptr)
			{
				if (this->pacman->GetXcord() == this->FruitPtr->GetXcord() && this->pacman->GetYcord() == this->FruitPtr->GetYcord())
				{
					this->pacman->AddFruitScore(FruitPtr->Getindicator());
					this->RemoveFruit();
					this->PrintPackmenStat();

				}
			}

			if (BreadCrumbsArr->GetCurrntlength() == 0)
			{
				WinGame(SaveMood);
				return true;
			}
			this->checkForInput(&dir);
			if (IsPacmenInGhostLocation())
			{
				play = ResetGame(SaveMood);
				std::cout.flush();
				if (play == false)
				{
					return false;
				}

				Sleep(600);
			}

		}

		//fruit cration
		if (Fruit::GetCounter() == 0) // if fruit is dead. 
		{
			if (this->ShouldCreateFruit())
			{
				this->FruitPtr = new Fruit();
				FruitPtr->move(this->corsor_for_Board, this->BreadCrumbsArr->GetArr(), this->BreadCrumbsArr->GetCurrntlength(),120);
				for(int i=0;i<Board::getNumOfGhost();i++)
				{
					if (this->GhostArr[i]->GetXcord() == this->FruitPtr->GetXcord() && this->GhostArr[i]->GetYcord() == this->FruitPtr->GetYcord())
					{
						this->RemoveFruit();
					}
				
				}
			}
			else 
			{
				// while fruit is dead, push 0 into the steps vector. 
				Fruit::pushDeadStepToVec(); 
			}
			
		}
		else
		{
			if (FruitPtr != nullptr && FruitPtr->GetTimer() == this->NumOfMovesOfFruitPtr)
			{
				RemoveFruit();
			}
			else
			{
				FruitPtr->move(this->corsor_for_Board, this->BreadCrumbsArr->GetArr(), this->BreadCrumbsArr->GetCurrntlength(),120);
				for (int i = 0; i < Board::getNumOfGhost(); i++)
				{
					if (this->GhostArr[i]->GetXcord() == this->FruitPtr->GetXcord() && this->GhostArr[i]->GetYcord() == this->FruitPtr->GetYcord())
					{
						this->RemoveFruit();
					}

				}
			}
		}

	}
}


void Game_Manager::print_game_Board() const
{
	system("CLS"); 
	PrintPackmenStat();
	COORD dwCursorPosition;
	short i;
	for (i = Board::getTOPLEFT().X; i <= Board::getTOPRIGHT().X; i++)
	{
		cout.flush();
		dwCursorPosition = { i,Board::getTOPLEFT().Y };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << char(254);//"- ";
	}

	for (i = Board::getBOTTOMLEFT().X; i <= Board::getBOTTOMRIGHT().X; i++)
	{
		cout.flush();
		dwCursorPosition = { i,Board::getBOTTOMLEFT().Y };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << char(254);//"- ";
	}

	for (i = Board::getTOPLEFT().Y; i <= Board::getBOTTOMLEFT().Y; i++)
	{
		cout.flush();
		dwCursorPosition = { Board::getTOPLEFT().X,i };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << char(222);// "|";
	}

	for (i = Board::getTOPLEFT().Y; i <= Board::getBOTTOMLEFT().Y; i++)
	{
		cout.flush();
		dwCursorPosition = { Board::getTOPRIGHT().X,i };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << char(221);// "|";
	}
	COORD* SecterDoorsArry = Board::getSecterDoors();
	for (i=0; i < Board::getSecretDoorsArrSize() ; i++)
	{
		cout.flush();
		dwCursorPosition = { SecterDoorsArry[i].X,SecterDoorsArry[i].Y };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << char(177);
	}

	COORD* IneerWalls = Board::getBoardInnerWalls();
	for (i = 0; i < Board::getBoardInnerWallsArrSize(); i++)
	{
		cout.flush();
		dwCursorPosition = { IneerWalls[i].X,IneerWalls[i].Y };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << char(219);
	}

	COORD* arr = this->BreadCrumbsArr->GetArr();
	for (i = 0; i < this->BreadCrumbsArr->GetMaxlength(); i++)
	{

		cout.flush();
		dwCursorPosition = { arr[i].X,arr[i].Y };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << char(249);
	}
}

void Game_Manager::PrintPackmenStat()const
{
	COORD Location = Board::GetLegngdLocation();
	cout.flush();
	COORD dwCursorPosition;

	dwCursorPosition = {Location.X+2,Location.Y+2};
	SetConsoleCursorPosition(this->corsor_for_Board, dwCursorPosition);
	cout << "                  ";



	for (short i = 0;i<20; i++)
	{
		dwCursorPosition = {i+Location.X,Location.Y};
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << "-";
	}
	for (short i = 0;i<20; i++)
	{
		dwCursorPosition = {i+ Location.X,Location.Y+4};
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << "-";
	}
	/*
	for (short i = 0; i < 5; i++)
	{
		dwCursorPosition = {Location.X+25,i};
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << "|";
	}
	for (short i = 0; i < 5; i++)
	{
		dwCursorPosition = {Location.X,i};
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << "|";
	}
	*/
	dwCursorPosition = {Location.X+5,Location.Y+1};
	SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
	cout << "Game status";
	dwCursorPosition = {Location.X+12,Location.Y+2};
	SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
	cout << "lives:" << this->pacman->get_Lives();
	dwCursorPosition = {Location.X+1,Location.Y+2};
	SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
	cout << "score:" << this->pacman->get_Score();
	dwCursorPosition = {Location.X+7,Location.Y+3};
	SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
	cout << "Fruit:" << this->pacman->Get_ExtraScore();


}

void Game_Manager::WinGame(bool SaveMood)const
{
	system("CLS");
	cout << "!!!!!!You finished the board!!!!!!" << endl;
	cout << "Press Any key to continue";
	if (SaveMood)
	{

		vector<vector<int>> ghostStepsVec;
		for (int i = 0; i < Board::getNumOfGhost(); i++)
		{
			ghostStepsVec.push_back(this->GhostArr[i]->get_stepsVector());
		}
		OutPutSteps::stepVectorsToMat(pacman->get_stepsVector(), ghostStepsVec, FruitPtr->get_FruitstepsVector());
		OutPutSteps::printStepsToFile();
		OutPutSteps::resetVector();

		this->pacman->PrintPacmanToFile(1);
	}

	if (_getch())
	{
		system("CLS");
		return;
	}
}

void Game_Manager::checkForInput(int* dir)const
{
	if (_kbhit())
	{
		char ch = _getch();
		if (ch == 97 || ch == 65)
		{
			*dir = 1;
		}
		else if (ch == 100 || ch == 68)
		{
			*dir = 2;
		}
		else if (ch == 119 || ch == 87)
		{
			*dir = 3;
		}
		else if (ch == 88 || ch == 120)
		{
			*dir = 4;
		}
		else if (ch == 115 || ch == 83)
		{
			*dir = 0;
		}
		else if (ch == 27)
		{
			this->pauseGame();
		}
	}
	else
		return;


}

void Game_Manager::pauseGame()const
{
	COORD dwCursorPosition;
	COORD Location = Board::GetLegngdLocation();
	dwCursorPosition = { Location.X + 5,Location.Y + 1 };
	SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
	cout << "           ";
	dwCursorPosition = { Location.X + 12,Location.Y + 2 };
	SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
	cout << "          ";
	dwCursorPosition = { Location.X + 1,Location.Y + 2 };
	SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
	cout << "           "; 
	dwCursorPosition = { Location.X + 7,Location.Y + 3 };
	SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
	cout << "           ";

	dwCursorPosition = { Location.X+5,Location.Y + 1 };
	SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
	cout << "Pause Game";
	dwCursorPosition = { Location.X,Location.Y + 2 };
	SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
	cout << "Press Esc to Return";



	bool pause = true;
	while (pause)
	{
		if (_kbhit())
		{
			char ch = _getch();
			if (ch == 27)
			{
				pause = false;
			}

		}
		Sleep(10);
	}
	dwCursorPosition = { Location.X + 5,Location.Y + 1 };
	SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
	cout << "        ";
	dwCursorPosition = { Location.X,Location.Y + 2 };
	SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
	cout << "           ";


	PrintPackmenStat();



}

bool Game_Manager::IsPacmenInGhostLocation()const
{
	for(int i=0;i<Board::getNumOfGhost();i++)
	{
		if (this->pacman->GetXcord() == this->GhostArr[i]->GetXcord() && this->pacman->GetYcord() == this->GhostArr[i]->GetYcord())
		{
			return true;
		}

	}
	return false;


}

bool Game_Manager::ResetGame(bool SaveMood, bool silanceMood)
{
	
	this->pacman->set_Lives(this->pacman->get_Lives() - 1);
	if (this->pacman->get_Lives() == 0)
	{
		if(SaveMood)
		{
			
			vector<vector<int>> ghostStepsVec;
			for (int i = 0; i < Board::getNumOfGhost(); i++)
			{
				ghostStepsVec.push_back(this->GhostArr[i]->get_stepsVector());
			}
			OutPutSteps::stepVectorsToMat(pacman->get_stepsVector(), ghostStepsVec, FruitPtr->get_FruitstepsVector());
			OutPutSteps::printStepsToFile();
			//OutPutSteps::resetVector();

			
			this->pacman->PrintPacmanToFile(0);
		}
		cout.flush();
		system("CLS");
		if (!silanceMood)
		{
			cout << "You lost all of your life, get it back together and come back to play some more !" << endl;
			cout << "Press Enter to go back to main menu";
			cout << "\n\n\n\n";

			if (_getch())
			{
				system("CLS");
				return false;
			}
		}
		else
		{
			return false;
		}
		
		
	}

	if (!silanceMood)
	{
		COORD Location = Board::GetLegngdLocation();
		COORD dwCursorPosition;
		cout.flush();
		dwCursorPosition = { Location.X + 5,Location.Y + 1 };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << "           ";
		dwCursorPosition = { Location.X + 12,Location.Y + 2 };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << "          ";
		dwCursorPosition = { Location.X + 1,Location.Y + 2 };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << "          ";
		dwCursorPosition = { Location.X + 7,Location.Y + 3 };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << "          ";
		dwCursorPosition = { Location.X + 5,Location.Y + 1 };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << "you lost a life";
		//this->pacman->ResetStartLocation(this->corsor_for_Board);
		//for (int i = 0; i < Board::getNumOfGhost(); i++)
		//{
		//	this->GhostArr[i]->ResetStartLocation(this->corsor_for_Board);
		//}
		Sleep(1500);
		dwCursorPosition = { Location.X + 5,Location.Y + 1 };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << "                ";
		this->PrintPackmenStat();
	}
	this->pacman->ResetStartLocation(this->corsor_for_Board, silanceMood);
	for (int i = 0; i < Board::getNumOfGhost(); i++)
	{
		this->GhostArr[i]->ResetStartLocation(this->corsor_for_Board, silanceMood);
	}
	return true;
}

bool Game_Manager::mainMenu(int& Level, int& playOption, string& boardName, FileHandler& filesHandle)
{
	COORD dwCursorPosition;
	cout.flush();

	while (!_kbhit())
	{
		cout.flush();

		dwCursorPosition = { 20,8 };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << "|-----------------------------------|";
		dwCursorPosition = { 20,9 };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << "|             Main Menu             |";
		dwCursorPosition = { 20,10 };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << "|(1) Start a new game               |";
		dwCursorPosition = { 20,11 };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << "|(8) Present instructions and keys  |";
		dwCursorPosition = { 20,12 };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << "|(9) Exit                           |";
		dwCursorPosition = { 20,13 };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << "|-----------------------------------|";

		int res;
		cin >> res;

		switch (res)
		{
		case 1:
			printPlayingOptions(dwCursorPosition, playOption);
			if (playOption == 3)
			{
				boardName = getBoardNameFromUser(dwCursorPosition, filesHandle);
			}
			system("CLS");
			printLevelOptions(dwCursorPosition, Level);
			return true; // Begin a new game; 

		case 8:
			printInstructions();
			system("CLS");
			break;

		case 9:
			return false; /// EXIT;

		default:
			cout << "Please enter a valid option !" << endl;	
		}
	}
	return false;
}

bool Game_Manager::printChooseToContinue()
{
	COORD dwCursorPosition;
	cout.flush();

	while (!_kbhit())
	{
		cout.flush();

		dwCursorPosition = { 20,8 };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << "|-----------------------------------|";
		dwCursorPosition = { 20,9 };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << "|Press(1) to continue.              |";
		dwCursorPosition = { 20,10 };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << "|Press(2) to exit.                  |";
		dwCursorPosition = { 20,11 };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << "|-----------------------------------|";

		int res;
		cin >> res;
		
		if (res == 1)
			return true;
		else
			return false;
	}
}

void Game_Manager::printPlayingOptions(COORD dwCursorPosition, int& playOption)
{
	cout.flush();
	system("CLS");

	while (!_kbhit())
	{
		
		cout.flush();

		dwCursorPosition = { 20,8 };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << "|-----------------------------------|";
		dwCursorPosition = { 20,9 };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << "|      Please choose Game Play:     |";
		dwCursorPosition = { 20,10 };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << "|(1) Play with default Board.       |";
		dwCursorPosition = { 20,11 };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << "|(2) Play with changing boards.     |";
		dwCursorPosition = { 20,12 };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << "|(3) Play by board name.            |";
		dwCursorPosition = { 20,13 };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << "|-----------------------------------|";

		int res;
		cin >> res;
		switch (res)
		{
		case(1):case(2):case(3):
		{
			playOption = res;
			return;
		}
		default:
		{
			cout << "Please enter a valid option !" << endl; 
		}
		}
		
		
	}
}

string Game_Manager::getBoardNameFromUser(COORD dwCursorPosition, FileHandler &files)
{
	string name;
	std::vector<string>  ValidfilesInDirectory = files.GetAllValidPacmanBoardFiles();
	std::vector<string> Not_ValidfilesInDirectory = files.GetAllNotValidPacmanBoardFiles();
	int numOfFiles = files.GetNumOfValidPacmanBoardFiles();
	int numOf_NOT_ValidFiles = files.GetNumOfInValidPacmanBoardFiles(); 

	int res;
	int i = 0, k = 0;
	system("CLS"); 

	if (numOfFiles == 0)
	{

		dwCursorPosition = { 5,11 };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << "There are no files in directory, you will be playing the default board."<< "\n";
		system("pause"); 
		return ""; 
	}

	dwCursorPosition = { 20,8 };
	SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
	cout << "|-----------------------------------|";
	dwCursorPosition = { 20,9 }; 
	SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
	cout << "Choose from the following:     "<< endl;

	for (i=0; i < numOfFiles; i++)
	{ 
		dwCursorPosition = { 20,short(10+i) };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << "("<<i+1<<")"<< ValidfilesInDirectory[i]<< "\n" << endl;
	}
	 

	if (numOf_NOT_ValidFiles > 0)
	{
		cout << "\n";
		dwCursorPosition = { 20,short(10 + i) };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << "The Following files are not valid:";
		
		for (k = 0; k < numOf_NOT_ValidFiles; k++)
		{
			dwCursorPosition = { 20,short(11 + i + k) };
			SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
			cout << "(-)" << Not_ValidfilesInDirectory[k] << "\n" << endl;
		}
	}

	dwCursorPosition = { 20,short(11+i+k) };
	SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
	cout << "|-----------------------------------|";

	cin >> res; 
	if (res <= numOfFiles)
	{
		return ValidfilesInDirectory[res-1];
	}
	else
	{
		return ValidfilesInDirectory[0];
	}

}

void Game_Manager::printLevelOptions(COORD dwCursorPosition, int& Level)
{
	system("CLS");

	cout.flush();
	while (!_kbhit())
	{
		cout.flush();

		dwCursorPosition = { 20,8 };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << "|-----------------------------------|";
		dwCursorPosition = { 20,9 };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << "|     Please choose game level:     |";
		dwCursorPosition = { 20,10 };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << "|(1) NOVICE                         |";
		dwCursorPosition = { 20,11 };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << "|(2) GOOD                           |";
		dwCursorPosition = { 20,12 };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << "|(3) BEST                           |";
		dwCursorPosition = { 20,13 };
		SetConsoleCursorPosition(corsor_for_Board, dwCursorPosition);
		cout << "|-----------------------------------|";

		int res;
		cin >> res;

		Level = res;
		return;
	}
}

void Game_Manager::printInstructions()
{
	system("CLS");
	cout << "\n\n";
	cout << "				  Goal:" << "\n\n";
	cout << "Guide the Pacman (@) around the board and eat -all- the little white dots " << "(" << char(249) << ")" << endl;
	cout << "while avoiding those nasty ghosts ($)." << endl;
	cout << "The game begins with 3 lives, every time a ghost catches you, a life is lost." << endl;
	cout << endl;
	cout << "				Controls:" << "\n\n";
	cout << "		" << "(" << "*" << ")" << "Left: A/a" << "	" << "	" << "(" << "*" ")" << "Right: D/d" << "\n\n";
	cout << "		" << "(" << "*" << ")" << "Up: W/w" << "	" << "	" << "(" "*" ")" << "Down: X/x" << "\n\n";
	cout << "		" << "(" "*" << ")" << "Press S/s to stop the Pacman at its place" << "\n\n";
	cout << "		" << "(" "*" << ")" << "Press Esc to pause the game." << endl;


	cout << "\n\n";
	cout << "	Pro tip:\n";
	cout << "	   Use the secret doors (They're there for a reason ;)" << endl << endl;


	system("pause");
}

bool Game_Manager::ShouldCreateFruit()
{
	int x = rand() % 10;	// Generating random index 
	if (x == 1)
	{
		return true;
	}
	return false;

}

void Game_Manager::RemoveFruit(bool SilencMode)
{

	gotoxy(this->corsor_for_Board, this->FruitPtr->GetXcord(), this->FruitPtr->GetYcord());
	int Index_ForBread_Crumbs = isCoordInArr({ short(this->FruitPtr->GetXcord()),short(this->FruitPtr->GetYcord()) }, this->BreadCrumbsArr->GetArr(), this->BreadCrumbsArr->GetCurrntlength());
	if(!SilencMode)
	{
	
		if (Index_ForBread_Crumbs != -1)
		{
			cout << char(249);
		}
		else
		{
			cout << " ";
		}
	}
	else
	{
		cout << "";
	}
	delete FruitPtr;
	FruitPtr = nullptr;
}

const Pacman& Game_Manager::getPacman()
{
	return *this->pacman;
}

int Game_Manager::PlayAutoGame(AutoMoves AutoMovesObj,bool SilenceMode)//1 for win 0 for losse -1 for runOutOfMoves
{
	if(!SilenceMode)
	{
		print_game_Board();
	}
	short Index_ForBread_Crumbs;
	int dir;
	bool Play;

	while (!AutoMovesObj.isAllMovesDone())
	{
		if (this->BreadCrumbsArr->GetCurrntlength() == 0)
		{
			//this->WinGame(false);
			return 1;
		}
		dir = AutoMovesObj.getPacmanMoves();
		this->pacman->move(dir,this->corsor_for_Board, SilenceMode?0:10);
		Index_ForBread_Crumbs = isCoordInArr({ short(this->pacman->GetXcord()),short(this->pacman->GetYcord()) }, this->BreadCrumbsArr->GetArr(), this->BreadCrumbsArr->GetCurrntlength());
		if (dir != 0 && Index_ForBread_Crumbs != -1)
		{
			this->pacman->set_Score(this->pacman->get_Score() + 1);
			this->BreadCrumbsArr->RemoveCordFromArr(Index_ForBread_Crumbs);
			if(!SilenceMode){ this->PrintPackmenStat();}
		}
		if (BreadCrumbsArr->GetCurrntlength() == 0)
		{
			return 1;
		}
		if (this->FruitPtr != nullptr)
		{
			if (this->pacman->GetXcord() == this->FruitPtr->GetXcord() && this->pacman->GetYcord() == this->FruitPtr->GetYcord())
			{
				this->pacman->AddFruitScore(FruitPtr->Getindicator());
				this->RemoveFruit(SilenceMode);
				if (!SilenceMode) { this->PrintPackmenStat(); }
			}
		}
		//this->checkForInput(&dir);
		if (this->IsPacmenInGhostLocation())
		{
			if (ResetGame(false, SilenceMode) == false)
			{
				return 0;
			}
		}


		if (Board::getNumOfGhost() >= 1)
		{
			//this->GhostArr[0]->move(this->corsor_for_Board, this->BreadCrumbsArr->GetArr(), this->BreadCrumbsArr->GetCurrntlength(), { (short)pacman->GetXcord(),(short)pacman->GetYcord() }, 100);
			this->GhostArr[0]->moveNOVICE(corsor_for_Board, this->BreadCrumbsArr->GetArr(), this->BreadCrumbsArr->GetCurrntlength(), SilenceMode ? 0 : 10, AutoMovesObj.getGhostMove(0));
			if (IsPacmenInGhostLocation())
			{
				if (ResetGame(false, SilenceMode) == false)
				{
					return 0;
				}
				//Sleep(600);
			}
			if (this->FruitPtr != nullptr)
			{
				if (this->GhostArr[0]->GetXcord() == this->FruitPtr->GetXcord() && this->GhostArr[0]->GetYcord() == this->FruitPtr->GetYcord())
				{
					this->RemoveFruit(SilenceMode);
				}
			}
			dir = AutoMovesObj.getPacmanMoves();
			this->pacman->move(dir, this->corsor_for_Board,SilenceMode ? 0 : 10);
			Index_ForBread_Crumbs = isCoordInArr({ short(this->pacman->GetXcord()),short(this->pacman->GetYcord()) }, this->BreadCrumbsArr->GetArr(), this->BreadCrumbsArr->GetCurrntlength());
			if (dir != 0 && Index_ForBread_Crumbs != -1)
			{
				this->pacman->set_Score(this->pacman->get_Score() + 1);
				this->BreadCrumbsArr->RemoveCordFromArr(Index_ForBread_Crumbs);
				if (!SilenceMode) { this->PrintPackmenStat(); }
			}
			if (this->FruitPtr != nullptr)
			{
				if (this->pacman->GetXcord() == this->FruitPtr->GetXcord() && this->pacman->GetYcord() == this->FruitPtr->GetYcord())
				{
					this->pacman->AddFruitScore(FruitPtr->Getindicator());
					this->RemoveFruit(SilenceMode);
					if (!SilenceMode) { this->PrintPackmenStat();}

				}
			}

			if (BreadCrumbsArr->GetCurrntlength() == 0)
			{
				return 1;
			}
			//this->checkForInput(&dir);
			if (IsPacmenInGhostLocation())
			{
				if (ResetGame(false, SilenceMode) == false)
				{
					return 0;
				}

				Sleep(600);
			}

		}
		if (Board::getNumOfGhost() >= 2)
		{
			this->GhostArr[1]->moveNOVICE(corsor_for_Board, this->BreadCrumbsArr->GetArr(), this->BreadCrumbsArr->GetCurrntlength(), SilenceMode ? 0 : 10, AutoMovesObj.getGhostMove(1));

			if (IsPacmenInGhostLocation())
			{
				if (ResetGame(false, SilenceMode) == false)
				{
					return 0;
				}
			}
			if (this->FruitPtr != nullptr)
			{
				if (this->GhostArr[1]->GetXcord() == this->FruitPtr->GetXcord() && this->GhostArr[1]->GetYcord() == this->FruitPtr->GetYcord())
				{
					this->RemoveFruit(SilenceMode);
				}
			}
			dir = AutoMovesObj.getPacmanMoves();
			this->pacman->move(dir, this->corsor_for_Board, SilenceMode ? 0 : 10);
			Index_ForBread_Crumbs = isCoordInArr({ short(this->pacman->GetXcord()),short(this->pacman->GetYcord()) }, this->BreadCrumbsArr->GetArr(), this->BreadCrumbsArr->GetCurrntlength());
			if (dir != 0 && Index_ForBread_Crumbs != -1)
			{
				this->pacman->set_Score(this->pacman->get_Score() + 1);
				this->BreadCrumbsArr->RemoveCordFromArr(Index_ForBread_Crumbs);
				if (!SilenceMode) { this->PrintPackmenStat(); }
			}
			if (this->FruitPtr != nullptr)
			{
				if (this->pacman->GetXcord() == this->FruitPtr->GetXcord() && this->pacman->GetYcord() == this->FruitPtr->GetYcord())
				{
					this->pacman->AddFruitScore(FruitPtr->Getindicator());
					this->RemoveFruit(SilenceMode);
					if (!SilenceMode) { this->PrintPackmenStat(); }

				}
			}

			if (BreadCrumbsArr->GetCurrntlength() == 0)
			{
				return 1;
			}
			if (IsPacmenInGhostLocation())
			{
				if (ResetGame(false, SilenceMode) == false)
				{
					return 0;
				}
			}

		}
		if (Board::getNumOfGhost() >= 3)
		{
			this->GhostArr[2]->moveNOVICE(corsor_for_Board, this->BreadCrumbsArr->GetArr(), this->BreadCrumbsArr->GetCurrntlength(), SilenceMode ? 0 : 10, AutoMovesObj.getGhostMove(2));
			if (IsPacmenInGhostLocation())
			{
				if (ResetGame(false, SilenceMode) == false)
				{
					return 0;
				}
			}
			if (this->FruitPtr != nullptr)
			{
				if (this->GhostArr[2]->GetXcord() == this->FruitPtr->GetXcord() && this->GhostArr[2]->GetYcord() == this->FruitPtr->GetYcord())
				{
					this->RemoveFruit(SilenceMode);
				}
			}
			dir = AutoMovesObj.getPacmanMoves();
			this->pacman->move(dir, this->corsor_for_Board, SilenceMode ? 0 : 10);
			Index_ForBread_Crumbs = isCoordInArr({ short(this->pacman->GetXcord()),short(this->pacman->GetYcord()) }, this->BreadCrumbsArr->GetArr(), this->BreadCrumbsArr->GetCurrntlength());
			if (dir != 0 && Index_ForBread_Crumbs != -1)
			{
				this->pacman->set_Score(this->pacman->get_Score() + 1);
				this->BreadCrumbsArr->RemoveCordFromArr(Index_ForBread_Crumbs);
				if (!SilenceMode) { this->PrintPackmenStat(); }
			}
			if (this->FruitPtr != nullptr)
			{
				if (this->pacman->GetXcord() == this->FruitPtr->GetXcord() && this->pacman->GetYcord() == this->FruitPtr->GetYcord())
				{
					this->pacman->AddFruitScore(FruitPtr->Getindicator());
					this->RemoveFruit(SilenceMode);
					if (!SilenceMode) { this->PrintPackmenStat(); }

				}
			}

			if (BreadCrumbsArr->GetCurrntlength() == 0)
			{
				return 1 ;
			}
			if (IsPacmenInGhostLocation())
			{
				
				if (ResetGame(false, SilenceMode) == false)
				{
					return 0;
				}
			}

		}
		if (Board::getNumOfGhost() >= 4)
		{
			this->GhostArr[3]->moveNOVICE(corsor_for_Board, this->BreadCrumbsArr->GetArr(), this->BreadCrumbsArr->GetCurrntlength(), SilenceMode ? 0 : 10, AutoMovesObj.getGhostMove(3));

			if (IsPacmenInGhostLocation())
			{
				
				if (ResetGame(false, SilenceMode) == false)
				{
					return 0;
				}
			}
			if (this->FruitPtr != nullptr)
			{
				if (this->GhostArr[3]->GetXcord() == this->FruitPtr->GetXcord() && this->GhostArr[3]->GetYcord() == this->FruitPtr->GetYcord())
				{
					this->RemoveFruit(SilenceMode);
				}
			}

			dir = AutoMovesObj.getPacmanMoves();
			this->pacman->move(dir, this->corsor_for_Board, SilenceMode ? 0 : 10);
			Index_ForBread_Crumbs = isCoordInArr({ short(this->pacman->GetXcord()),short(this->pacman->GetYcord()) }, this->BreadCrumbsArr->GetArr(), this->BreadCrumbsArr->GetCurrntlength());
			if (dir != 0 && Index_ForBread_Crumbs != -1)
			{
				this->pacman->set_Score(this->pacman->get_Score() + 1);
				this->BreadCrumbsArr->RemoveCordFromArr(Index_ForBread_Crumbs);
				if (!SilenceMode) { this->PrintPackmenStat(); }
			}
			if (this->FruitPtr != nullptr)
			{
				if (this->pacman->GetXcord() == this->FruitPtr->GetXcord() && this->pacman->GetYcord() == this->FruitPtr->GetYcord())
				{
					this->pacman->AddFruitScore(FruitPtr->Getindicator());
					this->RemoveFruit(SilenceMode);
					if (!SilenceMode) { this->PrintPackmenStat(); }

				}
			}

			if (BreadCrumbsArr->GetCurrntlength() == 0)
			{
				
				return 1;
			}
			if (IsPacmenInGhostLocation())
			{
				
				if (ResetGame(false, SilenceMode) == false)
				{
					return 0;
				}
			}

		}

		//fruit cration
		bool IsfruitAlive = AutoMovesObj.getFruitMove();
		bool RunGhostLoop = true;
		if (Fruit::GetCounter() == 0)
		{
			if (IsfruitAlive)
			{
				this->FruitPtr = new Fruit();
				FruitPtr->move(this->corsor_for_Board, this->BreadCrumbsArr->GetArr(), this->BreadCrumbsArr->GetCurrntlength(), SilenceMode?0:10);
				for (int i = 0; i < Board::getNumOfGhost() && RunGhostLoop; i++)
				{
					if (this->GhostArr[i]->GetXcord() == this->FruitPtr->GetXcord() && this->GhostArr[i]->GetYcord() == this->FruitPtr->GetYcord())
					{
						this->RemoveFruit(SilenceMode);
						RunGhostLoop = false; 
					}

				}
			}
		}
		else
		{
			if (FruitPtr != nullptr && FruitPtr->GetTimer() == this->NumOfMovesOfFruitPtr)
			{
				RemoveFruit(SilenceMode);
			}
			else
			{
				FruitPtr->move(this->corsor_for_Board, this->BreadCrumbsArr->GetArr(), this->BreadCrumbsArr->GetCurrntlength(),SilenceMode?0:10);
				for (int i = 0; i < Board::getNumOfGhost() && RunGhostLoop; i++)
				{
					if (this->GhostArr[i]->GetXcord() == this->FruitPtr->GetXcord() && this->GhostArr[i]->GetYcord() == this->FruitPtr->GetYcord())
					{
						this->RemoveFruit(SilenceMode);
						RunGhostLoop = false; 
					}

				}
			}
		}

	}

	return -1;

}



const bool Game_Manager::CheckResultFile(const string ResFile,bool WinLose)
{
	string winOrLose = WinLose ? "Win" : "Lose";
	string NumOfSteps = "Num_Of_Steps: ";
	NumOfSteps +=to_string(this->pacman->Get_NumOfSteps());
	string Location = "Location: ";
	Location += "{" + to_string(this->pacman->GetXcord()) + "," + to_string(this->pacman->GetYcord()) + "}";
	fstream File;
	
	File.open(ResFile, ios::in);
	string* mat = new string[3];
	int index = 0;
	
	if (!File) { cout << "Could not open resultFile file : " << ResFile << endl; return false; }
	while (getline(File, mat[index]))
	{
		++index;
	}
	File.close();
	if (index !=3) 
	{
		cout << "Result File not valid" << endl; 
		return false;
	}
	if (winOrLose != mat[0] || NumOfSteps != mat[1] || Location != mat[2])
	{
		if (winOrLose != mat[0])
			cout << "win or lose issue" << endl; 
		if (NumOfSteps != mat[1])
			cout << "num of steps issue" << endl;
		if(Location != mat[2])
			cout << "location issue" << endl;

		return false;
	}
	return true;
	



		








}