/#pragma once
//#include "functions.h"
//
//
///
//class object
//{
//private:
//	char indicator;
//	short xcord;
//	short ycord;
//	short StartXcor;
//	short StartYcord;
//public:
//	object(char indexator, short Sx, short Sy);
//	//object(const object& old);
//	HANDLE corse_for_Board;
//	void move_Left(int x, int indicator, COORD* arr, int lenght);
//	void move_Right(int x, int indicator, COORD* arr, int lenght);
//	void move_Down(int x, int indicator, COORD* arr, int lenght);
//	void move_Up(int x, int indicator, COORD* arr, int lenght);
//	void stayFoot(int x, int indicator);
//	int GetXcord()const;
//	int GetYcord()const;
//	void ResetStartLocation(HANDLE corsor_for_Board);
//	
//};
//
//
//
//
//class Packmen : public object
//{
//private:
//	short Lives;
//	short Score;
//public:
//	Packmen(char indexator, short Sx, short Sy, short score, short lives);
//	//Packmen(const Packmen& old);
//	void set_Score(short i);
//	short get_Score()const;
//	void set_Lives(short i);
//	short get_Lives()const;
//	void move(int dir);
//};
//
//
//
//class Gost :public object
//{
//public:
//	Gost(char indexator, short Sx, short Sy);
//	int setRandDir()const;
//	void move(COORD* arr, int lenght);
//};
//
//
//
//class Breadcrumbs
//{
//private:
//	COORD* Arr;
//	int Max_length;
//	int Current_length;
//public:
//	Breadcrumbs();
//	~Breadcrumbs();
//
//
//	COORD* GetArr()const;
//	int GetMaxlength()const;
//	int GetCurrntlength()const;
//
//	void SetCurrentlength(int num);
//	
//	void RemoveCordFromArr(int index);
//
//};
//
//
