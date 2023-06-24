#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

FILE* fin;
FILE* fout;

typedef struct BST* Tree;
typedef struct BST 
{
	int value;
	struct BST* left;
	struct BST* right;
}BST;

Tree insertNode(Tree root, int key);
Tree deleteNode(Tree root, int key);
int findNode(Tree root, int key);
void printInorder(Tree root);
void deleteTree(Tree root);

void main(int argc, char* argv[]) 
{
	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");
	char cv;
	int key;

	Tree root = NULL;

	while (!feof(fin)) 
	{
		fscanf(fin, "%c", &cv);
		switch (cv) 
		{
			case 'i':
				fscanf(fin, "%d", &key);
				if (!findNode(root, key))
					root = insertNode(root, key);
				else
					fprintf(fout, "insertion error: %d is already in the tree\n", key);
				break;
			case 'f':
				fscanf(fin, "%d", &key);
				if (findNode(root, key))
					fprintf(fout, "%d is in the tree\n", key);
				else
					fprintf(fout, "finding error: %d is not in the tree\n", key);
				break;
			case 'd':
				fscanf(fin, "%d", &key);
				if (findNode(root, key)) {
					root = deleteNode(root, key);
					fprintf(fout, "delete %d\n", key);
				}
				else {
					fprintf(fout, "deletion error: %d is not in the tree\n", key);
				}
				break;
			case 'p':
				fscanf(fin, "%c", &cv);
				if (cv == 'i') {
					if (root == NULL)
						fprintf(fout, "tree is empty");
					else
						printInorder(root);
				}
				fprintf(fout, "\n");
				break;
		}
	}
	deleteTree(root);
}
/*
Insert the value "key" in Tree "root"
Tree root : A pointer to the root node of the binary search tree.
int key : The value of the new node to insert.
return:
	pointer of root
print out:
	"insert key\n"
*/
Tree insertNode(Tree root, int key)
{
	if (root == NULL)
	{
		root = (BST*)malloc(sizeof(BST));
		root->value = key;
		root->left = NULL;
		root->right = NULL;
		fprintf(fout, "insert %d\n", root->value);
		return root;
	}

	///////
	BST* newNode = (BST*)malloc(sizeof(BST));
	newNode->value = key;
	newNode->left = NULL;
	newNode->right = NULL;

	BST* tmp = root;
	while (tmp != NULL)
	{
		if (key < tmp->value)
		{
			if (tmp->left == NULL)
			{
				tmp->left = newNode;
				fprintf(fout, "insert %d\n", newNode->value);
				return root;
			}
			else
			{
				tmp = tmp->left;
			}
		}
		else if (key > tmp->value)
		{
			if (tmp->right == NULL)
			{
				tmp->right = newNode;
				fprintf(fout, "insert %d\n", newNode->value);
				return root;
			}
			else
			{
				tmp = tmp->right;
			}
		}
	}
}
/*
Delete the value key in Tree root
Tree root : A pointer to the root node of the binary search tree.
int key : The value of the new node to be deleted.
return :
	pointer of root
*/
BST* findMinNode(BST* root)
{
	BST* tmp = root;
	while (tmp->left != NULL)
		tmp = tmp->left;
	return tmp;
}
BST* deleteNode(BST* root, int value)
{
	BST* tNode = NULL;
	if (root == NULL)
		return NULL;

	if (root->value > value)
		root->left = deleteNode(root->left, value);
	else if (root->value < value)
		root->right = deleteNode(root->right, value);
	else
	{
		// 자식 노드가 둘 다 있을 경우
		if (root->left != NULL && root->right != NULL)
		{
			tNode = findMinNode(root->right);
			root->value = tNode->value;
			root->right = deleteNode(root->right, tNode->value);
		}
		else
		{
			tNode = (root->left == NULL) ? root->right : root->left;
			free(root);
			return tNode;
		}
	}

	return root;
}
/*
Find the value key in Tree root
Tree root : A pointer to the root node of the binary search tree.
int key : The value of the node trying to find.
return :
	1, key is found
	0, key is not found
*/
int findNode(Tree root, int key) 
{
	BST* tmp = root;

	while (tmp != NULL)
	{
		if (tmp->value == key)
		{
			return 1;
		}
		else if (tmp->value > key) // 왼쪽으로 이동
		{
			if (tmp->left == NULL)
				return 0;

			tmp = tmp->left;
		}
		else if (tmp->value < key)// 오른쪽으로 이동
		{
			if (tmp->right == NULL)
				return 0;

			tmp = tmp->right;
		}
	}
	return 0;
}
/*
In Order Traversal
Tree root : A pointer to the root node of the binary search tree.
print out:
	"root->value "
*/
void printInorder(Tree root) 
{
	if (root == NULL)
	{
		return;
	}

	printInorder(root->left);
	fprintf(fout,"%d ", root->value);
	printInorder(root->right);
}
/*
Delete Tree
free allocated memory
Tree root : A pointer to the root node of the binary search tree.
*/
void deleteTree(Tree root) 
{
	if (root == NULL)
		return;
	if (root->left != NULL)
	{
		deleteTree(root->left);
		root->left = NULL;
	}

	if (root->right != NULL)
	{
		deleteTree(root->right);
		root->right = NULL;
	}

	free(root);
	return;
}
