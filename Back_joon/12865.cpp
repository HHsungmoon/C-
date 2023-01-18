#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int N, K;
	cin >> N >> K;
	vector<pair<int, int>> vec(N + 1);

	int** dp = new int* [N + 1];
	for (int i = 0; i <= N; i++)
	{
		dp[i] = new int[K + 1];
		for (int k = 0; k < K + 1; k++)
			dp[i][k] = 0;
	}

	for (int i = 1; i <= N; i++)
	{
		cin >> vec[i].first >> vec[i].second;
	}
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= K; j++)
		{
			if (j >= vec[i].first)
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - vec[i].first] + vec[i].second);
			else
				dp[i][j] = dp[i - 1][j];
		}
	}
	cout << dp[N][K];
	return 0;
}


/*
int main()
{
	int N, K;
	cin >> N >> K;

	vector<pair<int, int>> vec(N);
	for (int n = 0; n < N; n++)
	{
		cin >> vec[n].first >> vec[n].second;
	}

	sort(vec.begin(), vec.end());

	int** dp_arr = new int* [N];
	for (int i = 0; i < N; i++)
	{
		dp_arr[i] = new int[K+1];
		for (int k = 0; k < K + 1; k++)
			dp_arr[i][k] = 0;
	}

	// DP 채우기

	dp_arr[0][vec[0].first] = vec[0].second;
	for (int i = 1; i <= K; i++)
	{
		if (dp_arr[0][i - 1] > dp_arr[0][i])
			dp_arr[0][i] = dp_arr[0][i - 1];
	}

	for (int n = 1; n < N; n++)
	{
		//초기화
		for (int k = 0; k <= K; k++)
		{
			if (dp_arr[n - 1][k] != 0)
				dp_arr[n][k] = dp_arr[n - 1][k];
		}
		for (int k = 0; k < K; k++)
		{
			if (dp_arr[n][k] != 0 && k+vec[n].first <= K)
			{
				dp_arr[n][k + vec[n].first] = dp_arr[n][k] + vec[n].second;
			}
		}

		dp_arr[n][vec[n].first] = max(dp_arr[n][vec[n].first], vec[n].second);

		for (int i = 1; i <= K; i++)
		{
			if (dp_arr[n][i - 1] > dp_arr[n][i])
				dp_arr[n][i] = dp_arr[n][i - 1];
		}
	}

	for (int n = 0; n < N; n++)
	{
		for (int k = 0; k <= K; k++)
			cout << dp_arr[n][k] << " ";
		cout << endl;
	}

	int max_num = 0;
	max_num = *max_element(dp_arr[N - 1], dp_arr[N - 1] + K+1);

	cout << max_num << endl;

	return 0;
}
*/