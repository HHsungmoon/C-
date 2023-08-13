
#include <iostream>
#include <vector>
#include <string>

#include "Tblock.h"

using namespace std;

// [로테이트 4가지] [x] [y]
// 로테이트 3가지 T,J,L

const int Block_T[4][4][4] = {
	{
		{0,0,0,0},
		{0,1,0,0},
		{1,1,1,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,1,0,0},
		{0,1,1,0},
		{0,1,0,0}
	},
	{
		{0,0,0,0},
		{0,0,0,0},
		{1,1,1,0},
		{0,1,0,0}
	},
	{
		{0,0,0,0},
		{0,1,0,0},
		{1,1,0,0},
		{0,1,0,0}
	}
};
const int Block_J[4][4][4] = {
	{
		{0,0,1,0},
		{0,0,1,0},
		{0,1,1,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,1,0,0},
		{0,1,1,1},
		{0,0,0,0}
	},
		{
		{0,0,0,0},
		{0,1,1,0},
		{0,1,0,0},
		{0,1,0,0}
	},
	{
		{0,0,0,0},
		{1,1,1,0},
		{0,0,1,0},
		{0,0,0,0}
	}
};
const int Block_L[4][4][4] = {
	{
		{0,1,0,0},
		{0,1,0,0},
		{0,1,1,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,1,1,1},
		{0,1,0,0},
		{0,0,0,0}
	},
		{
		{0,0,0,0},
		{0,1,1,0},
		{0,0,1,0},
		{0,0,1,0}
	},
		{
		{0,0,0,0},
		{0,0,1,0},
		{1,1,1,0},
		{0,0,0,0}
	}
};

// 로테이트 2가지 Z,S,I
const int Block_I[4][4][4] = {
	{
		{0,0,0,0},
		{0,0,0,0},
		{1,1,1,1},
		{0,0,0,0}
	},
	{
		{0,0,1,0},
		{0,0,1,0},
		{0,0,1,0},
		{0,0,1,0}
	},
	{
		{0,0,0,0},
		{1,1,1,1},
		{0,0,0,0},
		{0,0,0,0}
	},
	{
		{0,1,0,0},
		{0,1,0,0},
		{0,1,0,0},
		{0,1,0,0}
	}
};
const int Block_Z[4][4][4] = {
	{
		{0,0,0,0},
		{1,1,0,0},
		{0,1,1,0},
		{0,0,0,0}
	},
	{
		{0,0,1,0},
		{0,1,1,0},
		{0,1,0,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,1,1,0},
		{0,0,1,1},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,0,1,0},
		{0,1,1,0},
		{0,1,0,0}
	}
};
const int Block_S[4][4][4] = {
	{
		{0,0,0,0},
		{0,0,1,1},
		{0,1,1,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,1,0,0},
		{0,1,1,0},
		{0,0,1,0}
	},
	{
		{0,0,0,0},
		{0,1,1,0},
		{1,1,0,0},
		{0,0,0,0}
	},
	{
		{0,1,0,0},
		{0,1,1,0},
		{0,0,1,0},
		{0,0,0,0}
	}
};

// 로테이트 1가지 O
const int Block_O[4][4][4] = {
	{
		{0,0,0,0},
		{0,1,1,0},
		{0,1,1,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,1,1,0},
		{0,1,1,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,1,1,0},
		{0,1,1,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,1,1,0},
		{0,1,1,0},
		{0,0,0,0}
	}
};

TBlock::TBlock() {};
TBlock::TBlock(int block_type, int rotation, int s_x, int s_y, const int block[4][4][4], Color color) // start_x, start_y
{
	// 초기 생성위치
	this->tb_x = s_x;
	this->tb_y = s_y;
	this->block_type = block_type;
	this->rotate_cnt = rotation;
	this->block_color = color;

	for (int i = 0; i < 4; i++) 
	{
		for (int x = 0; x < 4; x++) 
		{
			for (int y = 0; y < 4; y++) 
			{
				if (block[i][y][x] == 0)
					this->shape[i][y][x] = 0;
				else
					this->shape[i][y][x] = block_type;
			}
		}
	}
}

int TBlock::getX() { return this->tb_x;}
int TBlock::getY() {return this->tb_y;}
int TBlock::getRotationCount(){return rotate_cnt;}

vector<vector<int>> TBlock::get_shape()
{
	vector<vector<int>> block_shape(4, vector<int>(4, 0));
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			block_shape[y][x] = this->shape[this->rotate_cnt][y][x];
		}
	}

	return block_shape;
}

bool TBlock::Left_Move_possible(vector<vector<int>> board)
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (this->shape[this->rotate_cnt][y][x] != 0)
			{
				if (board[this->tb_y + y][this->tb_x + x - 1] != 0)
					return false;
			}
		}
	}
	return true;
}
bool TBlock::Right_Move_possible(vector<vector<int>> board)
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if ( this->shape[this->rotate_cnt][y][x] != 0)
			{
				if (board[this->tb_y + y][this->tb_x + x + 1] != 0)
					return false;
			}
		}
	}
	return true;
}
bool TBlock::Down_Move_possible(vector<vector<int>> board)
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (this->shape[this->rotate_cnt][y][x] != 0)
			{
				if (board[this->tb_y + y + 1][this->tb_x + x] != 0)
					return false;
			}
		}
	}
	return true;
}

void TBlock::move_down() 
{
	block_clear();
	this->tb_y++;
	block_print();
}
void TBlock::move_left() 
{ 
	block_clear();
	this->tb_x--;
	block_print();
}
void TBlock::move_right() 
{ 
	block_clear();
	this->tb_x++;
	block_print();
}


bool TBlock::Rotation_possible(int tmp, vector<vector<int>> board)
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (this->shape[y][x] != 0)
			{
				if (board[this->tb_y + y][this->tb_x + x] != 0)
					return false;
			}
		}
	}
	return true;
}

void TBlock::Right_rotation(vector<vector<int>> board)
{ 
	int tmp = (this->rotate_cnt + 1) % 4;
	
	if (this->Rotation_possible(tmp, board) == true)
	{
		this->block_clear();
		this->rotate_cnt = tmp;
		this->block_print();
	}
}
void TBlock::Left_rotation(vector<vector<int>> board)
{
	int tmp;
	if (this->rotate_cnt == 0)
	{
		tmp = 3;
	}
	else
	{
		tmp = (this->rotate_cnt - 1) % 4; 
	}
	if (this->Rotation_possible(tmp, board) == true)
	{
		this->block_clear();
		this->rotate_cnt = tmp;
		this->block_print();
	}

}

void TBlock::block_print()
{
	set_color(this->block_color);
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (this->shape[this->rotate_cnt][y][x] != 0)
			{
				goto_xy(this->tb_x + x, this->tb_y + y);
				cout << "■";
			}
		}
	}
	set_color(WHITE);
}

void TBlock::block_clear()
{
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			if (this->shape[this->rotate_cnt][y][x] != 0)
			{
				goto_xy(this->tb_x + x, this->tb_y + y);
				cout << "  ";
			}
		}
	}
}
