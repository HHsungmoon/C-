
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <random>

#include "Game_base.h"

// �ܼ�â�� Ŀ���� ����� �Լ�
void Hide_Cursor()
{
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// �ܼ� Ŀ����ġ �̵�
void gotoxy(int x, int y)
{
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// ���ӿ��� ���� ���ϰ� ������, �ܼ� Ŀ����ġ �̵� �Լ�
void goto_xy(int x, int y)
{
    gotoxy(x * 2 + 4, y + 2);
}

// 0,1,2,3 �װ��� �����̼� Ÿ�� ���� �����ϰ� ������ �ִ� �Լ�. C������ time�� �̿������� C++ ���̺귯���� ã�ƺ��� ����ϰ� ��
int random_rotation_num()
{
    std::random_device rd;

    // random_device �� ���� ���� ���� ������ �ʱ�ȭ �Ѵ�.
    std::mt19937 gen(rd());

    // ��� Ÿ���� �յ��ϰ� ��Ÿ���� ���� ����. ���Ժ��� Ÿ�Ե� �ִ�.
    std::uniform_int_distribution<int> dis(0, 3);

    return dis(gen);
}

// 7���� �� ������ �����ϰ� ������ �ִ� �Լ�
int random_block_num()
{
    std::random_device rd;

    // random_device �� ���� ���� ���� ������ �ʱ�ȭ �Ѵ�.
    std::mt19937 gen(rd());

    // ��� Ÿ���� �յ��ϰ� ��Ÿ���� ���� ����. ���Ժ��� Ÿ�Ե� �ִ�.
    std::uniform_int_distribution<int> dis(1,7);

    return dis(gen);
}

// �ܼ�â ��ü����
void clear_screen()
{
    system("cls");
}

// �ܼ� �ؽ�Ʈ ���� �������ִ� �Լ�
void set_color(unsigned short text) 
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}