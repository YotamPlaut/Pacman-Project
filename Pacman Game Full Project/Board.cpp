#include "Board.h"

COORD Board::pacmanStartLocation;

COORD* Board::ghostsStartLocation;

int Board::numOfGhost;


int Board::secretDoorsArrSize;
COORD* Board::SecterDoorsArry;

COORD* Board::BoardInnerWalls;
int Board::BoardInnerWallsArrSize;

COORD Board::TOPLEFT;
COORD Board::TOPRIGHT;
COORD Board::BOTTOMLEFT;
COORD Board::BOTTOMRIGHT;

COORD Board::LegendLocation;

COORD* Board::FruitPossibleLocation;
int Board::FruitPossibleLocationArrSize;

COORD* Board:: BreadCrumsLocation;
int Board:: BreadCrumsLocationArrSize;

string Board::BoardName;



bool Board::IsCordIninnerWalls(short x,short y)
{
	for (int i = 0; i < BoardInnerWallsArrSize; i++)
	{
		if (x == BoardInnerWalls[i].X && y == BoardInnerWalls[i].Y)
		{
			return true;
		}
	}
	return false;
}

// C'tor from creating a default board.
Board::Board()
{

	//Pckmen Part
	pacmanStartLocation = { 8,10 };

	this->BoardName = "Default_Board";


	//Ghost part
	numOfGhost = 2;
	ghostsStartLocation = new COORD[numOfGhost];	
	ghostsStartLocation[0] = {12,10};
	ghostsStartLocation[1] = {35,18};
	




	//4 points of game
	TOPLEFT = { 5,5 };
	TOPRIGHT = { 40,5 };
	BOTTOMLEFT = { 5,23 };
	BOTTOMRIGHT = { 40,23 };
	

	//Legend 
	LegendLocation = {12,0};

	//Fruit StartLocation;
	FruitPossibleLocationArrSize = 4;
	FruitPossibleLocation = new COORD[FruitPossibleLocationArrSize];
	FruitPossibleLocation[0] = {15,7};
	FruitPossibleLocation[1] = {19,9};
	FruitPossibleLocation[2] = {16,19};
	FruitPossibleLocation[3] = {24,17};
	//FruitPossibleLocation[4] = { 10,2 };
	//FruitPossibleLocation[5] = { 10,4 };
	//FruitPossibleLocation[6] = { 10,8 };
	//FruitPossibleLocation[7] = { 10,14 };
	//FruitPossibleLocation[8] = { 25,2 };
	//FruitPossibleLocation[9] = { 25,4 };
	//FruitPossibleLocation[10] = { 25,8 };
	//FruitPossibleLocation[11] = { 25,14 };
	//FruitPossibleLocation[12] = { 32,2 };
	//FruitPossibleLocation[13] = { 32,4 };
	//FruitPossibleLocation[14] = { 32,8 };
	//FruitPossibleLocation[15] = { 32,14 };


	//InnerWals
	BoardInnerWallsArrSize = 90;
	BoardInnerWalls = new COORD[BoardInnerWallsArrSize];

	BoardInnerWalls[0] = { 10, 8};
	BoardInnerWalls[1] = {11,8};
	BoardInnerWalls[2] = { 12,8 };
	BoardInnerWalls[3] = { 13,8 };
	BoardInnerWalls[4] = { 14,8 };
	BoardInnerWalls[5] = { 15,8 };
	BoardInnerWalls[6] = { 16,8 };
	BoardInnerWalls[7] = { 17,8 };
	BoardInnerWalls[8] = { 18,8 };
	BoardInnerWalls[9] = { 19,8 };

	
	BoardInnerWalls[10] = { 26,8 };
	BoardInnerWalls[11] = { 27,8 };
	BoardInnerWalls[12] = { 28,8 };
	BoardInnerWalls[13] = { 29,8 };
	BoardInnerWalls[14] = { 30,8 };
	BoardInnerWalls[15] = { 31,8 };
	BoardInnerWalls[16] = { 32,8 };
	BoardInnerWalls[17] = { 33,8 };
	BoardInnerWalls[18] = { 34,8 };
	BoardInnerWalls[19] = { 35,8 };


	BoardInnerWalls[20] = {10,20};
	BoardInnerWalls[21] = { 11,20 };
	BoardInnerWalls[22] = { 12,20 };
	BoardInnerWalls[23] = { 13,20 };
	BoardInnerWalls[24] = { 14,20};
	BoardInnerWalls[25] = { 15,20 };
	BoardInnerWalls[26] = { 16,20 };
	BoardInnerWalls[27] = { 17,20 };
	BoardInnerWalls[28] = { 18,20 };
	BoardInnerWalls[29] = { 19,20 };


	BoardInnerWalls[30] = {26,20 };
	BoardInnerWalls[31] = {26,20 };
	BoardInnerWalls[32] = { 27,20 };
	BoardInnerWalls[33] = { 28,20 };
	BoardInnerWalls[34] = { 29,20 };
	BoardInnerWalls[35] = { 30,20 };
	BoardInnerWalls[36] = { 31,20 };
	BoardInnerWalls[37] = { 32,20 };
	BoardInnerWalls[38] = { 33,20 };
	BoardInnerWalls[39] = { 34,20 };
	BoardInnerWalls[40] = { 35,20 };


	BoardInnerWalls[41] = { 35,11};
	BoardInnerWalls[42] = { 35,12};
	BoardInnerWalls[43] = { 35,13 };
	BoardInnerWalls[44] = { 35,14 };
	BoardInnerWalls[45] = { 35,15 };
	BoardInnerWalls[46] = { 35,16 };
	BoardInnerWalls[47] = { 35,17 };


	BoardInnerWalls[48] = { 10,11 };
	BoardInnerWalls[49] = { 10,12 };
	BoardInnerWalls[50] = { 10,13 };
	BoardInnerWalls[51] = { 10,14 };
	BoardInnerWalls[52] = { 10,15 };
	BoardInnerWalls[53] = { 10,17 };
	BoardInnerWalls[54] = { 10,16 };
	BoardInnerWalls[55] = { 10,17};

	BoardInnerWalls[56] = { 20,12 };
	BoardInnerWalls[57] = { 20,13 };
	BoardInnerWalls[58] = { 20,14 };
	BoardInnerWalls[59] = { 20,15 };
	BoardInnerWalls[60] = { 21,12 };
	BoardInnerWalls[61] = { 21,13 };
	BoardInnerWalls[62] = { 21,14 };
	BoardInnerWalls[63] = { 21,15 };
	BoardInnerWalls[64] = { 21,15 };
	BoardInnerWalls[65] = { 22,12 };
	BoardInnerWalls[66] = { 22,13 };
	BoardInnerWalls[67] = { 22,13 };
	BoardInnerWalls[68] = { 22,14 };
	BoardInnerWalls[69] = { 22,15 };
	BoardInnerWalls[70] = { 23,12 };
	BoardInnerWalls[71] = { 23,13 };
	BoardInnerWalls[72] = { 23,14 };
	BoardInnerWalls[73] = { 23,14 };
	BoardInnerWalls[73] = { 23,15 };
	BoardInnerWalls[74] = { 24,12 };
	BoardInnerWalls[75] = { 24,13 };
	BoardInnerWalls[76] = { 24,14 };
	BoardInnerWalls[77] = { 24,15 };
	BoardInnerWalls[78] = { 25,12 };
	BoardInnerWalls[79] = { 25,13 };
	BoardInnerWalls[80] = { 25,13 };
	BoardInnerWalls[81] = { 25,13 };
	BoardInnerWalls[82] = { 25,14 };
	BoardInnerWalls[83] = { 25,15 };
	BoardInnerWalls[84] = { 20,16 };
	BoardInnerWalls[85] = { 21,16 };
	BoardInnerWalls[86] = { 22,16 };
	BoardInnerWalls[87] = { 23,16 };
	BoardInnerWalls[88] = { 24,16 };
	BoardInnerWalls[89] = { 25,16 };
	


	//secret Doors
	secretDoorsArrSize = 8;
	SecterDoorsArry = new COORD[secretDoorsArrSize];
	SecterDoorsArry[0] = { 15,5 };
	SecterDoorsArry[1] = { 30,5};
	SecterDoorsArry[2] = { 15,23};
	SecterDoorsArry[3] = { 30,23 };
	SecterDoorsArry[4] = { 5,9};
	SecterDoorsArry[5] = {40,9};
	SecterDoorsArry[6] = {5,18};
	SecterDoorsArry[7] = {40,18};



	//breadCrums
	int counter=0;
	vector<COORD> arr;
	for(int i=TOPLEFT.Y+1;i<BOTTOMLEFT.Y;i++)
	{
		for(int j= TOPLEFT.X + 1; j < TOPRIGHT.X;j++)
		{
			if(!IsCordIninnerWalls(short(j),short(i)))
			{
				counter++;
				arr.push_back({ short(j),short(i) });
			}
		}
	}
	this->BreadCrumsLocationArrSize = counter;
	this->BreadCrumsLocation = new COORD[BreadCrumsLocationArrSize];
	for(int i=0;i< BreadCrumsLocationArrSize;i++)
	{
		BreadCrumsLocation[i] = arr[i];
	}

}

