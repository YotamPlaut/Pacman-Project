#include "AutoMoves.h"
#include <iostream>
#include <fstream>
#include <ctype.h>

using namespace std;


AutoMoves::AutoMoves(std::string fileName)
{
	fstream File;
	File.open(fileName, ios::in);
	int index = 0;
	string* mat = new string[100];
	int numOfRows = 0;
	if (!File) { cout << "Could not open file : " << fileName << endl; exit(1); }
	else
	{
		while (getline(File, mat[index]))
		{
			numOfRows++;
			++index;
		}
	}
	matToMoves(mat,numOfRows);

	
}

int AutoMoves::getPacmanMoves()
{
	if (pacmanIndex == pacmanMoves.size())
	{
		isDonePacmanMoves = true;
		return 0;
	}
	return pacmanMoves[pacmanIndex++];
}
int AutoMoves::getGhostMove(int ghostIndex)
{
	if (ghostsIndices[ghostIndex] == ghostMoves[ghostIndex].size())
	{
		isDoneGhostMoves[ghostIndex] = true;
		return 0;
	}
	else
	{
		int currentMove = ghostsIndices[ghostIndex];
		ghostsIndices[ghostIndex]++;
		return ghostMoves[ghostIndex][currentMove];
	}

}
bool AutoMoves::getFruitMove()
{
	if (fruitIndex == fruitMoves.size())
	{
		isDoneFruitMoves = true;
		return 0;
	}
	return fruitMoves[fruitIndex++];
}

bool AutoMoves::isAllMovesDone()
{
	bool _isDoneGhostsMoves = false;
	if (std::find(isDoneGhostMoves.begin(), isDoneGhostMoves.end(), false) == isDoneGhostMoves.end())
	{
		_isDoneGhostsMoves = true;
	}
	return (_isDoneGhostsMoves && this->isDoneFruitMoves && this->isDonePacmanMoves); // return true if all moves of all creatures are done. 
}



void AutoMoves::matToMoves(string* movesMat,int _NumOfRows)
{
	//int size = movesMat->size(); // check why its a big number. 
	char creature;
	int numOfGhosts =Board::getNumOfGhost(); 

	for (int i = 0; i <_NumOfRows; i++)
	{// each line is steps when the first Letter indicates the creature; 
		
		creature = movesMat[i][0];

		switch (creature)
		{
		case('P'): // get Pacman moves.
			stringToMovesVector_pacman(movesMat[i]);
			break;

		case('G'): // get ghost moves.
			int j;
			for (j = i; j < numOfGhosts + i; j++)
			{
				stringToMovesVector_ghost(movesMat[j]);
			}
			i = (j - 1);
			break;

		case('F'): // get fruit moves. 
			stringToMovesVector_fruit(movesMat[i]);
			break;
		
		default:
			continue;
		}

	}
}

void AutoMoves::stringToMovesVector_pacman(std::string movesString)
{
	// 0 = S
	// 1 = L
	// 2 = R 
	// 3 = U
	// 4 = D
	int stringSize = movesString.length();
	char dirByLetter;
	int amountOfMovesByNum;

	for (int i = 2; i < stringSize - 1; i++)
	{
		int j = 1;
		string numOfMoves_temp = "";
		dirByLetter = movesString[i];

		while (isdigit(movesString[(long)i + j]))
		{
			numOfMoves_temp += movesString[(long)i + j];
			j++;
		}
		if ((i + j) < stringSize - 1)
		{
			i += (j - 1);
		}
		if (numOfMoves_temp == "")
		{
			cout << "We found an issue with your steps file in the Pacman steps (no number of steps in index " << i + j << ").\nPlease fix the issue and run the program again." << endl;
			exit(1);
		}
		for (int z = 0; z < numOfMoves_temp.length(); z++) // input check. 
		{
			if (!isdigit(numOfMoves_temp[z]) || (numOfMoves_temp == ""))
			{
				cout << "We found an issue with your steps file in the Pacman steps (no number of steps in index " << i + j << ").\n Please fix the issue and run the program again." << endl;
				exit(1);
			}
			else
				amountOfMovesByNum = stoi(numOfMoves_temp);
		}

		switch (dirByLetter)
		{
		case('R'):
			this->pacmanMoves.insert(pacmanMoves.end(), amountOfMovesByNum, 2);
			break;

		case('L'):
			this->pacmanMoves.insert(pacmanMoves.end(), amountOfMovesByNum, 1);
			break;

		case('D'):
			this->pacmanMoves.insert(pacmanMoves.end(), amountOfMovesByNum, 4);
			break;

		case('U'):
			this->pacmanMoves.insert(pacmanMoves.end(), amountOfMovesByNum, 3);
			break;

		case('S'):
			this->pacmanMoves.insert(pacmanMoves.end(), amountOfMovesByNum, 0);
			break;
		}
	}
}

