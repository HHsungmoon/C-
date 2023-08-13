
#include <cstdio>
#include <iostream>
#include <vector>
#include <conio.h>
#include "Tborder.h"
#include "Game_base.h"

using namespace std;

// 게임 시작전 메뉴를 출력
void Print_Menu()
{
	cout << "\n\n\n\n";
	cout << "\t\t"; cout << "@@@@@@@@@@@@  @@@@@@@@@   @@@@@@@@@@@  @@@@@@@@   @   @@@@@@@@@@@\n" << endl;
	cout << "\t\t"; cout << "      @       @                @       @      @   @   @          \n" << endl;
	cout << "\t\t"; cout << "      @       @                @       @      @   @   @          \n" << endl;
	cout << "\t\t"; cout << "      @       @@@@@@@@@        @       @     @    @   @@@@@@@@@@@\n" << endl;
	cout << "\t\t"; cout << "      @       @                @       @ @ @      @             @\n" << endl;
	cout << "\t\t"; cout << "      @       @                @       @     @    @             @\n" << endl;
	cout << "\t\t"; cout << "      @       @@@@@@@@@        @       @      @   @   @@@@@@@@@@@\n\n\n" << endl;

	cout << "\t\t"; cout << "                  Made by Hong Sung Moon\n" << endl;
	cout << "\t\t"; cout << "                      조작법" << endl;
	cout << "\t\t"; cout << "                      > : 좌로 블록 1칸이동" << endl;
	cout << "\t\t"; cout << "                      < : 우로 블록 1칸이동" << endl;
	cout << "\t\t"; cout << "                      v :  아래로 빠르게 1칸 이동" << endl;
	cout << "\t\t"; cout << "                      a :  블록 왼쪽 방향으로 90도 회전" << endl;
	cout << "\t\t"; cout << "                      d :  블록 오른쪽 방향으로 90도 회전" << endl << endl;
	cout << "\t\t"; cout << "                게임을 시작하려면 아무키나 누르세요.\n" << endl;
	
	_getch();
	clear_screen();
}

// main함수에 선언된 크기 만큼 board를 만듬
vector<vector<int>> make_board(int tb_x, int tb_y)
{
	vector<vector<int>>board(tb_y, vector<int>(tb_x));

	for (int x = 0; x < tb_x; x++)
	{
		board[tb_y - 1][x] = -1;
	}
	for (int y = 0; y < tb_y; y++)
	{
		board[y][0] = -1;
		board[y][tb_x - 1] = -1;
	}

	board[3][0] = -2;
	board[3][tb_x - 1] = -2;

	return board;
}

void print_board(vector<vector<int>> board)
{
	for (int y = 0; y < board.size(); y++)
	{
		for (int x = 0; x < board[y].size(); x++)
		{
			if (board[y][x] != 0)
			{
				switch (board[y][x])
				{
				case -1:
					set_color(WHITE);
					break;
				case -2:
					set_color(DARK_RED);
					goto_xy(board[3].size() + 1, 3);
					cout << "dead_line";
				case 1: // T 보라
					set_color(VIOLET);
					break;
				case 2: // J 
					set_color(BLUE);
					break;
				case 3: // L
					set_color(DARK_GRAY);
					break;
				case 4: // Z
					set_color(RED);
					break;
				case 5: // S
					set_color(GREEN);
					break;
				case 6:  // I
					set_color(SKYBLUE);
					break;
				case 7: // O
					set_color(YELLOW);
					break;
				default:
					break;
				}
				goto_xy(x, y);
				cout << "■";
			}
		}
	}
	set_color(WHITE);
}

void clear_board(vector<vector<int>> board)
{
	for (int y = 0; y < board.size(); y++)
	{
		for (int x = 0; x < board[y].size(); x++)
		{
			goto_xy(x, y);
			cout << "  ";
		}
	}
}