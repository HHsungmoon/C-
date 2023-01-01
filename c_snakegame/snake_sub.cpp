#define _CRT_SECURE_NO_WARNINGS


#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<windows.h>

#include "snake_sub.h"


void _goto_xy(int x, int y)
{
	HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x,y };

	fflush(stdout);
	SetConsoleCursorPosition(hd, pos);
}

//COORD getCursor(void)
//{
//	COORD cur;
//	CONSOLE_SCREEN_BUFFER_INFO curInfo;
//
//	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&curInfo);
//	cur.X=curInfo.dwCursorPosition.X;
//	cur.Y=curInfo.dwCursorPosition.Y;
//	return cur;
//}


void _hide_cursor()
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void _clear_screen()
{
	system("cls");
}

void _initialize_random()
{
	time_t current_tick = time(0);
	srand((unsigned int)current_tick);
}


char* current_time()
{
	time_t now = time(0);
	return ctime(&now);
}


