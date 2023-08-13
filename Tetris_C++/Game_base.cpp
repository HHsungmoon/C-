
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <random>

#include "Game_base.h"

// 콘솔창의 커서를 숨기는 함수
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

// 게임에서 쓰기 편하게 조정한, 콘솔 커서위치 이동 함수
void goto_xy(int x, int y)
{
    gotoxy(x * 2 + 4, y + 2);
}

// 0,1,2,3 네가지 로테이션 타입 값을 랜덤하게 설정해 주는 함수. C에서는 time을 이용했지만 C++ 라이브러리를 찾아보고 사용하게 됨
int random_rotation_num()
{
    std::random_device rd;

    // random_device 를 통해 난수 생성 엔진을 초기화 한다.
    std::mt19937 gen(rd());

    // 블록 타입을 균등하게 나타나는 난수 생성. 정규분포 타입도 있다.
    std::uniform_int_distribution<int> dis(0, 3);

    return dis(gen);
}

// 7가지 블럭 종류를 랜덤하게 설정해 주는 함수
int random_block_num()
{
    std::random_device rd;

    // random_device 를 통해 난수 생성 엔진을 초기화 한다.
    std::mt19937 gen(rd());

    // 블록 타입을 균등하게 나타나는 난수 생성. 정규분포 타입도 있다.
    std::uniform_int_distribution<int> dis(1,7);

    return dis(gen);
}

// 콘솔창 전체삭제
void clear_screen()
{
    system("cls");
}

// 콘솔 텍스트 색상 변경해주는 함수
void set_color(unsigned short text) 
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}