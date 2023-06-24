#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

FILE* fin;
FILE* fout;

typedef struct BNode* BNodePtr;

struct BNode
{
    int order;        /*key number*/
    int size;           /* number of children */
    BNodePtr* child;    /* children pointers */
    int* key;           /* keys */
    int is_leaf;
}BNode;

BNodePtr CreateTree(int order);

void Insert(BNodePtr* root, int key);
int Find(BNodePtr root, int key);
void PrintTree(BNodePtr root);
void DeleteTree(BNodePtr root);
void SplitChild(BNodePtr node, int index);
void InsertNonFull(BNodePtr node, int key);

int main(int argc, char* argv[]) 
{
    fin = fopen(argv[1], "r");
    fout = fopen(argv[2], "w");

    int order;
    fscanf(fin, "%d", &order);
    BNodePtr root = CreateTree(order);

    char cv;
    int key;
    while (!feof(fin)) 
    {
        fscanf(fin, "%c", &cv);
        switch (cv) {
        case 'i':
            fscanf(fin, "%d", &key);
            if (Find(root, key))
                fprintf(fout, "insert error : key %d is already in the tree!\n", key);
            else
                Insert(&root, key);
            break;
        case 'f':
            fscanf(fin, "%d", &key);
            if (Find(root, key))
                fprintf(fout, "key %d found\n", key);
            else
                fprintf(fout, "finding error : key %d is not in the tree!\n", key);
            break;
        case 'p':
            if (root->size == 1)
                fprintf(fout, "print error : tree is empty!");
            else
                PrintTree(root);
            fprintf(fout, "\n");
            break;
        }
    }

    DeleteTree(root);
    fclose(fin);
    fclose(fout);

    return 0;
}

/*
Create new BTree with given order
order: order of BTree (order >= 2) 
return:
        the pointer of new BTree
 */

BNodePtr CreateNode(int order)
{
    BNodePtr new_Node = (BNodePtr)malloc(sizeof(BNode));
    new_Node->order = order;
    new_Node->size = 1;
    new_Node->child = (BNodePtr*)malloc(sizeof(BNodePtr*) * (order));
    new_Node->key = (int*)malloc(sizeof(int) * (order));
    new_Node->is_leaf = 1; // 일단 노드를 만들면 true니까
    for (int i = 0; i < order; i++)
    {
        new_Node->child[i] = NULL;
        new_Node->key[i] = -1;
    }
    return new_Node;
}

BNodePtr CreateTree(int order) 
{
    BNodePtr new_btree = CreateNode(order);
    return new_btree;
}


BNodePtr split_node_type1(BNodePtr root) //루트노드가 리프노드일 때 split
{
    BNodePtr parent, right_child;
    parent = CreateNode(root->order); parent->is_leaf = 0;
    right_child = CreateNode(root->order);

    int mid = root->size / 2 - 1;

    int right_idx = 0;
    for (int i = mid + 1; i < root->size-1; i++)
    {
        right_child->key[right_idx] = root->key[i];
        right_idx++; right_child->size++;

        root->key[i] = -1;
    }
    root->size -= right_child->size;

    parent->key[0] = root->key[mid]; 
    root->key[mid] = -1;
    parent->size += 1;

    parent->child[0] = root;
    parent->child[1] = right_child;

    return parent;
}

BNodePtr split_node_type2(BNodePtr parent, BNodePtr child)  // parent가 full이 아닐때 split
{
    BNodePtr right_child = CreateNode(parent->order);

    int mid = child->size / 2 - 1;

    for (int i = 0; i < parent->size; i++)
    {
        if (parent->key[i] == -1) // parent 노드의 맨 뒤에서 split 할때
        {
            parent->key[i] = child->key[mid];
            parent->size++;
            child->key[mid] = -1;

            int right_idx = 0;
            for (int t = mid+1; t < child->size-1; t++)
            {
                right_child->key[right_idx] = child->key[t];
                right_child->size++; right_idx++;
                child->key[t] = -1;
            }
            child->size -= right_child->size;

            parent->child[i + 1] = right_child;
            return parent;
        }
        else if (child->key[0] < parent->key[i])
        {
            // 공간확보
            for (int t = parent->size - 1; t > i; t--)
            {
                parent->key[t] = parent->key[t - 1];
                parent->child[t + 1] = parent->child[t];
            }
            parent->key[i] = child->key[mid];
            parent->size += 1;
            child->key[mid] = -1;

            int right_idx = 0;
            for (int t = mid + 1; t < child->size - 1; t++)
            {
                right_child->key[right_idx] = child->key[t];
                right_child->size++; right_idx++;
                child->key[t] = -1;
            }
            child->size -= right_child->size;

            parent->child[i + 1] = right_child;
            return parent;
        }
    }
}

BNodePtr find_prev_node(BNodePtr root, int key)
{
    if (root == NULL)
        return NULL;
    BNodePtr tmp = root;
    BNodePtr prev = root;

    while (tmp->is_leaf == 0)
    {
        int check = 1;

        for (int i = 0; i < tmp->size; i++)
        {
            if (tmp->key[i] == key)
                return prev;
            if (tmp->key[i] == -1 || key < tmp->key[i])
            {
                prev = tmp;
                tmp = tmp->child[i];
                check = 0;
                break;
            }
        }
        if(check ==1)
            tmp = tmp->child[tmp->size - 1];
    }
    return prev;
}

