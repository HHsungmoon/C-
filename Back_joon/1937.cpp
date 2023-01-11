#include <iostream>
#include <vector>

using namespace std;

int N;
int** map_arr;
int** DP_map;

int idx[4] = { -1, 1, 0, 0 };
int idy[4] = { 0, 0, -1, 1 };

int DFS(int x, int y)
{
	if (DP_map[y][x] != 0)
		return DP_map[y][x];
	DP_map[y][x] = 1;

	int now_xy = map_arr[y][x];
	for (int i = 0; i < 4; i++)
	{
		int nx = x + idx[i];
		int ny = y + idy[i];

		if (nx >= 0 && nx < N && ny >= 0 && ny < N && now_xy < map_arr[ny][nx]) // 배열 범위 체크, 이동 가능할 때
		{
			if (DP_map[ny][nx] != -1) /// 계산된 값을 아는 경우
			{
				DP_map[y][x] = max(DP_map[y][x], DFS(nx,ny)+1);
			}
		}
	}
	return DP_map[y][x];
}

void print_map()
{
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			cout << DP_map[y][x] << " ";
		}
		cout << endl;
	}
}

int main()
{
	cin >> N;

	map_arr = new int* [N];
	DP_map = new int* [N];
	for (int i = 0; i < N; i++)
	{
		map_arr[i] = new int[N];
		DP_map[i] = new int[N];
	}
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			cin >> map_arr[y][x];
			DP_map[y][x] = 0;
		}
	}

	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			DFS(x, y);
			//print_map();
			//cout << endl;
		}
	}

	int ans = 0;
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			ans = max(DP_map[y][x], ans);
		}
	}

	cout << ans << endl;

	return 0;
}