#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
using std::cout; using std::cin;
using std::endl; using std::string;
using std::filesystem::directory_iterator;

// A class to manage the file loading from the directory. 

class FileHandler
{
private:
	static int FileBoardIndex; // counts in which valid file we are at a current time. 
	std::vector<string> ValidPacmanBoardFiles; // vec holding all the valid pacman files 
	std::vector<string> NotValidPacmanBoardFiles; // // vec holding all the  NOT_valid pacman files 
	std::vector<string>PacmanStepFiles; // vec holding all the step files from directory. 
	std::vector<string>PackemResultFile; // vec holding all the results from directory. 
	void GetOnlyPackmenFiles(std::vector<string> arr); // from a vec holding all file types, get only the pacman files. 
	void SetBoardFiles(std::vector<string> arr);// intializing allValidPacmanBoardFiles  
	void setPacmanStepAndResultFiles(std::vector<string>arr); // intializing pacman steps and results files. 
	bool IsBoardFileValid(const string fileName); // checks if a board in valid. 


public:
	FileHandler();
	string GetSingleBoardFile(); 

	// GETTERS
	std::vector<string> GetAllValidPacmanBoardFiles() {
		return ValidPacmanBoardFiles;
	}

	short GetNumOfValidPacmanBoardFiles() {return (short)ValidPacmanBoardFiles.size();}

	std::vector<string> GetAllNotValidPacmanBoardFiles() {
		return NotValidPacmanBoardFiles;
	}
	short GetNumOfInValidPacmanBoardFiles() {return (short)NotValidPacmanBoardFiles.size();}

	string GetStepFile(string boardName);

	string GetResultFile(string boardName);

};

