#include <iostream>

using namespace std;

int N, K;
int Coin[101];
int DP[10001];

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> K;
    for (int i = 1; i <= N; i++) 
        cin >> Coin[i];

    DP[0] = 1;
    for (int i = 1; i <= N; i++)
    {
        for (int j = Coin[i]; j <= K; j++)
        {
            DP[j] = DP[j] + DP[j - Coin[i]];
        }
    }
    cout << DP[K] << endl;

    return 0;
}