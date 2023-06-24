#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

FILE* fin;
FILE* fout;

typedef struct _DisjointSet
{
	int size_maze;
	int* ptr_arr;
}DisjointSets;

void init(DisjointSets* sets, DisjointSets* maze_print, int num);
void Union(DisjointSets* sets, int i, int j);
int find(DisjointSets* sets, int i);
void createMaze(DisjointSets* sets, DisjointSets* maze_print, int num);
void printMaze(DisjointSets* sets, int num);
void freeMaze(DisjointSets* sets, DisjointSets* maze_print);

int main(int argc, char* agrv[])
{
	srand((unsigned int)time(NULL));

	int num, i;
	fin = fopen(agrv[1], "r");
	fout = fopen(agrv[2], "w");

	DisjointSets* sets, * maze_print;
	fscanf(fin, "%d", &num);

	sets = (DisjointSets*)malloc(sizeof(DisjointSets));
	maze_print = (DisjointSets*)malloc(sizeof(DisjointSets));

	init(sets, maze_print, num);
	createMaze(sets, maze_print, num);
	printMaze(maze_print, num);

	freeMaze(sets, maze_print);

	fclose(fin);
	fclose(fout);

	return 0;
}
/*
Allocate and Initialize Disjoint sets
	"sets": have num*num disjoint sets
	"maze_print": have num*num*2 values (two directions: right, down)
		the values are either 0(no wall) or 1 (wall)
*/


void init(DisjointSets* sets, DisjointSets* maze_print, int num)
{
	// ���� 0~n*n -1�� ���� -1���� ������(����)�� root�� ����Ų��.
	sets->ptr_arr = (int*)malloc(sizeof(int) * num * num);
	sets->size_maze = num * num;
	for (int i = 0; i < sets->size_maze; i++)
	{
		sets->ptr_arr[i] = -1;
	}

	// 2*i ���� right ���� ����, 2*i+1 ���� down ���� ����
	maze_print->ptr_arr = (int*)malloc(sizeof(int) * num * num * 2);
	maze_print->size_maze = num * num * 2;
	for (int i = 0; i < maze_print->size_maze; i++)
	{
		maze_print->ptr_arr[i] = 1;
	}
	// �ⱸ�� 0���� �ٲ�����
	maze_print->ptr_arr[num * num * 2 - 2] = 0;
}

/*
Merge two disjoint sets including i and j respectively
*/
void Union(DisjointSets* sets, int i, int j)
{
	int i_root = find(sets, i);
	int j_root = find(sets, j);
	if (sets->ptr_arr[i_root] < sets->ptr_arr[j_root]) // i_root�� �� ū tree�̴�.
	{
		sets->ptr_arr[j_root] = i_root;
	}
	else if (sets->ptr_arr[i_root] > sets->ptr_arr[j_root]) // j_root�� �� ū tree�̴�.
	{
		sets->ptr_arr[i_root] = j_root;
	}
	else if (sets->ptr_arr[i_root] == sets->ptr_arr[j_root])
	{
		sets->ptr_arr[i_root] -= 1;
		sets->ptr_arr[j_root] = i_root;
	}
}
/*
Find the set including given element "i" and return the representative element
*/
int find(DisjointSets* sets, int i)
{
	while (sets->ptr_arr[i] >= 0)
	{
		i = sets->ptr_arr[i];
	}
	return i;
}
/*
Create Maze without cycle
You should generate the maze by randomly choosing cell and direction
*/
/*  print_array �Լ��� console�� ���� array�� ���¸� ����ϴ� �Լ��� disjoint ��Ȳ�� �˷��ִ� �Լ���.
void print_array(DisjointSets* sets)
{
	for (int i = 0; i < sets->size_maze; i++)
	{
		printf("%d ", sets->ptr_arr[i]);
	}
	printf("\n");
}*/

void createMaze(DisjointSets* sets, DisjointSets* maze_print, int num)
{
	while (find(sets, 0) != find(sets, num * num - 1)) // 0�� idx�� ������ idx�� ���� Ʈ���� �ִٸ� ����� ���̱� ������ ����
	{
		int random_number = rand() % (num * num * 2); /// num�� 4�϶� 0~31�� ���� ��� ������ ���� �´�.
		int idx = random_number / 2; // 0~num*2-1 �� ������ idx��
		int dir = random_number % 2; // ���� ����. dir���� right 0, down 1

		int union_idx = -1;
		if (dir == 0 && idx % num != num - 1)// �����ʿ��� ���� ����..
		{
			union_idx = idx + 1;
		}
		else if (dir == 1 && idx < sets->size_maze - num) // �Ʒ��δ� ���� ���� ��
		{
			union_idx = idx + num;
		}

		if (union_idx != -1 && find(sets, idx) != find(sets, union_idx)) // union ����
		{
			Union(sets, idx, union_idx);
			maze_print->ptr_arr[random_number] = 0;
		}

		//print_array(sets);
	}
}

/*
Print Maze
Example>
+---+---+---+---+---+
			|       |
+   +   +---+   +---+
|   |       |       |
+---+   +---+   +   +
|               |   |
+   +---+   +   +---+
|   |       |       |
+   +   +---+---+---+
|   |
+---+---+---+---+---+
*/

void printMaze(DisjointSets* maze_print, int num)
{
	for (int i = 0; i < num; i++)
	{
		fprintf(fout, "+---");
	}
	fprintf(fout, "+\n");

	for (int i = 0; i < num * 2 - 1; i++)
	{
		if (i % 2 == 0)
		{
			if (i == 0) // ��ŸƮ �Ա� �ձ�
			{
				fprintf(fout, " ");
			}
			else
			{
				fprintf(fout, "|");
			}

			for (int t = 0; t < num; t++)
			{
				if (maze_print->ptr_arr[2 * (i / 2 * num + t)] == 1)
				{
					fprintf(fout, "     |");
				}
				else
				{
					fprintf(fout, "     ");
				}

			}
			fprintf(fout, "\n");
		}
		else
		{
			fprintf(fout, "+");

			for (int t = 0; t < num; t++)
			{
				if (maze_print->ptr_arr[2 * (i / 2 * num + t) + 1] == 1) // down ���� �ִ��� üũ
				{
					fprintf(fout, "---+");
				}
				else
				{
					fprintf(fout, "   +");
				}
			}
			fprintf(fout, "\n");
		}

	}
	for (int i = 0; i < num; i++)
	{
		fprintf(fout, "+---");
	}
	fprintf(fout, "+\n");
}
/*
Deallocate sets
*/
void freeMaze(DisjointSets* sets, DisjointSets* maze_print)
{
	free(sets->ptr_arr);
	free(sets);
	free(maze_print->ptr_arr);
	free(maze_print);
}
