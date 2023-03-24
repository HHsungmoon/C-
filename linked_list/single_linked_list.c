#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

FILE* fin;
FILE* fout;

typedef struct Node* PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position; // == Node* Position
typedef int ElementType;

typedef struct Node 
{
	ElementType element;
	Position next;  // Position 이 Node* 이다.
}Node;

List MakeEmpty(List L);
int IsEmpty(List L);
int IsLast(Position P, List L);
void Insert(ElementType X, List L, Position P);
Position FindPrevious(ElementType X, List L);
Position Find(ElementType X, List L);
void Delete(ElementType X, List L);
void DeleteList(List L);
int* GetElements(List L);
int ListSize = 0;

int main(int argc, char** argv) {
	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");
	char x;
	int* elements;

	Position header = NULL, tmp = NULL;
	header = MakeEmpty(header);
	while (fscanf(fin, "%c", &x) != EOF) 
	{
		if (x == 'i') 
		{
			int a, b;	fscanf(fin, "%d%d", &a, &b);
			tmp = Find(a, header);
			if (tmp != NULL) 
			{
				fprintf(fout, "insertion(%d) failed : the key already exists in the list\n", a);
				//printf("insertion(%d) failed : the key already exists in the list\n", a);
				continue;
			}
			tmp = Find(b, header);
			if (tmp == NULL)
			{
				fprintf(fout, "insertion(%d) failed : can not find the location to be inserted\n", a);
				//printf("insertion(%d) failed : can not find the location to be inserted\n", a);
				continue;
			}
			Insert(a, header, tmp);
		}
		else if (x == 'd') {
			int a;	fscanf(fin, "%d", &a);
			tmp = Find(a, header);
			if (tmp == NULL) {
				fprintf(fout, "deletion(%d) failed : element %d is not in the list\n", a, a);
				//printf("deletion(%d) failed : element %d is not in the list\n", a, a);
				continue;
			}
			Delete(a, header);
		}
		else if (x == 'f') 
		{
			int a;	fscanf(fin, "%d", &a);
			tmp = FindPrevious(a, header);
			if (IsLast(tmp, header))
			{
				fprintf(fout, "finding(%d) failed : element %d is not in the list\n", a, a);
				//printf("finding(%d) failed : element %d is not in the list\n", a, a);
			}
			else 
			{
				if (tmp->element > 0)
				{
					fprintf(fout, "key of the previous node of %d is %d\n", a, tmp->element);
					//printf("key of the previous node of %d is %d\n", a, tmp->element);
				}
				else
				{
					fprintf(fout, "key of the previous node of %d is head\n", a);
					//printf("key of the previous node of %d is head\n", a);
				}
			}
		}
		else if (x == 'p') 
		{
			if (IsEmpty(header)==0)
			{
				fprintf(fout, "empty list!\n");
				//printf("empty list!\n");
			}
			else
			{
				elements = GetElements(header);
				for (int i = 0; i < ListSize; i++) 
				{
					fprintf(fout, "key:%d ", elements[i]);
					//printf("key:%d ", elements[i]);
				}
				fprintf(fout, "\n");
				//printf("\n");
				free(elements);
			}
		}
	}
	DeleteList(header);
	fclose(fin);
	fclose(fout);

	return 0;
}

List MakeEmpty(List L) 
{
	L = (Node*)malloc(sizeof(Node) * 1);  // malloc
	L->element = -1;
	L->next = NULL;
	return L;
}

int IsEmpty(List L) 
{
	if (L->element == -1 && L->next == NULL)
		return 0;
	return 1;
}

int IsLast(Position P, List L) 
{
	if (P == NULL)
		return 1;
	Position tmp = Find(P->element, L);
	if (tmp->next == NULL) // last 1
		return 1;
	return 0; // last가 아니면 0
}

void Insert(ElementType X, List L, Position P) 
{
	Node* insert = (Node*)malloc(sizeof( Node));
	insert->element = X;
	insert->next = P->next;
	P->next = insert;
	ListSize += 1;
}

int* GetElements(List L) 
{
	int* elements_array = (int*)malloc(sizeof(int) * ListSize);
	
	Node* ptr = L; int idx = 0;
	while (ptr != NULL)
	{
		if (ptr->element != -1)
		{
			if (idx < ListSize)
			{
				elements_array[idx] = ptr->element;
				idx++;
				ptr = ptr->next;
			}
		}
		else
			ptr = ptr->next;
	}
	return elements_array;
}

Position FindPrevious(ElementType X, List L) 
{
	Position prev_tmp_ptr = L;
	Position tmp_ptr = prev_tmp_ptr->next;
	while (tmp_ptr != NULL)
	{
		if (tmp_ptr->element == X) // find
		{
			return prev_tmp_ptr;
		}
		else
		{
			prev_tmp_ptr = tmp_ptr;
			tmp_ptr = tmp_ptr->next;
		}
	}
	return NULL;
}

Position Find(ElementType X, List L) 
{
	Position tmp_ptr = L;
	while (tmp_ptr != NULL)
	{
		if (tmp_ptr->element == X) // find
			return tmp_ptr;
		else
		{
			tmp_ptr = tmp_ptr->next;
		}
	}
	return NULL;
}

void Delete(ElementType X, List L) 
{
	Position prev_tmp_ptr = L;
	Position tmp_ptr = prev_tmp_ptr->next;
	while (tmp_ptr != NULL)
	{
		if (tmp_ptr->element == X) // find
		{
			prev_tmp_ptr->next = tmp_ptr->next;
			free(tmp_ptr);
			ListSize -= 1;
			return;
		}
		else
		{
			prev_tmp_ptr = tmp_ptr;
			tmp_ptr = tmp_ptr->next;
		}
	}
}

void DeleteList(List L) 
{
	Position tmp_ptr = L;
	while (tmp_ptr != NULL)
	{
		Position next_ptr = tmp_ptr->next;
		free(tmp_ptr);
		tmp_ptr = next_ptr;
	}
}