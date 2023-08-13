
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <random>

#include "Game_base.h"


void Hide_Cursor()
{
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// 콘솔 커서위치 이동
void gotoxy(int x, int y)
{
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void goto_xy(int x, int y)
{
    gotoxy(x * 2 + 4, y + 2);
}

int random_rotation_num()
{
    std::random_device rd;

    // random_device 를 통해 난수 생성 엔진을 초기화 한다.
    std::mt19937 gen(rd());

    // 블록 타입을 균등하게 나타나는 난수 생성. 정규분포 타입도 있다.
    std::uniform_int_distribution<int> dis(0, 3);

    return dis(gen);
}

int random_block_num()
{
    std::random_device rd;

    // random_device 를 통해 난수 생성 엔진을 초기화 한다.
    std::mt19937 gen(rd());

    // 블록 타입을 균등하게 나타나는 난수 생성. 정규분포 타입도 있다.
    std::uniform_int_distribution<int> dis(1,7);

    return dis(gen);
}

void clear_screen()
{
    system("cls");
}

// 콘솔 텍스트 색상 변경해주는 함수
void set_color(unsigned short text) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}