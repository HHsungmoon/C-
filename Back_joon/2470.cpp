#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int N;
	cin >> N;
	vector<int> vec;
	for (int i = 0; i < N; i++)
	{
		int tmp;
		cin >> tmp;
		vec.push_back(tmp);
	}

	sort(vec.begin(), vec.end());  // 오름차순 정렬

	int min = 0;
	int max = N - 1;
	int result = 2000000001;
	int r1, r2;

	while (min < max)
	{
		int sum = vec[min] + vec[max];

		if (sum > 0)
		{
			if (result > sum)
			{
				result = sum;
				r1 = vec[min];
				r2 = vec[max];
			}
			max--;
		}
		else if (sum < 0)
		{
			if (result > -sum)
			{
				result = -sum;
				r1 = vec[min];
				r2 = vec[max];
			}
			min++;
		}
		else if (sum == 0)
		{
			r1 = vec[min];
			r2 = vec[max];
			break;
		}
	}

	cout << r1 << " " << r2 << endl;

	return 0;
}