#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int max_num = 0;

int** copy_block_arr(int** block_arr, int N)
{
	int** copy_arr = new int* [N];
	for (int i = 0; i < N; i++)
	{
		copy_arr[i] = new int[N];
	}
	for (int x = 0; x < N; x++)
		for (int y = 0; y < N; y++)
			copy_arr[x][y] = block_arr[x][y];

	return copy_arr;
}

void print_block(int** block_arr, int N)
{
	cout << endl;
	for (int x = 0; x < N; x++)
	{
		for (int y = 0; y < N; y++)
			cout << block_arr[x][y] << " ";
		cout << endl;
	}
}

void shift_left(int** block_arr, int N)
{
	int cnt = 0;
	// 빈칸없이 정렬
	for (int y = 0; y < N; y++)
	{
		int* tmp_arr = new int[N];
		for (int i = 0; i < N; i++) tmp_arr[i] = 0;

		for (int x = 0; x < N; x++)
		{
			if (block_arr[y][x] != 0)
			{
				tmp_arr[cnt] = block_arr[y][x];
				cnt++;
			}
		}
		for (int i = 0; i < N; i++)
		{
			block_arr[y][i] = tmp_arr[i];
		}
		cnt = 0;
		delete[] tmp_arr;
	}

	for (int y = 0; y < N; y++)  // block_arr[y][x]
	{
		int* tmp = new int[N];
		for (int i = 0; i < N; i++) tmp[i] = 0;
		for (int x = 0; x < N; x++)
		{
			if (x != N - 1)
			{
				if (block_arr[y][x] != 0 && block_arr[y][x] == block_arr[y][x + 1])
				{
					tmp[cnt] = block_arr[y][x] + block_arr[y][x + 1];
					x++;
					cnt++;
				}
				else if (block_arr[y][x] != 0)
				{
					tmp[cnt] = block_arr[y][x];
					cnt++;
				}
			}
			else
			{
				tmp[cnt] = block_arr[y][x];
			}
		}
		for (int i = 0; i < N; i++)
		{
			block_arr[y][i] = tmp[i];
		}
		cnt = 0;
		delete[] tmp;
	}
}

void shift_right(int** block_arr, int N)
{
	int cnt = N-1;
	for (int y = 0; y < N; y++)
	{
		int* tmp_arr = new int[N];
		for (int i = 0; i < N; i++) tmp_arr[i] = 0;

		for (int x = N-1; x >= 0; x--)
		{
			if (block_arr[y][x] != 0)
			{
				tmp_arr[cnt] = block_arr[y][x];
				cnt--;
			}
		}
		for (int i = 0; i < N; i++)
		{
			block_arr[y][i] = tmp_arr[i];
		}
		cnt = N-1;
		delete[] tmp_arr;
	}

	cnt = 0;
	for (int y = 0; y < N; y++)  // block_arr[y][x]
	{
		int* tmp = new int[N];
		for (int i = 0; i < N; i++) tmp[i] = 0;
		for (int x = N - 1; x >= 0; x--)
		{
			if (x != 0)
			{
				if (block_arr[y][x] != 0 && block_arr[y][x] == block_arr[y][x - 1])
				{
					tmp[cnt] = block_arr[y][x] + block_arr[y][x - 1];
					x--;
					cnt++;
				}
				else if (block_arr[y][x] != 0)
				{
					tmp[cnt] = block_arr[y][x];
					cnt++;
				}
			}
			else
			{
				tmp[cnt] = block_arr[y][x];
			}
		}
		for (int i = 0; i < N; i++)
		{
			block_arr[y][(N - 1) - i] = tmp[i];
		}
		cnt = 0;
		delete[] tmp;
	}
}

void shift_up(int** block_arr, int N)
{
	int cnt = 0;
	for (int x = 0; x < N; x++)
	{
		int* tmp_arr = new int[N];
		for (int i = 0; i < N; i++) tmp_arr[i] = 0;

		for (int y = 0; y < N; y++)
		{
			if (block_arr[y][x] != 0)
			{
				tmp_arr[cnt] = block_arr[y][x];
				cnt++;
			}
		}
		for (int i = 0; i < N; i++)
		{
			block_arr[i][x] = tmp_arr[i];
		}
		cnt = 0;
		delete[] tmp_arr;
	}

	for (int x = 0; x < N; x++)  // block_arr[y][x]
	{
		int* tmp = new int[N];
		for (int i = 0; i < N; i++) tmp[i] = 0;
		for (int y = 0; y < N; y++)
		{
			if (y != N - 1)
			{
				if (block_arr[y][x] != 0 && block_arr[y][x] == block_arr[y + 1][x])
				{
					tmp[cnt] = block_arr[y][x] + block_arr[y + 1][x];
					y++;
					cnt++;
				}
				else if (block_arr[y][x] != 0)
				{
					tmp[cnt] = block_arr[y][x];
					cnt++;
				}
			}
			else
			{
				tmp[cnt] = block_arr[y][x];
			}
		}
		for (int i = 0; i < N; i++)
		{
			block_arr[i][x] = tmp[i];
		}
		cnt = 0;
		delete[] tmp;
	}
}

