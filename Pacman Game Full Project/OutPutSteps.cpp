#include "OutPutSteps.h"

using namespace std; 
vector<string> OutPutSteps::stepsVec_OfStrings_forOutPut;

void OutPutSteps::printStepsToFile()
{
	string boardNameForStepsFile = Board::GetBoardName(); 
	boardNameForStepsFile += ".steps.txt";
	ofstream stepsFile(boardNameForStepsFile);
	if (stepsFile.is_open())
	{

		for (int i = 0; i < stepsVec_OfStrings_forOutPut.size(); i++)
		{
			stepsFile << stepsVec_OfStrings_forOutPut[i] << endl;
		}
			stepsFile.close();
	}
	else
	{
		cout << "could not create steps file !" << endl;
	}

}

void OutPutSteps::stepVectorsToMat(const std::vector<int> pacmanVec, const std::vector<vector<int>> ghostVec, const std::vector<int> fruitVec)
{
	vector<string> stringsVec; 
	string pacmanStepsString = pacmanStepsVecToString(pacmanVec);
	stringsVec.push_back(pacmanStepsString); 

	int numOfGhosts = Board::getNumOfGhost(); 
	string tempGhostString; 
	for (int i = 0; i < numOfGhosts; i++)
	{
		tempGhostString = ghostStepsVecToString(ghostVec[i], i); 
		stringsVec.push_back(tempGhostString); 
	}

	string fruitStepsString = fruitStepsVecToString(fruitVec); 
	stringsVec.push_back(fruitStepsString); 
	
	stepsVec_OfStrings_forOutPut = stringsVec; 

}

char OutPutSteps::dirCharFromVec(int val)
{
	switch (val)
	{
	case(2):
		return 'R'; 

	case(1):
		return 'L'; 

	case(4):
		return 'D'; 

	case(3):
		return 'U'; 

	case(0):
		return 'S'; 
	}
}

string OutPutSteps::pacmanStepsVecToString(vector<int> vec)
{
	
	int sizeOfPacmanVec = vec.size(); // 
	int numOfSteps;
	string tempString;
	tempString += "P ";
	
	if (vec.size() == 1)
	{
		char dirByChar = OutPutSteps::dirCharFromVec(vec[0]);
		tempString.push_back(dirByChar);
		tempString.push_back(1);
	}
	else if (vec.size() == 0)
	{
		return  tempString;
	}
	else
	{
		
		int index = 0; 
		int k = 1;
		int counter = 1;
		char dirByChar; 
		while (index < sizeOfPacmanVec-1)
		{
			dirByChar = OutPutSteps::dirCharFromVec(vec[index]);
			k = 1;
			counter = 1; 

			while ((index + k) < sizeOfPacmanVec)
			{
				if (vec[index + k] == vec[index])
				{
					counter++; 
					k++; 
					if ((index + k) == sizeOfPacmanVec)
					{
						tempString.push_back(dirByChar);
						string tempChar = to_string(counter); 
						tempString += tempChar;
						return tempString;
					}
				}
				else 
				{
					tempString.push_back(dirByChar);
					string tempChar = to_string(counter);
					tempString += tempChar;
					index = index + k; 
					if (index == sizeOfPacmanVec - 1)
					{
						dirByChar = OutPutSteps::dirCharFromVec(vec[index]);
						tempString.push_back(dirByChar);
						tempString.push_back('1');
					}
					break;
				}
			}

		}
		return tempString;
	}
}

string OutPutSteps::ghostStepsVecToString(vector<int> vec, int ghostNum)
{
	int size = vec.size();
	int numOfSteps;
	string tempString;
	tempString += 'G';
	char numOfGhost = (ghostNum + 1) + '0'; 
	tempString += numOfGhost;
	tempString += ' ';

	
	if (vec.size() == 1)
	{
		char dirByChar = OutPutSteps::dirCharFromVec(vec[0]);
		tempString.push_back(dirByChar);
		tempString.push_back(1);
	}
	else if (vec.size() == 0)
	{
		return  tempString;
	}
	else
	{
		int i = 0;
		while (i < size - 1)
		{
			numOfSteps = 0;
			char dirByChar = OutPutSteps::dirCharFromVec(vec[i]);

			if (i < size - 1 && vec[i] == vec[i + 1])
			{
				
				while (i < size - 1 && vec[i] == vec[i + 1])
				{
					numOfSteps++;
					i++;
				}
				numOfSteps++;

				tempString.push_back(dirByChar);
				string tempChar = to_string(numOfSteps);
				tempString += tempChar;
			}
			else if (i < size - 1 && vec[i] != vec[i + 1])
			{
				tempString.push_back(dirByChar);
				tempString += '1'; 
			}
			if (i < size - 1)
			{
				i++;
			}
		}
	}

	return tempString;
}

string OutPutSteps::fruitStepsVecToString(vector<int> vec)
{
	int size = vec.size(); 
	int numOfSteps;
	string tempString;
	tempString+= "F ";

	if (vec.size() == 1)
	{
		char dirByChar = OutPutSteps::dirCharFromVec(vec[0]);
		tempString.push_back(dirByChar);
		tempString.push_back(1);
	}
	else if (vec.size() == 0)
	{
		return  tempString;
	}
	else
	{
		int i = 0;
		while (i < size - 1)
		{
			numOfSteps = 0;
			char dirByChar = vec[i] ? 'B' : 'D';

			if (i < size - 1 && vec[i] == vec[i + 1])
			{
				while (i < size - 1 && vec[i] == vec[i + 1])
				{
					numOfSteps++;
					i++;
				}
				numOfSteps++;

				tempString.push_back(dirByChar);
				string tempChar = to_string(numOfSteps);
				tempString += tempChar;
			}
			if (i < size - 1)
			{
				i++;
			}
		}
	}

	return tempString;

}