BNodePtr data_input(BNodePtr root, int key)
{
    for (int i = 0; i < root->size; i++)
    {
        if (root->key[i] == -1)
        {
            root->key[i] = key;
            root->size += 1;
            return root;
        }
        else if (key < root->key[i])
        {
            for (int t = root->size - 1; t > i; t--)
            {
                root->key[t] = root->key[t - 1];
            }
            root->key[i] = key;
            root->size += 1;
            return root;
        }
    }
}


void Print_now(BNodePtr node)
{
    if (node != NULL)
    {
        for (int i = 0; i < node->size; i++)
        {
            printf("%d ", node->key[i]);
        }
        printf("\n");

        if (!node->is_leaf)
        {
            for (int i = 0; i < node->size; i++)
            {
                Print_now(node->child[i]);
            }
        }
    }
}

BNodePtr Node_Full_split(BNodePtr full_node, BNodePtr root)
{
    BNodePtr left_child, right_child;
    left_child = CreateNode(full_node->order);
    right_child = CreateNode(full_node->order);

    left_child->is_leaf = 0;
    right_child->is_leaf = 0;

    int mid = full_node->size / 2 - 1;
    for (int i = 0; i < full_node->size-1; i++)
    {
        if (i < mid)
        {
            left_child->key[i] = full_node->key[i];
            left_child->child[i] = full_node->child[i];
            left_child->size++;
        }
        else if(i > mid)
        {
            right_child->key[i-mid-1] = full_node->key[i];
            right_child->child[i-mid-1] = full_node->child[i];
            right_child->size++;
        }
    }

    left_child->child[left_child->size -1] = full_node->child[mid];
    right_child->child[right_child->size - 1] = full_node->child[full_node->size-1];

    int mid_num = full_node->key[mid]; int order = full_node->order;
    BNodePtr parent_node = find_prev_node(root, full_node->key[0]);

    if (parent_node == full_node) // 새로 부모 노드 생성
    {
        BNodePtr root = CreateNode(order);
        root->is_leaf = 0;
        root->key[0] = mid_num;
        root->child[0] = left_child;
        root->child[1] = right_child;
        root->size = 2;
        free(full_node);
        return root;
    }
    else // 부모 노드에 mid 넣기
    {
        free(full_node);
        for (int i = 0; i < parent_node->size; i++)
        {
            if (parent_node->key[i] == -1)
            {
                parent_node->key[i] = mid_num; parent_node->size++;
                parent_node->child[i] = left_child;
                parent_node->child[i + 1] = right_child;

                break;
            }
            else if (mid_num < parent_node->key[i])
            {
                // 공간확보
                for (int t = parent_node->size - 1; t > i; t--)
                {
                    parent_node->key[t] = parent_node->key[t - 1];
                    parent_node->child[t + 1] = parent_node->child[t];
                }
                parent_node->key[i] = mid_num;
                parent_node->size += 1;
                parent_node->child[i] = left_child;
                parent_node->child[i + 1] = right_child;
                break;
            }
        }
        if (parent_node->size > parent_node->order)   // parent 노드의 full 여부 체크
        {
            root = Node_Full_split(parent_node, root);
        }
        return root;
    }
}

/*
Insert the key value into BTree
key: the key value in BTree node
*/
void Insert(BNodePtr* root, int key)
{
    if ((*root)->is_leaf == 1)
    {
        (*root) = data_input((*root), key);

        if ((*root)->size == (*root)->order + 1)// split 필요
        {
            (*root) = split_node_type1((*root));
        }
    }
    else if((*root)->is_leaf == 0)
    {
        BNodePtr tmp = find_prev_node((*root), key);
        BNodePtr child = NULL;

        for (int i = 0; i < tmp->size; i++)
        {
            if (tmp->key[i] == -1 || key < tmp->key[i])
            {
                child = tmp->child[i];
                child = data_input(child, key);
                break;
            }
        }

        if (child->size >= child->order + 1) // split 필요
        {
             if (tmp->size <= tmp->order) // split 하고 중간값을 부모노드에 삽입
            {
                tmp = split_node_type2(tmp, child);
            }

            if (tmp->size > tmp->order)// parent 노드의 full 여부 체크
            {
                (*root) = Node_Full_split(tmp, *root);
            }
        }
    }

    printf("insert : %d\n" ,key);
    Print_now((*root));
    printf("\n");
}

/*
Find node that has key in BTree
key: the key value in BTree node
1이면 find, 0 is not find
*/
int Find(BNodePtr root, int key) 
{
    for (int i = 0; i < root->size; i++)
    {
        if (root->key[i] == -1 || key < root->key[i])
        {
            if (root->child[i] == NULL)
            {
                return 0;
            }
            else
            {
                return Find(root->child[i],key);
            }
        }
        else if (key == root->key[i])
        {
            return 1;
        }
    }
}

/*
Print Tree, inorder traversal
left -> root -> right
*/
void PrintTree(BNodePtr root) 
{
    for (int i = 0; i < root->size-1; i++)
    {
        if (root->is_leaf == 1) // 리프라면 전부 출력
        {
            for (int t = 0; t < root->size-1; t++)
            {
                fprintf(fout, "%d ", root->key[t]);
            }
            return;
        }
        else if(root->is_leaf == 0)
        {
            PrintTree(root->child[i]);
        }
        fprintf(fout, "%d ", root->key[i]);
    }

    PrintTree(root->child[root->size-1]);
}

/*
Free memory, delete a BTree completely
*/
void DeleteTree(BNodePtr root) 
{
    if (root == NULL)
        return;

    if (root->is_leaf == 0)
    {
        for (int i = 0; i < root->size; i++)
        {
            DeleteTree(root->child[i]);
        }
    }
    free(root->key);
    free(root->child);
    free(root);
}
