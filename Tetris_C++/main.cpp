#include <iostream>
#include <vector>
#include <conio.h>
#include <algorithm> // copy
#include <cstdio>
#include <chrono>
#include <thread>
#include <time.h>
#include <Windows.h>
#include <set>

#include "Tblock.h"
#include "Tborder.h"

using namespace std;
/*
���� = 0
��ϡ� = 1~7 // ��� ���򺰷�
�ٴں��� ���� ������ = 1~7 // ��� ���򺰷�
������� �� = -2 // ����
�� �� = -1 // ���
*/

#define Board_x 20 //��Ʈ���� �� x �� ����
#define Board_y 30 //��Ʈ���� �� y �� ����
#define Start_x  Board_x / 2 -2
#define Start_y   0

#define LEFT 75 // ��
#define RIGHT 77  // ��
#define UP 72 // ��
#define DOWN 80 // ��


vector<vector<int>> board;
static int score = 0;

void print_score()
{
    goto_xy(Board_x+5, 5);
    cout << "SCORE: " << score;
}

// ����� �����ϴ� �Լ�. 
TBlock* create_block()
{
    int b_num = random_block_num();
    int r_num = random_rotation_num();

    TBlock* new_block = NULL;

    switch (b_num)
    {
    case 1:
        new_block = new TBlock(b_num, r_num, Start_x, Start_y, Block_T, VIOLET);  break;
    case 2:
        new_block = new TBlock(b_num, r_num, Start_x, Start_y, Block_J, BLUE); break;
    case 3:
        new_block = new TBlock(b_num, r_num, Start_x, Start_y, Block_L, GRAY); break;
    case 4:
        new_block = new TBlock(b_num, r_num, Start_x, Start_y, Block_I, RED); break;
    case 5:
        new_block = new TBlock(b_num, r_num, Start_x, Start_y, Block_Z, GREEN); break;
    case 6:
        new_block = new TBlock(b_num, r_num, Start_x, Start_y, Block_S, SKYBLUE); break;
    case 7:
        new_block = new TBlock(b_num, r_num, Start_x, Start_y, Block_O, YELLOW); break;
    default:
        break;
    }

    return new_block;
}
void delete_block(TBlock* block)
{
    delete(block);
}



// ���� �����߿� Ű���� �Է� Ÿ�Կ� ���� ����� �����̴� �Լ�
void block_movement(TBlock* block, char key)
{
    switch (key)
    {
    case LEFT:
        if (block->Left_Move_possible(board) == true)
            block->move_left();
        break;
    case RIGHT:
        if (block->Right_Move_possible(board) == true)
            block->move_right();
        break;
    case DOWN:
        if (block->Down_Move_possible(board) == true)
            block->move_down();
        break;
    case 'a':
        block->Left_rotation(board);
        break;
    case 'd':
        block->Right_rotation(board);
        break;
    }
}

// ����� ���̻� ������ �� ���� �� board�� ����� �߰��� �ش�. 
//�̶� set ������ ����ؼ� ������ ����� �ִ� Y�� �ѹ��� return �Ѵ�. -> �� �� �ϼ��Ǿ��� �� ó���� ����
set<int> Fix_block_board(TBlock* block)
{
    set<int> added_line;  // ���� �ߺ��� ���ϱ� ���� set STL ���
    vector<vector<int>> block_shape = block->get_shape();
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (block_shape[y][x] != 0 && board[block->getY() + y][block->getX() + x] == 0)
            {
                board[block->getY() + y][block->getX() + x] = block_shape[y][x];
                added_line.insert(block->getY() + y);
            }
        }
    }
    return added_line;
}

// �� ���� �ϼ��Ǿ��� ���ɼ��� �ִ� Y�� �����͸� �޾� üũ�Ѵ�. �� �� �ϼ��� �ش� ������ ����.
void clear_line(set<int> line_data)
{
    vector<int> added_line(line_data.begin(), line_data.end());
    sort(added_line.begin(), added_line.end(), greater<int>()); // ���� �Ʒ����κ��� üũ�ؾ� �ϱ⶧���� �������� ����
    int clear_line_num = 0;
    
    for (auto iter = added_line.begin(); iter != added_line.end(); iter++) // ���ͷ����� ���. vector, set �ڷ��� ��� ����ص� �ڵ�� ���Ƽ� ����.
    {
        bool line_condition = true;
        for (int x = 1; x < Board_x - 1; x++)
        {
            if (board[*iter][x] == 0)
            {
                line_condition = false;
                break;
            }
        }
        if (line_condition == true) // �� �� �ϼ� �̹Ƿ� lineŬ����� ���ھ� 1 ���
        {
            board.erase(board.begin() + *iter);
            clear_line_num++;
            score++;
            print_score();
        }
    }

    if (clear_line_num > 0)
    {
        for (int i = 0; i < clear_line_num; i++)
        {
            vector<int> tmp(Board_x, 0);
            tmp[0] = -1; tmp[Board_x - 1] = -1;
            board.insert(board.begin(), tmp);
        }
        clear_board(board);
        print_board(board);
    }
}

// ������� ��ġ ���� ����� boarder�� ���� ��ġ�ϸ�(������� ���� ������) ��������
bool game_end_check()
{
    for (int x = 1; x < Board_x-1; x++)
    {
        if (board[3][x] != 0)
            return true;
    }
    return false;
}


void run_Tetrics_game()
{
    print_score();
    while (game_end_check() == false) // ���� �����ϴ� while��
    {
        TBlock* block = create_block();
        int key=0;
        block->block_print();
        set<int> added_line;

        while (1) // ��� 1���� ���� ���� ���� while��
        {
            for (int i = 0; i < 20; i++)  // �����̴� 0.5�� ������ �Է� ���� üũ�� 0.01�� ���� �Ѵ�.
            {
                if (_kbhit())
                {
                    key = _getch();
                    block_movement(block, key);
                }
                else
                    Sleep(10);
            }

            if (block->Down_Move_possible(board) == true) // ����� �Ʒ��� ������ �� �ִٸ�
            {
                block->move_down();
            }
            else // ����� �� ������ �� ���ٸ� board�� ������ �ְ�, 1�� �ϼ� üũ�� ó���� �� �� ����, ���ο� ����� ����� ���� ����Ŭ ����
            {
                added_line = Fix_block_board(block);
                clear_line(added_line);
                break;
            }
        }
        delete_block(block);
    }

    goto_xy(Board_x + 4, 10);
    cout << "game_end" << endl;
    return;
}



int main()

{
    Hide_Cursor();

	board = make_board(Board_x, Board_y);

    Print_Menu();

	print_board(board);

    run_Tetrics_game();
    goto_xy(0, Board_y+5);

	return 0;
}