void AutoMoves::stringToMovesVector_fruit(std::string movesString)
{
	int stringSize = movesString.length();
	char stateByChar, amountofMovesByChar;
	int amountofMovesByNum;

	for (int i = 2; i < stringSize - 1; i++)
	{
		stateByChar = movesString[i];
		int j = 1;
		string numOfMoves_temp = "";

		while (isdigit(movesString[(long)i + j]))
		{
			numOfMoves_temp += movesString[(long)i + j];
			j++;
		}
		if ((i + j) < stringSize - 1)
		{
			i += (j - 1);
		}
		if (numOfMoves_temp == "")
		{
			cout << "We found an issue with your steps file in the Fruit steps (no number of steps in index " << i + j << ").\nPlease fix the issue and run the program again." << endl;
			exit(1);
		}
		for (int z = 0; z < numOfMoves_temp.length(); z++) // input check. 
		{
			if (!isdigit(numOfMoves_temp[z]) || (numOfMoves_temp == ""))
			{
				cout << "We found an issue with your steps file in the Fruit steps (no number of steps in index " << i + j << ").\n Please fix the issue and run the program again." << endl;
				exit(1);
			}
			else
				amountofMovesByNum = stoi(numOfMoves_temp);
		}

		switch (stateByChar)
		{
		case('B'):
			this->fruitMoves.insert(fruitMoves.end(), amountofMovesByNum, 1);
			break;

		case('D'):
			this->fruitMoves.insert(fruitMoves.end(), amountofMovesByNum, 0);
			break;
		}
	}

}

void AutoMoves::stringToMovesVector_ghost(std::string movesString)
{
	int stringSize = movesString.length();
	char dirByLetter;
	int amountOfMovesByNum;
	vector<int> temp;

	for (int i = 3; i < stringSize - 1; i++)
	{
		int j = 1;
		string numOfMoves_temp = "";
		dirByLetter = movesString[i];

		while (isdigit(movesString[(double)(i + j)]))
		{
			numOfMoves_temp += movesString[(double)(i + j)];
			j++;
		}
		if ((i + j) < stringSize - 1)
		{
			i += (j - 1);
		}
		if (numOfMoves_temp == "")
		{
			cout << "We found an issue with your steps file in one of the ghosts steps (no number of steps in index " << i + j << ").\nPlease fix the issue and run the program again." << endl;
			exit(1);
		}
		for (int z = 0; z < numOfMoves_temp.length(); z++) // input check. 
		{
			if (!isdigit(numOfMoves_temp[z]) || (numOfMoves_temp == ""))
			{
				cout << "We found an issue with your steps file in one of the ghosts steps (no number of steps in index " << i + j << ").\n Please fix the issue and run the program again." << endl;
				exit(1);
			}
			else
				amountOfMovesByNum = stoi(numOfMoves_temp);
		}


		switch (dirByLetter)
		{
		case('R'):
			temp.insert(temp.end(), amountOfMovesByNum, 2);
			break;

		case('L'):
			temp.insert(temp.end(), amountOfMovesByNum, 1);
			break;

		case('D'):
			temp.insert(temp.end(), amountOfMovesByNum, 4);
			break;

		case('U'):
			temp.insert(temp.end(), amountOfMovesByNum, 3);
			break;

		case('S'):
			temp.insert(temp.end(), amountOfMovesByNum, 0);
			break;
		}
	}
	this->ghostMoves.push_back(temp);
}



// Move functions are pushing directions into object steps Vector. 
// At the end of every playGame functions, all vectors are being collected and moved to format. 
// when the use closes the game completely, the vector are being outported to a text file. 
