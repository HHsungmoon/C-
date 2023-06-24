#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#define INF 1e9

FILE* fin;
FILE* fout;

typedef struct HeapStruct 
{
	int Capacity;
	int Size;
	int* Elements;
}Heap;

Heap* CreateHeap(int heapSize);
int Insert(Heap* heap, int value);
int Find(Heap* heap, int value);
int DeleteMax(Heap* heap);
int* GetElements(Heap* heap);
int IsFull(Heap* heap);
int IsEmpty(Heap* heap);
int Size(Heap* heap);

void swap(int* a, int* b) 
{
	int t = *a;
	*a = *b;
	*b = t;
}

int main(int argc, char* argv[]) 
{
	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");

	char cv;
	Heap* maxHeap;
	int heapSize, key, max_element;
	int ret;
	int* elements;
	while (!feof(fin))
	{
		fscanf(fin, "%c", &cv);
		switch (cv) 
		{
		case 'n':
			fscanf(fin, "%d", &heapSize);
			maxHeap = CreateHeap(heapSize);
			break;
		case 'i':
			fscanf(fin, "%d", &key);
			ret = Insert(maxHeap, key);
			if (ret == 0) fprintf(fout, "insert %d\n", key);
			else if (ret == 1) fprintf(fout, "insert error : heap is full\n");
			else if (ret == 2) fprintf(fout, "insert error : %d is already in the heap\n", key);
			else {
				fprintf(fout, "error: unknown return type\n");
				return -1;
			}

			break;
		case 'd':
			max_element = DeleteMax(maxHeap);
			if (max_element == 0) {
				fprintf(fout, "delete error : heap is empty\n");

			}
			else if (max_element > 0) {
				fprintf(fout, "max element : %d deleted\n", max_element);
			}
			break;
		case 'p':
			if (IsEmpty(maxHeap)) {
				fprintf(fout, "print error : heap is empty\n");
			}
			else {
				elements = GetElements(maxHeap);
				int size = Size(maxHeap);
				for (int i = 0; elements[i] > -1 && i < size; i++) {
					fprintf(fout, "%d ", elements[i]);
				}
				fprintf(fout, "\n");
				free(elements);
			}
			break;
		case 'f':
			fscanf(fin, "%d", &key);
			if (Find(maxHeap, key)) 
				fprintf(fout, "%d is in the heap\n", key);
			else 
				fprintf(fout, "finding error : %d is not in the heap\n", key);
			break;
		}
	}

	return 0;
}

/*
Create new heap with given heapSize
Element[0] should save INF
heapSize: positive integer
return:
	the pointer of new heap
*/
Heap* CreateHeap(int heapSize) 
{
	Heap* new_heap = (Heap*)malloc(sizeof(Heap));
	new_heap->Capacity = heapSize;
	new_heap->Size = 0;
	new_heap->Elements = (int*)malloc(sizeof(int) * heapSize+1);
	new_heap->Elements[0] = INF;

	return new_heap;
}

/*
Insert the value into Heap
value: positive integer
return:
	0 , success
	1 , heap is full
	2 , duplicated
*/
int Insert(Heap* heap, int value) 
{
	if (Find(heap, value) == 1) // duplicated
	{
		return 2;
	}
	if (IsFull(heap)==1) // heap is full
	{
		return 1;
	}

	// insert
	
	heap->Size += 1;
	heap->Elements[heap->Size] = value;
	
	// maxheap 조정
	for (int i = heap->Size; heap->Elements[i / 2] < value; i /= 2)
	{
		if (heap->Elements[i] > heap->Elements[i / 2]) // 큰값이 자식노드로 있는 경우이기 때문에 swap
		{
			swap(&heap->Elements[i], &heap->Elements[i / 2]);
		}
	}

	return 0;
}

/*
Find the value in Heap
return:
	1, success
	0, fail
*/
int Find(Heap* heap, int value)
{
	for (int i = 1; i <= heap->Size; i++)
	{
		if (heap->Elements[i] == value)
			return 1;
	}
	return 0;
}

/*
Delete the maximum value in Heap
return:
	Max value, success
	0, heap is empty
*/
int DeleteMax(Heap* heap) 
{
	if (IsEmpty(heap) == 1)
	{
		return 0;
	}

	int max_element = heap->Elements[1];
	int last_element = heap->Elements[heap->Size];
	heap->Size -= 1;
	int child_idx, i;

	for (i = 1; i * 2 <= heap->Size; i = child_idx)
	{
		child_idx = i * 2;
		if (child_idx < heap->Size &&heap->Elements[child_idx] < heap->Elements[child_idx + 1]) // 현재 노드의 left, right노드 비교, right가 크다면
		{
			child_idx++;
		}
		
		if (last_element < heap->Elements[child_idx])
		{
			heap->Elements[i] = heap->Elements[child_idx];
		}
		else
		{
			break;
		}
	}
	heap->Elements[i] = last_element;
	return max_element;
}

/*
Return an array of copied elements from the heap
The length of the returned array should be the same as the size of the heap
The order of the returned array should be the same as the order of heap->Elements
If heap is empty, return NULL
***WARNING***
Do not just return heap->Elements
You must copy the elements to another allocated array
*/
int* GetElements(Heap* heap) 
{
	int* arr = (int*)malloc(sizeof(int) * heap->Size);
	for (int i = 1; i <= heap->Size; i++)
	{
		arr[i - 1] = heap->Elements[i];
	}

	return arr;
}

/*
check heap is full
return:
	1, heap is full
	0, heap is not full
*/
int IsFull(Heap* heap) 
{
	if (heap->Size+1 > heap->Capacity) // heap is full
	{
		return 1;
	}
	return 0;
}

/*
check heap is empty
return:
	1, heap is empty
	0, heap is not empty
*/
int IsEmpty(Heap* heap) 
{
	if (heap->Size == 0)
		return 1;
	return 0;
}

/*
get size of heap
return:
	size of heap
*/
int Size(Heap* heap) 
{
	return heap->Size;
}



