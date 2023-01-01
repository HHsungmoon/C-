#include <iostream>
#include <vector>
#include <Windows.h>
#include <cstdio>
#include <string>
#include <conio.h>

#include "snake_sub.h"

using namespace std;

typedef struct
{
	int x;
	int y;
}TYPE_XY;

TYPE_XY food;

typedef struct
{
	TYPE_XY head;
	TYPE_XY body[50];
	char head_direction;
	int body_len;
}Snake;

char game_start_screen()
{
	_goto_xy(20, 5);
	printf("game start -> press 's'\n");
	
	char c = _getch();
	return c;
}

void print_board()
{
	for (int x0 = 0; x0 <= 50; x0++)
		cout << "#";

	for (int y = 1; y <= 20; y++)
	{
		_goto_xy(0, y);
		cout << '#';
		_goto_xy(50, y);
		cout << '#';
	}

	_goto_xy(0, 20);
	for (int x0 = 0; x0 < 50; x0++)
		cout << "#";
}

void make_snake(Snake* snake)
{
	snake->head.x = 20;
	snake->head.y = 10;
	snake->head_direction = RIGHT;
	snake->body_len = 4;
	for (int i = 1; i <= snake->body_len; i++) // 처음 뱀의 길이 4;
	{
		snake->body[i-1].x = snake->head.x - i;
		snake->body[i-1].y = snake->head.y;
	}
}

void print_snake(Snake snake)
{
	char head_ch;
	switch (snake.head_direction)
	{
		case RIGHT:
			head_ch = '<';
			break;
		case LEFT:
			head_ch = '>';
			break;
		case DOWN:
			head_ch = '^';
			break;
		case UP:
			head_ch = 'v';
			break;
	}
	
	_goto_xy(snake.head.x, snake.head.y);
	cout << head_ch;
	for (int i = 0; i < snake.body_len; i++)
	{
		_goto_xy(snake.body[i].x, snake.body[i].y);
		cout << "*";
	}
}

void move_snake(Snake* snake)
{
	memmove(&snake->body[1], &snake->body[0], sizeof(TYPE_XY) * snake->body_len);
	snake->body[0].x = snake->head.x;
	snake->body[0].y = snake->head.y;

	int dir = snake->head_direction;
	switch (dir)
	{
	case RIGHT:
		snake->head.x += 1;
		break;
	case LEFT:
		snake->head.x -= 1;
		break;
	case DOWN:
		snake->head.y += 1;
		break;
	case UP:
		snake->head.y -= 1;
		break;
	}
}

void clear_snake(Snake snake)
{
	_goto_xy(snake.head.x, snake.head.y);
	cout << " ";

	for (int i = 0; i < snake.body_len; i++)
	{
		_goto_xy(snake.body[i].x, snake.body[i].y);
		cout << " ";
	}
}

void print_food()
{
	_goto_xy(food.x, food.y);
	cout << "F";
}

void make_new_food()
{
	srand((unsigned int)time(NULL));

	int new_x = rand() % 50;
	int new_y = rand() % 20;

	if (new_x == 0 || new_y == 0)
		make_new_food();

	food.x = new_x;
	food.y = new_y;
	return;
}

bool snake_eat_food(Snake snake)
{
	if (snake.head.x == food.x && snake.head.y == food.y)
		return true;
	else
		return false;
}


void key_direction(Snake* snake, int key)
{
	switch (key)
	{
	case RIGHT:
		if(snake->head_direction != LEFT)
			snake->head_direction = RIGHT;
		break;
	case LEFT:
		if(snake->head_direction != RIGHT)
			snake->head_direction = LEFT;
		break;
	case DOWN:
		if(snake->head_direction != UP)
			snake->head_direction = DOWN;
		break;
	case UP:
		if(snake->head_direction != DOWN)
			snake->head_direction = UP;
		break;
	}
}

bool snake_hit_wall(Snake snake)
{
	if (snake.head.x <= 0 || snake.head.x > 50 || snake.head.y <= 0 || snake.head.y > 20)
		return true;
	return false;
}

void print_score(int score)
{
	_goto_xy(60, 3);
	cout << "SCORE : " << score;
}

bool snake_hit_body(Snake snake)
{
	for (int i = 0; i < snake.body_len; i++)
	{
		if (snake.head.x == snake.body[i].x && snake.head.y == snake.body[i].y)
			return true;
	}
	return false;
}

void run_game()
{
	bool key_input = false;
	print_board();

	Snake snake1;
	make_snake(&snake1);
	print_snake(snake1);
	make_new_food();
	print_food();

	while (1)
	{
		for (int i = 0; i < 20; i++)  // 딜레이는 0.5초 이지만 입력 여부 체크는 0.01초 마다 한다.
		{
			Sleep(10);
			if (_kbhit())
			{
				int key = _getch();
				key_direction(&snake1, key);
			}
		}

		clear_snake(snake1);
		move_snake(&snake1);
		if (snake_hit_wall(snake1) == true)
			break;
		if (snake_hit_body(snake1) == true)
			break;
		print_snake(snake1);

		if (snake_eat_food(snake1) == true)
		{
			make_new_food();
			snake1.body_len += 1;
			print_food();
			print_score(snake1.body_len - 4);
		}
	}

	cout << "end game" << endl;
	Sleep(10000);
}

int main()
{
	_hide_cursor();
	// game start screen
	if (game_start_screen() == 's')
	{
		_clear_screen();
		run_game();
	}
	else if(game_start_screen() == DKey_ESC)
	{
		_clear_screen();
		cout << "ESC end game" << endl;
		return 0;
	}

	return 0;
}

/*  memo
Sleep(10000);  /// 1000 -> 1초
memmove(복사받을 처음 위치의 포인터값, 복사를 시작할 처음 위치의 포인터값, 크기)
*/