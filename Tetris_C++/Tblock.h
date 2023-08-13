#ifndef __TBlock__
#define __TBlock__

#include <vector>
#include "Game_base.h"

using namespace std;

// 로테이트 3가지 T,J,L
extern const int Block_T[4][4][4];
extern const int Block_J[4][4][4];
extern const int Block_L[4][4][4];
// 로테이트 2가지 Z,S,I
extern const int Block_I[4][4][4];
extern const int Block_Z[4][4][4];
extern const int Block_S[4][4][4];

// 로테이트 1가지 O
extern const int Block_O[4][4][4];

//  Left_Move_possible, Right_Move_possible, Rotation_possible 세가지 함수는 다른 public함수 내에서 사용하기 때문에 private로 선언해 줘도 괜찮다.
class TBlock
{
private:
	int shape[4][4][4];
	int tb_x;
	int tb_y;
	int block_type;
	int rotate_cnt;
	Color block_color;

public:
	TBlock();
	TBlock(int block_num, int rotation, int s_x, int s_y, const int block[4][4][4], Color color); // start_x, start_y
	
	int getX();
	int getY();
	int getRotationCount();
	vector<vector<int>> get_shape();

	bool Left_Move_possible(vector<vector<int>> board);
	bool Right_Move_possible(vector<vector<int>> board);
	bool Down_Move_possible(vector<vector<int>> board);

	void move_down();
	void move_left();
	void move_right();

	bool Rotation_possible(int tmp, vector<vector<int>> board);
	void Right_rotation(vector<vector<int>> board);
	void Left_rotation(vector<vector<int>> board);

	void block_print();
	void block_clear();
};

#endif