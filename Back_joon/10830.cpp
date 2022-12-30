#include <iostream>

using namespace std;


void one_round(int** main, int** sub, int** cout_arr, int N)
{
	for (int n = 0; n < N; n++)
	{
		for (int k = 0; k < N; k++)
		{
			for (int m = 0; m < N; m++)
			{
				cout_arr[n][k] += main[n][m] * sub[m][k];
			}
		}
	}
	for (int n = 0; n < N; n++)
	{
		for (int k = 0; k < N; k++)
		{
			main[n][k] = cout_arr[n][k] % 1000;
			cout_arr[n][k] = 0;
		}
	}
}

void run(int** nn_arr, int** cout_arr, int N, long long B)
{
	int** tmp = new int* [N];
	for (int i = 0; i < N; i++)
	{
		tmp[i] = new int[N];
	}

	int exit_first = 0;

	while (B > 1)
	{
		if (B % 2 == 1)
		{
			if (exit_first == 0)
			{
				for (int n = 0; n < N; n++)
				{
					for (int k = 0; k < N; k++)
					{
						tmp[n][k] = nn_arr[n][k];
					}
				}
				exit_first = 1;
			}
			else 
			{ 
				one_round(tmp, nn_arr, cout_arr, N); 
			}
		}

		one_round(nn_arr, nn_arr, cout_arr, N);
		B /= 2;
	}
	if(exit_first == 1) one_round(nn_arr, tmp, cout_arr, N);

	for (int i = 0; i < N; i++)
	{
		delete[] tmp[i];
	}
}

void print_arr(int** nn_arr, int N)
{
	for (int n = 0; n < N; n++)
	{
		for (int k = 0; k < N; k++)
		{
			cout << nn_arr[n][k] % 1000 << " ";
		}
		cout << endl;
	}
}

int main()
{
	int N;
	long long B;
	cin >> N >> B;

	int** nn_arr = new int* [N];
	for (int i = 0; i < N; i++)
	{
		nn_arr[i] = new int[N];
		for (int t = 0; t < N; t++)
		{
			cin >> nn_arr[i][t];
		}
	}

	int** cout_arr = new int* [N];
	for (int i = 0; i < N; i++)
	{
		cout_arr[i] = new int[N];
	}
	for (int n = 0; n < N; n++)
	{
		for (int k = 0; k < N; k++)
		{
			cout_arr[n][k] = 0;
		}
	}

	/// //////////////////////////

	run(nn_arr, cout_arr, N, B);

	print_arr(nn_arr, N);

	for (int i = 0; i < N; i++)
	{
		delete[] nn_arr[i];
		delete[] cout_arr[i];
	}


	return 0;
}