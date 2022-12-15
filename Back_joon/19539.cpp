#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

bool solve(int N, vector<int>T_arr)
{
	int total = accumulate(T_arr.begin(), T_arr.end(), 0);
	int count = 0;
	int type2 = 0;
	int type1 = 0;

	if (total % 3 == 0)
	{
		for (int i = 0; i < N; i++)
		{
			type2 += T_arr[i] / 2;
			type1 = T_arr[i] % 2;
		}
		if (total/3 <= type2)   ///&& (type2 - type1) % 3 == 0 이게 있으면 안되는 이유
			return true;
		else
			return false;
	}
	else
	{
		return false;
	}
}

int main()
{
	int N;
	cin >> N;
	vector<int> T_arr(N);
	for (int i = 0; i < N; i++)
		cin >> T_arr[i];

	if (solve(N, T_arr) == true)
		cout << "YES" << endl;
	else
		cout << "NO" << endl;


	return 0;
}