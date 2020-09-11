#ifndef _MAIN_HEAD_
#define _MAIN_HEAD_

#define _CRT_SECURE_NO_WARNINGS 
#include<iostream>
#include<windows.h>
#include<conio.h>
#include<fstream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<iomanip>
#include <vector>
#include <ctime>
#include <string>
using namespace std;
//global variable declaration
int k = 7, r = 0, flag = 0;
COORD coord = { 0, 0 };

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

ofstream fout;
ifstream fin;

#endif