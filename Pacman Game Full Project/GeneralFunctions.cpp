#include "GeneralFunctions.h"


void playChangingBoards(FileHandler files, int level,bool SaveMood)
{
	int numOfBoards = files.GetNumOfValidPacmanBoardFiles();
	Pacman P; // obejct to move from board to board. 

	for (int i = 0; i < numOfBoards; i++)
	{
		Game_Manager Game(files.GetSingleBoardFile(), P, level);

		// continue for next board when PlayGame = true. 
		// Else leave the game back to main menu.  

		if (!Game.PlayGame(SaveMood))
		{
			break;
		}
		else
		{
			if (i == numOfBoards - 1)
			{
				cout << "You have finished all boards successfully !! Well Done";
				system("pause");
				break;
			}
			if (Game_Manager::printChooseToContinue())
			{
				P = Game.getPacman(); // operator (=) of Pacman class. 
				continue;
			}
			else
			{
				break;
			}

		}


	}
	system("CLS");
}


void playRegularGame(bool SaveMood)
{
	FileHandler filesHandel;
	int gameLevel, PlayOption;
	string BoardName;
	srand(time(0));
	bool PlayGame = true;
	
	Game_Manager* newGame = nullptr;

	while (PlayGame)
	{
		PlayGame = Game_Manager::mainMenu(gameLevel, PlayOption, BoardName, filesHandel);
		if (!PlayGame)
		{
			break;
		}


		switch (PlayOption)
		{

			case(1): // Play default board; 
			{
				newGame = new Game_Manager(gameLevel);
				newGame->PlayGame(SaveMood);
				break;
			}
			case(2): // Play with changing boards. 
			{
				playChangingBoards(filesHandel, gameLevel,SaveMood);
				break;
			}
			case(3): // Play by choosing a board name from the directory. 
			{
				if (BoardName == "")
				{
					newGame = new Game_Manager(gameLevel);
					newGame->PlayGame(SaveMood);
				}
				else
				{
					newGame = new Game_Manager(BoardName, gameLevel);
					newGame->PlayGame(SaveMood);
				}
				break;
			}
		}

		if(newGame)
		{
			delete newGame;
		}
		
	}
	system("CLS");
	cout << "\n\n\nThank you for playing, hope to see you again soon\n\n\n";

}



void PlayAutoGame(bool SilenceMood)
{
	FileHandler files;
	int numOfBoards = files.GetNumOfValidPacmanBoardFiles();
	Pacman P; // obejct to move from board to board. 
	for(int i=0;i<numOfBoards;i++)
	{
		system("CLS");
		string BoardFile = files.GetSingleBoardFile();
		string StepFile = files.GetStepFile(BoardFile);
		string ResultFile = files.GetResultFile(BoardFile);
		if(StepFile=="")
		{
			cout << "We couldnt find step file correspand to the board:" << BoardFile <<"\n" << endl;
			continue;
		}
		else
		{
			Game_Manager Game(BoardFile,P,1);
			AutoMoves AutoMove(StepFile);
			system("CLS");
			cout << "Runing Step file name: " << StepFile <<"\n"<< endl;
			
			system("pause"); 
			int GameResult=Game.PlayAutoGame(AutoMove,SilenceMood);
			system("CLS");
			if(GameResult==1)//the game ends with a win, check the result file and contiinew to next file
			{
				P = Game.getPacman();
				if(ResultFile!="")
				{
					cout << "cheking result file" << endl;
					Game.CheckResultFile(ResultFile, 1) ? cout << "Test Succeed" : cout << "Test Failed";
					cout << endl; 
					system("pause"); 
				}
				else
				{
					cout << "didnt find result file" << endl;
				}

			}
				
			else if(GameResult==0)//the games ends with a lose.check the result file and exit from the functiom
			{
				if (ResultFile != "")
				{
					cout << "cheking result file" << endl;
					Game.CheckResultFile(ResultFile,0) ? cout << "Test Succeed" : cout << "Test Failed";
					cout << endl;
				}
				else
				{
					cout << "didnt find result file" << endl;
				}
				return;
				
			}
			else if (GameResult == -1)//the game ends becuase the end of moves in step file, print a proper message ad exit
			{
				cout << "we run all the moves  in the step file, but the pacmen didn't win or die\n" << endl;
				return;
			}
			else//no reson to get here
			{
				cout<<"sonthing wird happend";
			}
		}
	}

	cout << "Done runing all step files in directory";


}


void SetGameMode(int argc, char** argv, bool& SaveMode, bool& AutoPlay, bool& SilanceMood)
{
	if (argc <= 1)
	{
		AutoPlay = false;
		SaveMode = false;
		SilanceMood = false;
	}
	if (argc > 1)
	{
		if ((strcmp(argv[1], "-load") == 0))
		{
			AutoPlay = true;
			SaveMode = false;
			if (argc > 2 && strcmp(argv[2], "-silent") == 0)
			{
				SilanceMood = true;
			}
			else
			{
				SilanceMood = false;
			}
		}
		else if ((strcmp(argv[1], "-save") == 0))
		{
			AutoPlay = false;
			SaveMode = true;
			SilanceMood = false;
		}
		else
		{
			AutoPlay = false;
			SaveMode = false;
			SilanceMood = false;
		}
	}


}