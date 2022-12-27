#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<cmath>

using namespace std;

bool cmp(const pair<int, int>& a, const pair<int, int>& b)
{
	if (a.second == b.second) return a.first < b.first;
	return a.second > b.second;
}

int main()
{
	int N; 
	cin >> N;
	vector<string> str_arr(N);
	for (int i = 0; i < N; i++)
	{
		cin >> str_arr[i];
	}

	map<char, int> mapset;
	for (int i = 0; i < N; i++)
	{
		for (int idx = 0; idx < str_arr[i].size(); idx++)
		{
			if (mapset.find(str_arr[i][idx]) == mapset.end()) // 못찾았다. 없다.
			{
				mapset.insert({ str_arr[i][idx], pow(10, str_arr[i].size() - idx - 1) });
			}
			else // 이미 있는 경우
			{
				auto iter = mapset.find(str_arr[i][idx]);
				iter->second += pow(10, str_arr[i].size() - idx - 1);
			}
		}
	}

	vector<pair<char, int>> vec(mapset.begin(), mapset.end());
	sort(vec.begin(), vec.end(), cmp);

	int result = 0; int mul_num = 9;
	for (int i = 0; i < vec.size(); i++)
	{
		result += vec[i].second * mul_num;
		mul_num -= 1;
	}
	cout << result << endl;
	
	return 0;
}
