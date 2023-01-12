#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int N;
	cin >> N;
	vector<int> vec(N);

	for (int i = 0; i < N; i++)
	{
		cin >> vec[i];
	}

	vector<int> res;
	vector<int>::iterator iter;
	res.push_back(vec[0]);
	for (int i = 1; i < N; i++) 
	{
		if (res.back() < vec[i])
		{
			res.push_back(vec[i]);
		}
		else 
		{
			iter = lower_bound(res.begin(), res.end(), vec[i]);
			*iter = vec[i];
		}
	}

	cout << res.size() << endl;

	return 0;
}