// C'tor from creating a board from a given file name. 
Board::Board(const string fileName)
{
	ifstream file;
	string* mat = new std::string[100];
	file.open(fileName);
	if (!file)
	{
		std::cout << "Bad";
	}
	int counter = 0;
	while (getline(file, mat[counter]))
	{
		++counter;
	}
	file.close();

	SetFourpoints(mat, counter);
	SetGhostLocationAndPakmenAndLegend(mat, counter);
	SetInnerWallsAndFruitLocations(mat, counter);
	SetSecretDors(mat, counter);
	SetBreadCrumsArry(mat);
	file.close();
	

	string _BoardName;
	int index = 0;
	while (fileName[index] != '.' && index <= fileName.size())
	{
		_BoardName += fileName[index];
		index++;
	}
	this->BoardName = _BoardName;

}


void Board::SetFourpoints(string* mat,int Size)
{
	string::iterator it;
	bool Loop = true;
	short counter;
	for (int i = 0; i <= Size && Loop; i++)
	{
		counter = 0;
		for (it = mat[i].begin(); it != mat[i].end() && Loop; it++)
		{
			if(*it=='#')
			{
				TOPLEFT = {counter,(short)i};
				Loop = false;
			}
			counter++;
		}
	}
	
	Loop = true;


	for (int i = Size-1; i>=0 && Loop; i--)
	{
		size_t counter = mat[i].length();
		for (it = mat[i].end()-1; it != mat[i].begin() && Loop; it--)
		{
			if (*it == '#')
			{
				BOTTOMRIGHT = {(short)counter,(short)i};
				Loop = false;
			}
			counter--;
		}
	}
	TOPRIGHT = {BOTTOMRIGHT.X,TOPLEFT.Y};
	BOTTOMLEFT = {TOPLEFT.X,BOTTOMRIGHT.Y};
}

