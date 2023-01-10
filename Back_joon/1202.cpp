#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int N, K;
	cin >> N >> K;
	vector<pair<int, int>> vec(N);
	vector<int> bag(K);

	for (int n = 0; n < N; n++)
	{
		cin >> vec[n].first >> vec[n].second;
	}
	for (int k = 0; k < K; k++)
	{
		cin >> bag[k];
	}

	sort(vec.begin(), vec.end());  // 무게를 오름차순 정렬
	sort(bag.begin(), bag.end());

	long long total = 0;
	int n_idx = 0;
	priority_queue<int> pq;

	for (int i = 0; i < K; i++)  // bag idx
	{
		while (n_idx < N && vec[n_idx].first <= bag[i])
		{
			pq.push(vec[n_idx].second);
			n_idx++;
		}

		// pq 초기화, 가방에 입력
		if (pq.empty() == false)
		{
			total += (long long)pq.top();
			pq.pop();
		}
	}

	cout << total << endl;

	return 0;
}

