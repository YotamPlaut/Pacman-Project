#include "Bread_Crumbs.h"



Bread_Crumbs::Bread_Crumbs()
{
	/*
	int index = 0;
	this->Arr = new COORD[10000];
	this->Max_length = 0;
	for (short i = Board::getTOPLEFT().X + 1; i < Board::getTOPRIGHT().X; i++)
	{
		for (short j = Board::getTOPLEFT().Y + 1; j < Board::getBOTTOMLEFT().Y; j++)
		{
			if(!Board::IsCordIninnerWalls(i,j))
			{
				this->Arr[index] = { i,j };
				index++;
				this->Max_length++;
			}
		}
	}
	this->Current_length = this->Max_length;
	*/
	
	this->Current_length=this->Max_length= Board::GetBreadCrumsLocationArrSize();
	this->Arr = new COORD[Current_length];
	COORD* tempArr = Board::GetBreadCrumsLocation();
	for(int i=0;i< Current_length;i++)
	{
		Arr[i] = tempArr[i];
	
	}
	
}

Bread_Crumbs:: ~Bread_Crumbs()
{
	delete[]this->Arr;
}


COORD* Bread_Crumbs::GetArr()const
{
	return this->Arr;
}

int Bread_Crumbs::GetMaxlength()const
{
	return this->Max_length;
}

int Bread_Crumbs::GetCurrntlength()const
{
	return this->Current_length;

}

void Bread_Crumbs::SetCurrentlength(int num)
{
	this->Current_length = num;
}


void Bread_Crumbs::RemoveCordFromArr(int index)
{
	int counter = 0;
	COORD* NewArr = new COORD[Current_length-1];
	for (int i = 0; i < this->Current_length; i++)
	{
		if (index != i)
		{
			NewArr[counter] = this->Arr[i];
			counter++;
		}
	}
	delete[] this->Arr;
	this->Arr = NewArr;
	this->Current_length--;
}