void Board::SetGhostLocationAndPakmenAndLegend(string* mat, int Size)
{
	string::iterator it;
	vector<COORD> Ghostarr;
	int Ghostcounter = 0;
	short Colindex = 0;
	for (int i = 0; i <= Size; i++)
	{
		Colindex = 0;
		for (it = mat[i].begin(); it != mat[i].end(); it++)
		{
			if (*it == '$')
			{
				Ghostcounter++;
				Ghostarr.push_back({ Colindex,(short)i});
			}
			if(*it=='@')
			{
				pacmanStartLocation = { Colindex,(short)i};
			}
			if(*it=='&')
			{
				LegendLocation= { Colindex,(short)i };
			}

			Colindex++;
		}
	}

	numOfGhost = Ghostcounter;
	ghostsStartLocation = new COORD[Ghostcounter];
	for(int i=0;i<Ghostcounter;i++)
	{
		ghostsStartLocation[i].X = Ghostarr[i].X;
		ghostsStartLocation[i].Y = Ghostarr[i].Y;

	}


	





}

void Board::SetInnerWallsAndFruitLocations(string* mat, int Size)
{	
	vector<COORD>arrInnerWalls;
	int InnerWallsCounter=0;
	
	vector<COORD>FruitLocation;
	int FruitLocationCounter = 0;


	for(int i=TOPLEFT.Y+1;i<BOTTOMLEFT.Y-1;i++)
	{
		for(int j=TOPLEFT.X+1;j<TOPRIGHT.X-1;j++)
		{
			if(mat[i][j]=='#')
			{
				arrInnerWalls.push_back({short(j),short(i)});
				InnerWallsCounter++;
			}
			else
			{
				FruitLocation.push_back({ short(j),short(i) });
				FruitLocationCounter++;
			}
			
		}
	}
	
	BoardInnerWallsArrSize = InnerWallsCounter;
	BoardInnerWalls = new COORD[BoardInnerWallsArrSize];
	for(int i=0;i< BoardInnerWallsArrSize;i++)
	{
		BoardInnerWalls[i] = arrInnerWalls[i];
	}
	
	FruitPossibleLocationArrSize = FruitLocationCounter;
	FruitPossibleLocation = new COORD[FruitPossibleLocationArrSize];
	for(int i=0;i< FruitPossibleLocationArrSize;i++)
	{
		FruitPossibleLocation[i] = FruitLocation[i];
	}

	
}

