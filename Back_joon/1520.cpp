#include <iostream>

using namespace std;

int M, N; 
int arr[501][501] = {};
int DP[501][501] = {};

int move_x[4] = { 0,0,-1,1 };
int move_y[4] = { -1,1,0,0 };


int DFS(int x, int y)
{
	if (x == N - 1 && y == M - 1)
	{
		return 1;
	}
	if (DP[y][x] != -1)
	{
		return DP[y][x];
	}

	DP[y][x] = 0;
	for (int i = 0; i < 4; i++)
	{
		int nx = x + move_x[i];
		int ny = y + move_y[i];

		if (nx >= 0 && nx < N && ny >= 0 && ny < M )  //arr[y][x]
		{
			if(arr[ny][nx] < arr[y][x])
			{
				DP[y][x] = DP[y][x] + DFS(nx, ny);
			}
		}
	}

	return DP[y][x];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> M >> N;

	for (int i = 0; i < M; i++)
	{
		for (int n = 0; n < N; n++)
		{
			cin >> arr[i][n];
			DP[i][n] = -1;
		}
	}

	cout << DFS(0, 0);

	return 0;
}