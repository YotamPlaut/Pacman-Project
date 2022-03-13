#pragma once
#include <vector>
#include <string>
#include "Game_Manager.h"
#include <ostream>


class OutPutSteps
{
private:

	static vector<string> stepsVec_OfStrings_forOutPut; 
	
public:

	static void resetVector() { stepsVec_OfStrings_forOutPut.clear(); }
	static void printStepsToFile();
	static void stepVectorsToMat(const std::vector<int> pacmanVec, const std::vector<vector<int>> ghostVec,const std::vector<int> fruitVec);

	static char dirCharFromVec(int val); 
	static string pacmanStepsVecToString(vector<int> vec);
	static string ghostStepsVecToString(vector<int> vec, int ghostNum);
	static string fruitStepsVecToString(vector<int> vec);

};