void Board::SetSecretDors(string* mat, int Size)
{	
	vector<COORD>arr;
	int counter=0;
	for(int i=TOPLEFT.X;i<TOPRIGHT.X;i++)
	{
		if(mat[TOPLEFT.Y][i] == ' ')
		{
			arr.push_back({(short)i,TOPLEFT.Y});
			counter++;
		}
		if (mat[BOTTOMLEFT.Y][i] == ' ')
		{
			arr.push_back({(short)i,BOTTOMLEFT.Y });
			counter++;
		}
	}

	
	for(int i=TOPLEFT.Y;i<BOTTOMLEFT.Y;i++)
	{
		if(mat[i][TOPLEFT.X]==' ')
		{
			arr.push_back({ TOPLEFT.X,short(i)});
			counter++;		
		}
		if(mat[i][(int)BOTTOMRIGHT.X-(1)] == ' ')
		{
			arr.push_back({BOTTOMRIGHT.X,(short)i});
			counter++;
		}
	}



	

	secretDoorsArrSize = counter;
	SecterDoorsArry = new COORD[secretDoorsArrSize];
	for(int i=0;i<secretDoorsArrSize;i++)
	{
		SecterDoorsArry[i] = arr[i];
	}
}

void Board::SetBreadCrumsArry(string* mat)
{
	int counter = 0;
	vector<COORD> arr;
	for (int i = TOPLEFT.Y + 1; i < BOTTOMLEFT.Y; i++)
	{
		for (int j = TOPLEFT.X + 1; j < TOPRIGHT.X; j++)
		{
			if (!IsCordIninnerWalls(short(j), short(i)) && mat[i][j]!='%')
			{
				counter++;
				arr.push_back({ short(j),short(i) });
			}
		}
	}
	this->BreadCrumsLocationArrSize = counter;
	this->BreadCrumsLocation = new COORD[BreadCrumsLocationArrSize];
	for (int i = 0; i < BreadCrumsLocationArrSize; i++)
	{
		BreadCrumsLocation[i] = arr[i];
	}



}





Board::~Board()
{
	delete[] this->BoardInnerWalls;
	delete[] this->SecterDoorsArry;
	delete[] this->ghostsStartLocation;
	delete[] this->FruitPossibleLocation;
}






								
	
	






