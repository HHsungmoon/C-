#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

FILE* fin;
FILE* fout;

typedef struct Array Array;

struct Array 
{
    int size;
    int* values;
};

Array* CreateArray(int size);
void QuickSort(Array* array, int left, int right);
int Partition(Array* array, int left, int right);
void PrintArray(Array* array, int left, int right);
void DeleteArray(Array* array);
void swap(int* a, int* b);

int main(int argc, char* argv[]) 
{
    fin = fopen(argv[1], "r");
    fout = fopen(argv[2], "w");

    int size, i;
    Array* array;

    fscanf(fin, "%d", &size);
    array = CreateArray(size);
    for (i = 0; i < size; i++) {
        fscanf(fin, "%d", &array->values[i]);
    }

    QuickSort(array, 0, size - 1);

    fprintf(fout, "\nsorting result :\n");
    PrintArray(array, 0, size - 1);

    DeleteArray(array);


    return 0;
}

/*
Create new array
input : size of the number to be sorted
output : the pointer of array
*/
Array* CreateArray(int size)
{
    Array* arr = (Array*)malloc(sizeof(Array));
    arr->size = size;
    arr->values = (int*)malloc(sizeof(int) * size);
    return arr;
}

/*
Quick sort
*/
void QuickSort(Array* array, int left, int right) 
{
    int piv_idx = Partition(array, left, right);
    if (left < piv_idx-1)
    {
        QuickSort(array, left, piv_idx - 1);
    }

    if (right > piv_idx+1)
    {
        QuickSort(array, piv_idx+1, right);
    }
    return;
}

/*
Divide into 2 sub-lists based on pivot.
+ Select right-most data as pivot
+ Print left, right, pivot index at first
+ Print array values for every swap -> Printing array values should be implemented in a PrintArray function
Print format :
    1. "left : %d, right : %d, pivot : %d\n"
    2. refered on PrintArray function
return:
    pivot index
*/
int Partition(Array* array, int left, int right) 
{
    int f_left = left;  int f_right = right;
    int pivot_idx = right; 
    int pivot = array->values[pivot_idx];
    fprintf(fout, "left : %d, right : %d, pivot : %d\n", left, right, pivot);
    right--;

    PrintArray(array, f_left, f_right);
    while (left < right)
    {
        if (array->values[left] > pivot && array->values[right] > pivot)
        {
            right--;
        }
        else if (array->values[left] < pivot && array->values[right] < pivot)
        {
            left++;
        }
        else if(array->values[left] > pivot && array->values[right] < pivot)
        {
            swap(&array->values[left], &array->values[right]);
            left++; right--;
            PrintArray(array, f_left, f_right);
        }
        else
        {
            left++; right--;
        }
    }

    if (array->values[left] > pivot)
    {
        if (pivot_idx == left)
            return pivot_idx;
        swap(&array->values[pivot_idx], &array->values[left]);
        PrintArray(array, f_left, f_right);
        return left;
    }
    else if (array->values[left] < pivot)
    {
        if (pivot_idx == left + 1)
            return pivot_idx;
        swap(&array->values[pivot_idx], &array->values[left+1]);
        PrintArray(array, f_left, f_right);
        return left + 1;
    }
}

/*
Print array values
Print format :
    “%-3s” : out of bound and should be filled with "-" charater
    “%-3d” : array values to be printed
*/
void PrintArray(Array* array, int left, int right) 
{
    for (int i = 0; i < array->size; i++)
    {
        if (i >= left && i <= right) // 범위 내의 값
        {
            fprintf(fout, "%-3d", array->values[i]);
        }
        else
        {
            fprintf(fout, "%-3s", "-");
        }
    }
    fprintf(fout, "\n");
}

/*
DeleteArray
*/
void DeleteArray(Array* array) 
{
    free(array->values);
    free(array);
}

/*
Swap values
*/
void swap(int* a, int* b) 
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
