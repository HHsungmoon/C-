#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE* fin;
FILE* fout;

typedef int ElementType;
typedef ElementType List;
typedef struct HashTbl* HashTable;

typedef struct HashTbl 
{
	int TableSize;
	List* TheLists;
}HashTbl;

HashTable createTable(int TableSize);
void Insert(HashTable H, ElementType Key, int solution);
void Delete(HashTable H, ElementType Key, int solution);
int Find(HashTable H, ElementType Key, int solution);
void printTable(HashTable H);
void deleteTable(HashTable H);

int main(int argc, char* argv[]) 
{
	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");


	char solution_str[20];
	int solution, TableSize;

	fscanf(fin, "%s", solution_str);
	if (!strcmp(solution_str, "linear"))
		solution = 1;
	else if (!strcmp(solution_str, "quadratic"))
		solution = 2;
	else {
		fprintf(fout, "Error: Invalid hashing solution!");
		return 0;
	}

	fscanf(fin, "%d", &TableSize);

	HashTable H = createTable(TableSize);

	char cv;
	int key;
	while (!feof(fin)) 
	{
		int result = 0;
		fscanf(fin, "%c", &cv);
		switch (cv) 
		{
		case 'i':
			fscanf(fin, "%d", &key);
			Insert(H, key, solution);
			break;

		case 'f':
			fscanf(fin, "%d", &key);
			result = Find(H, key, solution);
			if (result)
				fprintf(fout, "%d is in the table\n", key);
			else
				fprintf(fout, "%d is not in the table\n", key);
			break;
		case 'd':
			fscanf(fin, "%d", &key);
			Delete(H, key, solution);
			break;

		case 'p':
			printTable(H);
			break;
		}
	}

	deleteTable(H);

	return 0;
}

/*
Create new Hash Table with given TableSize
reture:
	the pointer of new hash table
*/
HashTable createTable(int TableSize) 
{
	HashTable new_tb = (HashTable)malloc(sizeof(HashTbl));
	new_tb->TableSize = TableSize;
	new_tb->TheLists = (List*)malloc(sizeof(List) * TableSize);
	for (int i = 0; i < TableSize; i++)
	{
		new_tb->TheLists[i] = 0;
	}

	return new_tb;
}

/*
Insert the key in hash table with given solution (linear or quadratic).
print out :
	Successful insertion : "insert %d into address %d\n"
	When inserting duplicate key value : "insertion error : %d already exists at address %d\n"
	When HashTable is full : "insertion error : table is full\n"
*/
void Insert(HashTable H, ElementType Key, int solution) 
{
	// find 수행
	if (Find(H, Key, solution) == 1)
	{
		for (int i = 0; i < H->TableSize; i++)
		{
			if (H->TheLists[i] == Key)
			{
				fprintf(fout, "insertion error: %d already exists at address %d\n", Key,i);
				return;
			}
		}
	}
	int address = Key % H->TableSize;;
	
	int iter = 1; int cnt = 0;
	while (H->TheLists[address] != 0 && cnt <= H->TableSize) // collision 수행
	{
		cnt++;
		if (solution == 1)
		{
			address = (Key + iter) % H->TableSize;
			iter++;
		}
		else if (solution == 2)
		{
			address = (Key + iter * iter) % H->TableSize;
			iter++;
		}
	}

	if (cnt == H->TableSize)
	{
		fprintf(fout, "insertion Error: table is full\n");
	}
	// insert
	if (H->TheLists[address] == 0)
	{
		H->TheLists[address] = Key;
		fprintf(fout, "insert %d into address %d\n", Key, address);
		return;
	}
}
/*
Delete the key in hash table with given solution (linear or quadratic).
print out :
	when key value is found :  "delete %d\n"
	when key value does not exist : %d is not in the table\n"
*/
void Delete(HashTable H, ElementType Key, int solution) 
{
	if (Find(H, Key, solution) == 0)
	{
		fprintf(fout, "deletion Error: %d is not in the table\n", Key);
		return;
	}

	int address = Key % H->TableSize;;

	int iter = 1;
	while (H->TheLists[address] != Key) // collision 수행
	{
		if (solution == 1)
		{
			address = (Key + iter) % H->TableSize;
			iter++;
		}
		else if (solution == 2)
		{
			address = (Key + iter * iter) % H->TableSize;
			iter++;
		}
	}
	fprintf(fout, "delete %d\n", H->TheLists[address]);
	H->TheLists[address] = 0;
}

/*
Find the Key from hash table with given solution (linear or quadratic).
return:
	0 : when the key is not found
	1 : when the key is found
*/
int Find(HashTable H, ElementType Key, int solution)
{
	for (int i = 0; i < H->TableSize; i++)
	{
		if (H->TheLists[i] == Key)
			return 1;
	}
	return 0;
}
/*
Print all values of Hash Table
print out the key values ​​in the Hash Table in the order of index in the Hash Table.
	empty Hash Table print : "0 "
	Non empty Hash Table print : "%d "
*/
void printTable(HashTable H) 
{
	int empty_check = 0;
	for (int i = 0; i < H->TableSize; i++)
	{
		if (H->TheLists[i] != 0)
		{
			empty_check = 1;
			break;
		}
	}

	if (empty_check == 0)
	{
		fprintf(fout, "0 ");
	}
	else
	{
		for (int i = 0; i < H->TableSize; i++)
		{
			fprintf(fout, "%d ", H->TheLists[i]);
		}
		fprintf(fout, "\n");
	}
}
/*
delete Table
*/
void deleteTable(HashTable H) 
{
	free(H->TheLists);
	free(H);
}