void shift_down(int** block_arr, int N)
{
	int cnt = N - 1;
	for (int x = 0; x < N; x++)
	{
		int* tmp_arr = new int[N];
		for (int i = 0; i < N; i++) tmp_arr[i] = 0;

		for (int y = N - 1; y >= 0; y--)
		{
			if (block_arr[y][x] != 0)
			{
				tmp_arr[cnt] = block_arr[y][x];
				cnt--;
			}
		}
		for (int i = 0; i < N; i++)
		{
			block_arr[i][x] = tmp_arr[i];
		}
		cnt = N - 1;
		delete[] tmp_arr;
	}

	for (int x = 0; x < N; x++)  // block_arr[y][x]
	{
		int* tmp = new int[N];
		for (int i = 0; i < N; i++) tmp[i] = 0;
		for (int y = N - 1; y >= 0; y--)
		{
			if (y != 0)
			{
				if (block_arr[y][x] != 0 && block_arr[y][x] == block_arr[y - 1][x])
				{
					tmp[cnt] = block_arr[y][x] + block_arr[y - 1][x];
					y--;
					cnt--;
				}
				else if (block_arr[y][x] != 0)
				{
					tmp[cnt] = block_arr[y][x];
					cnt--;
				}
			}
			else
			{
				tmp[cnt] = block_arr[y][x];
			}
		}
		for (int i = 0; i < N; i++)
		{
			block_arr[i][x] = tmp[i];
		}
		cnt = N - 1;
		delete[] tmp;
	}
}

void test_run_2048(int** block_arr, int N)
{
	int** tmp_arr;
	tmp_arr = copy_block_arr(block_arr, N);

	shift_up(tmp_arr, N);

	print_block(tmp_arr, N);

}

void delete_arr(int** tmp_arr, int N)
{
	for (int i = 0; i < N; i++)
	{
		delete[] tmp_arr[i];
	}
	delete[] tmp_arr;
}

int max_num_update(int** block_arr, int N)
{
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			if (block_arr[y][x] > max_num)
				max_num = block_arr[y][x];
		}
	}
	return max_num;
}

int run_2048(int** block_arr, int N, int cnt)
{
	if (cnt == 5)
	{
		return max_num_update(block_arr, N);
	}

	int** tmp_arr;
	tmp_arr = copy_block_arr(block_arr, N);
	for (int i = 0; i < 4; i++) // 0-좌로밀기, 1-우로밀기, 2-위로밀기, 3-아래로밀기
	{
		switch (i)
		{
		case 0:
			tmp_arr = copy_block_arr(block_arr, N);
			shift_left(tmp_arr, N);
			run_2048(tmp_arr, N, cnt + 1);
			break;
		case 1:
			tmp_arr = copy_block_arr(block_arr, N);
			shift_right(tmp_arr, N);
			run_2048(tmp_arr, N, cnt + 1);
			break;
		case 2:
			tmp_arr = copy_block_arr(block_arr, N);
			shift_up(tmp_arr, N);
			run_2048(tmp_arr, N, cnt + 1);
			break;
		case 3:
			tmp_arr = copy_block_arr(block_arr, N);
			shift_down(tmp_arr, N);
			run_2048(tmp_arr, N, cnt + 1);
			break;
		}
	}

	delete_arr(tmp_arr, N);
	return max_num;
}

int main()
{
	int N;
	cin >> N;
	int** block_arr = new int* [N];
	for (int i = 0; i < N; i++)
	{
		block_arr[i] = new int[N];
	}
	for (int x = 0; x < N; x++)
		for (int y = 0; y < N; y++)
			cin >> block_arr[x][y];

	run_2048(block_arr, N, 0);
	//test_run_2048(block_arr, N);
	cout << max_num << endl;

	for (int i = 0; i < N; i++)
	{
		delete[] block_arr[i];
	}
	delete[] block_arr;
	return 0;
}