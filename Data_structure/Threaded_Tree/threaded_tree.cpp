#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

FILE* fin;
FILE* fout;

#define FROMPARENT 0
#define FROMTHREAD 1

typedef struct ThreadedTree* ThreadedPtr;
typedef int ElementType;

typedef struct ThreadedTree 
{
	int left_thread; // flag if ptr is thread, 1, if it is a thread or 0, if it points to a child node
	ThreadedPtr left_child;
	ElementType data;
	ThreadedPtr right_child;
	int right_thread; // flag if ptr is thread, 1, if it is a thread or 0, if it points to a child node
}ThreadedTree;

/*
Create a root of new Threaded Tree
Root data should be -1
return:
	the pointer of new Threaded Tree
*/
ThreadedPtr CreateTree() 
{
	ThreadedTree* new_root = (ThreadedTree*)malloc(sizeof(ThreadedTree));
	new_root->left_thread = 1;
	new_root->left_child = new_root;
	new_root->data = -1;
	new_root->right_child = new_root;
	new_root->right_thread = 1;
	
	return new_root;
}


/*
Insert the key value "data" in Threaded Tree
root : Pointer to the root node of Threaded Tree
root_idx : Index of the root node of Threaded Tree, means the first node to find the insertion position
data : data key value of the node to be newly inserted,
idx : The index of the node to be newly inserted, 0 means root index
return :
	1, the insertion succeeds
	0, the insertion fails.
*/

int Insert(ThreadedPtr root, int root_idx, ElementType data, int idx) 
{
	ThreadedTree* Node = (ThreadedTree*)malloc(sizeof(ThreadedTree));
	Node->left_thread = 1;
	Node->left_child = NULL;
	Node->data = data;
	Node->right_child = NULL;
	Node->right_thread = 1;

	// Ʈ���� ����ִ� ��� ���ο� ��带 ��Ʈ�� �����Ѵ�.
	if (root_idx == idx-1) 
	{
		root->right_child = Node;
		root->right_thread = 0;
		Node->left_child = root;
		Node->right_child = root;

		return 1;
	}

	//// insert ��ġ ã��
	int arr[8] = { -1, -1,-1,-1,-1, -1,-1,-1 };
	int arr_idx = 0;
	while (idx != 1)
	{
		int tmp = idx % 2;
		idx = idx / 2;

		arr[arr_idx] = tmp;
		arr_idx++;
	}

	ThreadedPtr tmp_node = root;
	for (int i = arr_idx; i > 0; i--)
	{
		if (arr[i] == 0) // ����
		{
			tmp_node = tmp_node->left_child;
		}
		else if(arr[i] == 1) // ������
		{
			tmp_node = tmp_node->right_child;
		}
		else
		{
			tmp_node = tmp_node->right_child;
		}
	}

	// tmp_node�� ���ο� ����� �θ���� �����ȴ�.
	if(arr[0] == 0) // tmp_node�� ���ʿ� ����
	{
		Node->left_child = tmp_node->left_child;
		tmp_node->left_child = Node;
		Node->right_child = tmp_node;
		tmp_node->left_thread = 0; // �ڽ��� ���ܼ�
		return 1;
	}
	else if (arr[0] == 1)
	{
		Node->right_child = tmp_node->right_child;
		tmp_node->right_child = Node;
		Node->left_child = tmp_node;
		tmp_node->right_thread = 0;
		return 1;
	}

	return 0; // ����
}


/*
In Order Traversal
Implementing in a recursive form is prohibited.
When printing out, the interval between each key is one space
print out:
	"inorder traversal : data1 data2 data3" (When there are 3 data, except root node)

*/
void printInorder(ThreadedPtr root)
{
	fprintf(fout, "inorder traversal : ");

	ThreadedPtr curr = root->right_child;
	while (curr != NULL) 
	{
		while (curr->left_thread == 0)   // ���� ���� ���� node���� ����.
		{
			curr = curr->left_child;
		}
		fprintf(fout, "%d ",curr->data); // print the current node
		while (curr->right_thread == 1) // ������ ����� �̵�
		{ 
			curr = curr->right_child;
			if (curr->data == -1) // ������ �� �� ��带 ����ϰ� �� �� �� ���� ��尡 -1�̶�� ��ü �� ���ұ⿡ return �ع�����.
				return;
			fprintf(fout, "%d ", curr->data); // ������
		}
		curr = curr->right_child; // ������ ���� �̵�
	}
}

// insert�� ������ �Ǿ����� Ȯ���� ���� �Լ� - �����ʹ� ��� ����.
void print_tree(ThreadedPtr root)
{
	printf("%d", root->data);
	if (root->left_thread == 0)
	{
		print_tree(root->left_child);
	}
	if (root->right_thread == 0)
	{
		print_tree(root->right_child);
	}

}

/*
Delete the Tree
*/
void DeleteTree(ThreadedPtr root) 
{
	if (root->left_thread == 0)
	{
		DeleteTree(root->left_child);
	}
	if (root->right_thread == 0)
	{
		DeleteTree(root->right_child);
	}

	free(root);
}



int main(int argc, char* argv[]) 
{
	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");

	ThreadedPtr root = CreateTree();

	int NUM_NODES;
	fscanf(fin, "%d", &NUM_NODES);

	int root_idx = 0, idx = 0;

	while (++idx <= NUM_NODES) 
	{
		ElementType data;
		fscanf(fin, "%d", &data);

		if (Insert(root, root_idx, data, idx) == 0) 
		{
			fprintf(fout, "Insertion failed!\n");
			return 0;
		}
	}

	printInorder(root);
	DeleteTree(root);

	fclose(fin);
	fclose(fout);

	return 0;
}
