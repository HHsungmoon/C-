#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

FILE* fin;
FILE* fout;

struct AVLNode;
typedef struct AVLNode* Position;
typedef struct AVLNode* AVLTree;
typedef int ElementType;

typedef struct AVLNode {
	ElementType element;
	AVLTree left, right;
	int height;
}AVLNode;

int Height(AVLNode* T)
{
	if (T == NULL)
		return -1;
	return T->height;
}

int Max(int a, int b) 
{
	return (a > b) ? a : b;
}

/*
Rotation functions for AVLTree
*/
AVLNode* SingleRotateWithLeft(AVLNode* node)
{
	AVLTree tmp = node->left;
	node->left = tmp->right;
	tmp->right = node;
	node->height = Max(Height(node->left), Height(node->right)) + 1;
	tmp->height = Max(Height(tmp->left), node->height) + 1;
	return tmp;
}
AVLNode* SingleRotateWithRight(AVLNode* node)
{
	AVLTree tmp = node->right;
	node->right = tmp->left;
	tmp->left = node;
	node->height = Max(Height(node->left), Height(node->right)) + 1;
	tmp->height = Max(Height(tmp->right), node->height) + 1;
	return tmp;
}
AVLNode* DoubleRotateWithLeft(AVLNode* node)
{
	node->left = SingleRotateWithRight(node->left);
	return SingleRotateWithLeft(node);
}
AVLNode* DoubleRotateWithRight(AVLNode* node)
{
	node->right = SingleRotateWithLeft(node->right);
	return SingleRotateWithRight(node);
}

/*
Insert the value X in AVLTree T
return:
	pointer of root
print out:
	"insertion error : X is already in the tree!\n" , X is already in T
*/
AVLTree Insert(ElementType X, AVLNode* T)
{
	if (T == NULL) 
	{
		T = (AVLNode*)malloc(sizeof(struct AVLNode));
		T->element = X;
		T->height = 0;
		T->left = NULL;
		T->right = NULL;
	}
	else if (X == T->element)
	{
		fprintf(fout, "insertion error : %d is already in the tree!\n", X);
		return T;
	}
	else if (X < T->element) 
	{
		T->left = Insert(X, T->left);
		if (Height(T->left) - Height(T->right) == 2) 
		{
			if (X < T->left->element)
				T = SingleRotateWithLeft(T);
			else
				T = DoubleRotateWithLeft(T);
		}
	}
	else if (X > T->element) 
	{
		T->right = Insert(X, T->right);
		if (Height(T->right) - Height(T->left) == 2) {
			if (X > T->right->element)
				T = SingleRotateWithRight(T);
			else
				T = DoubleRotateWithRight(T);
		}
	}

	T->height = Max(Height(T->left), Height(T->right)) + 1;
	return T;
}

AVLTree FindMin(AVLTree T)
{
	if (T == NULL)
		return NULL;
	else if (T->left == NULL)
		return T;
	else
		return FindMin(T->left);
}

/*
Delete the value X in AVLTree T
return:
	pointer of root
print out:
	"deletion error : X is not in the tree!\n", X is not in T
*/
AVLTree Delete(ElementType X, AVLTree T) 
{
	AVLTree temp;
	if (T == NULL) 
	{
		fprintf(fout,"deletion error : %d is not in the tree!\n", X);
		return T;
	}
	else if (X < T->element)
		T->left = Delete(X, T->left);
	else if (X > T->element)
		T->right = Delete(X, T->right);
	else if (T->left && T->right) {
		temp = FindMin(T->right);
		T->element = temp->element;
		T->right = Delete(T->element, T->right);
	}
	else {
		temp = T;
		if (T->left == NULL)
			T = T->right;
		else if (T->right == NULL)
			T = T->left;
		free(temp);
	}
	if (T == NULL)
		return T;
	T->height = Max(Height(T->left), Height(T->right)) + 1;
	if (Height(T->left) - Height(T->right) == 2) {
		if (Height(T->left->left) >= Height(T->left->right))
			T = SingleRotateWithLeft(T);
		else
			T = DoubleRotateWithLeft(T);
	}
	else if (Height(T->right) - Height(T->left) == 2) 
	{
		if (Height(T->right->right) >= Height(T->right->left))
			T = SingleRotateWithRight(T);
		else
			T = DoubleRotateWithRight(T);
	}
	return T;
}
/*
Pre order Traversal
*/
void PrintPreorder(AVLTree T) 
{
	if (T == NULL)
	{
		return;
	}

	fprintf(fout, "%d(%d) ", T->element, T->height);
	PrintPreorder(T->left);
	PrintPreorder(T->right);
}
/*
Delete Tree
free allocated memory
*/
void DeleteTree(AVLTree T) 
{
	if (T != NULL) {
		DeleteTree(T->left);
		DeleteTree(T->right);
		free(T);
	}
}


int main(int argc, char* argv[]) 
{
	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");
	AVLTree Tree = NULL;
	char cv;
	int key;

	int i = 0;

	while (!feof(fin)) 
	{
		//printf("%d: ", ++i);
		fscanf(fin, "%c", &cv);
		switch (cv) {
		case 'i':
			fscanf(fin, "%d\n", &key);
			Tree = Insert(key, Tree);
			break;
		case 'd':
			fscanf(fin, "%d\n", &key);
			Tree = Delete(key, Tree);
			break;
		}
		PrintPreorder(Tree);
		fprintf(fout, "\n");
		//printf("\n");
	}

	DeleteTree(Tree);
	fclose(fin);
	fclose(fout);
	return 0;
}
