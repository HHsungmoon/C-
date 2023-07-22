#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

FILE* fin;
FILE* fout;

using namespace std;

typedef struct BNode
{
    int is_leaf;
    int num_keys;        /* max key number*/

    vector<BNode*> child;    /* children pointers */
    vector<int> keys;     /* keys */
    
    BNode* prev;
    BNode* left;    /* ������尡 true�϶�: is_leaf�� 1�϶� */
    BNode* right;
}BNode;


BNode* CreateNode(int num_keys, bool is_leaf)
{
    BNode* node = new BNode;
    node->is_leaf = is_leaf;
    node->num_keys = num_keys;
    node->prev = NULL;
    node->left = NULL;
    node->right = NULL;

    return node;
}

// key �� ���� Ʈ���� �ִ��� ���θ� Ȯ���ϴ� �Լ�.
int Find(BNode* root, int key)
{
    if (root == NULL)
        return 0;

    if (root->is_leaf == 1)
    {
        for (int i = 0; i < root->keys.size(); i++)
        {
            if (key == root->keys[i])
                return 1;
        }
        return 0;
    }
    else
    {
        if (root->keys.back() <= key)
        {
            return Find(root->child.back(), key);
        }
        else
        {
            for (int i = 0; i < root->keys.size(); i++)
            {
                if (key < root->keys[i])
                {
                    return Find(root->child[i], key);
                }
            }
        }
    }
}

// ã���� �ϴ� ���� �ִ� Leaf_node�� ã�ư��� �Լ�
BNode* find_leaf_node(BNode* root, int key)
{
    while (root->is_leaf == 0)
    {
        if (root->keys[root->keys.size()-1] <= key)
        {
            root = root->child[root->child.size()-1];
        }
        else
        {
            for (int i = 0; i < root->keys.size(); i++)
            {
                if (key < root->keys[i])
                {
                    root = root->child[i];
                    break;
                }
            }
        }
    }
    return root;
}

// CMD �ܼ�â�� ���� B+Tree�� ���
void CMD_print_inorder(BNode* node)
{
    if (node != NULL)
    {
        if (node->left != NULL && node->is_leaf == 1)
            std::cout << "left:" << node->left->keys[0] << "/ ";

        for (int i = 0; i < node->keys.size(); i++)
        {
            std::cout << node->keys[i] << " ";
        }
        if (node->right != NULL && node->is_leaf == 1)
            std::cout << "right:" << node->right->keys[0] << "/ ";
        std::cout << endl;

        if (!node->is_leaf)
        {
            for (int i = 0; i < node->child.size(); i++)
            {
                CMD_print_inorder(node->child[i]);
            }
        }
    }
}

// .txt ���Ͽ� ���� B+Tree�� ���
void File_print_inorder(BNode* root)
{
    if (root != NULL)
    {
        if (root->left != NULL && root->is_leaf == 1)
            fprintf(fout, "L: %d /", root->left->keys[0]);

        for (int i = 0; i < root->keys.size(); i++)
        {
            fprintf(fout, "%d ", root->keys[i]);
        }
        if (root->right != NULL && root->is_leaf == 1)
            fprintf(fout, "R: %d /", root->right->keys[0]);
        fprintf(fout, "\n");

        if (!root->is_leaf)
        {
            for (int i = 0; i < root->child.size(); i++)
            {
                File_print_inorder(root->child[i]);
            }
        }
    }
}

// CMD �ܼ�â�� ���� B+Tree�� ��� �ϴµ� layer�� �������� root���� 1�پ� ���
void CMD_print_layer_type(BNode* root)
{
    BNode* node = root;
    BNode* tmp = root;

    while (1)
    {
        tmp = node;
        while (tmp != NULL)
        {
            cout << "[";
            for (int i = 0; i < tmp->keys.size(); i++)
            {
                cout << tmp->keys[i] << " ";
            }
            cout << "]-";
            tmp = tmp->right;
        }
        cout << "|" << endl;

        if (node->child.empty() == true)
            return;
        else
        {
            node = node->child[0];
        }
    }
    
}

// insert, delete ��Ȳ���� ������ ��ȭ�� �ִ� Leaf_node�� �¿� ��带 Ȯ���ϴ� �Լ�
bool Insertion_left_right_check(BNode* tmp, int max_M)
{
    if (tmp->left != NULL && tmp->left->keys.size() < max_M)
        return true;
    else if (tmp->right != NULL && tmp->right->keys.size() < max_M)
        return true;
    return false;
}
bool Deletion_left_right_check(BNode* tmp, int min_M)
{
    if (tmp->left != NULL && tmp->left->keys.size() > min_M)
        return true;
    else if (tmp->right != NULL && tmp->right->keys.size() > min_M)
        return true;
    return false;
}

// leaf_node�� �� ���� key�� �ٲ�鼭 parent�� �ִ� key�� �˸°� �ٲ��ִ� �Լ�
BNode* update_parent_node(BNode* root, BNode* leaf_prev_node, int change_key, int update_key)
{
    for (int i = 0; i < leaf_prev_node->keys.size(); i++)
    {
        if (leaf_prev_node->keys[i] == change_key)
        {
            leaf_prev_node->keys[i] = update_key;
            return root;
        }
        if (leaf_prev_node->keys[i] > change_key)
        {
            if (root != leaf_prev_node)
                update_parent_node(root, leaf_prev_node->prev, change_key, update_key);
        }
    }
    return root;
}

// insert key �Լ�. �˸��� ��ġ�� �����͸� �����Ѵ�.
BNode* data_insert(BNode* root, BNode* Leaf_node, int key)
{
    if (Leaf_node->keys[Leaf_node->keys.size() - 1] <= key) // ���� �ڿ� insert
    {
        Leaf_node->keys.push_back(key);
    }
    else if (Leaf_node->keys[0] > key) // ���� �տ� insert
    {
        Leaf_node->keys.insert(Leaf_node->keys.begin(), key);
        // �θ�Ű ����
        if (Leaf_node->prev->child[0] != Leaf_node)
            root = update_parent_node(root, Leaf_node->prev, Leaf_node->keys[1], Leaf_node->keys[0]);
    }
    else  // �߰��� insert
    {
        for (int i = 0; i < Leaf_node->keys.size(); i++)
        {
            if (Leaf_node->keys[i] > key)
            {
                Leaf_node->keys.insert(Leaf_node->keys.begin() + i, key);
                break;
            }
        }
    }

    return root;
}

// ���� ù��° node split�� �����ϴ� �Լ�. root ��尡 leaf_node�϶���
BNode* Leaf_node_split_type1(BNode* root)
{
    BNode* pnode = CreateNode(root->num_keys, 0);
    BNode* new_node = CreateNode(root->num_keys, 1);

    int len = root->num_keys /2 ;
    //new_node->keys.assign(root->keys.begin()+len, root->keys.end());

    for (int i = len; i < root->num_keys; i++)
    {
        new_node->keys.push_back(root->keys[i]);
    }
    for (int i = len; i < root->num_keys; i++)
    {
        root->keys.pop_back();
    }

    pnode->keys.push_back(new_node->keys[0]);
    pnode->child.push_back(root);
    pnode->child.push_back(new_node);

    root->prev = pnode;
    new_node->prev = pnode;
    root->right = new_node;
    new_node->left = root;

    return pnode;
}

// Insertion_nodesplit_type2 �Լ� ����������� �θ��尡 full�� �Ǿ��� �� �θ��� split ���. ���ο� ��带 ����� root�� ����� �ش�.
BNode* parent_node_split_type1(BNode* root)
{
    BNode* pnode = CreateNode(root->num_keys, 0);
    BNode* new_node = CreateNode(root->num_keys, 0);

    int mid = root->num_keys / 2;

    for (int i = mid+1; i < root->num_keys; i++)
    {
        new_node->keys.insert(new_node->keys.begin(), root->keys.back());
        root->keys.pop_back();
    }
    for (int i = mid+1; i < root->num_keys +1; i++)
    {
        new_node->child.insert(new_node->child.begin(), root->child.back());
        root->child.back()->prev = new_node;
        root->child.pop_back();
    }

    pnode->keys.push_back(root->keys[mid]);
    root->keys.pop_back();
    pnode->child.push_back(root);
    pnode->child.push_back(new_node);

    root->prev = pnode;
    new_node->prev = pnode;

    root->right = new_node;
    new_node->left = root;

    return pnode;
}

// Insertion_nodesplit_type2 �Լ� ����������� �θ��尡 full�� �Ǿ��� ��, ���ο� �θ� ��� ���� ���� split �Ѵ�.
BNode* parent_node_change_type1(BNode* prev, BNode* split)
{
    BNode* new_node = CreateNode(split->num_keys, 0);
    new_node->prev = prev;
    split->right = new_node;
    new_node->left = split;
    int mid = split->num_keys / 2;

    for (int i = mid + 1; i < split->num_keys; i++)
    {
        new_node->keys.insert(new_node->keys.begin(), split->keys.back());
        split->keys.pop_back();
    }
    for (int i = mid + 1; i < split->num_keys + 1; i++)
    {
        new_node->child.insert(new_node->child.begin(), split->child.back());
        split->child.back()->prev = new_node;
        split->child.pop_back();
    }
    
    int i = 0;
    if (prev->child[0] == split)
    {
        prev->keys.insert(prev->keys.begin(), split->keys[mid]);
        prev->child.insert(prev->child.begin() + 1, new_node);
    }
    else if (prev->child.back() == split)
    {
        prev->keys.push_back(split->keys[mid]);
        prev->child.push_back(new_node);
    }
    else
    {
        for (i = 0; i < prev->child.size(); i++)
        {
            if (prev->child[i] == split)
                break;
        }
        prev->keys.insert(prev->keys.begin() + i, split->keys[mid]);
        prev->child.insert(prev->child.begin() + i + 1, new_node);
    }
    split->keys.pop_back();
    return prev;
}

// root��尡 leaf_node�� �ƴҶ� leaf_node�� split �ϴ� �Լ�. 
BNode* Leaf_node_split_type2(BNode* root, BNode* prev, BNode* Leaf_node)
{
    BNode* new_node = CreateNode(Leaf_node->num_keys, 1);

    int len = Leaf_node->num_keys / 2;
    for (int i = len; i < Leaf_node->num_keys; i++)
    {
        new_node->keys.insert(new_node->keys.begin(), Leaf_node->keys.back()); 
        Leaf_node->keys.pop_back();
    }

    for (int i = 0; i < prev->child.size(); i++)
    {
        if (prev->child[i] == Leaf_node)
        {
            prev->keys.insert(prev->keys.begin() + i, new_node->keys[0]);
            prev->child.insert(prev->child.begin() + i + 1, new_node);
            break;
        }
    }

    new_node->right = Leaf_node->right;
    Leaf_node->right = new_node;
    new_node->left = Leaf_node;
    if (new_node->right != NULL)
        new_node->right->left = new_node;
    new_node->prev = Leaf_node->prev;

    BNode* tmp = prev;
    while (tmp->keys.size() == tmp->num_keys) // prev��� split �ʿ�
    {
        if (tmp->prev != NULL)
            tmp = tmp->prev;
        if (tmp == root && tmp->keys.size() == tmp->num_keys) // root�� prev�� ����
        {
            // ���ο� prev ��带 ���� split
            root = parent_node_split_type1(root);
            break;
        }
        else
        {
            tmp = parent_node_change_type1(tmp, prev);
            prev = prev->prev;
        }
    }

    return root;
}


// ���� leaf_node�� full�϶� �¿� ��忡 ������� �ִٸ� �Ѱ��ش�.
BNode* left_right_key_move(BNode* root, BNode* Leaf_node)
{
    BNode* left_node = Leaf_node->left;
    BNode* right_node = Leaf_node->right;

    if (left_node != NULL && left_node->keys.size() < Leaf_node->num_keys -1) // left���� key �Ѱ��ֱ�
    {
        int change_key = Leaf_node->keys[0];
        left_node->keys.push_back(Leaf_node->keys[0]);
        Leaf_node->keys.erase(Leaf_node->keys.begin());
        
        root = update_parent_node(root, Leaf_node->prev, change_key, Leaf_node->keys[0]);
    }
    else if (right_node != NULL && right_node->keys.size() < Leaf_node->num_keys-1) // right���� key �Ѱ��ֱ�
    {
        int change_key = Leaf_node->keys.back();
        right_node->keys.insert(right_node->keys.begin(), change_key);
        Leaf_node->keys.pop_back();
   
        root = update_parent_node(root, Leaf_node->right->prev, right_node->keys[1], right_node->keys[0]);
    }
    return root;
}

// key insert ���� �Լ�. root�� leafnode�϶��� �ƴҶ��� ������ �˰��� ����
BNode* Insert(BNode* root, int key)
{
    //std::cout << "insert " << key << endl;
    if (root->is_leaf == 1) // insert ����
    {
        if (root->keys.size() == 0 || root->keys[root->keys.size() - 1] <= key)
        {
            root->keys.push_back(key);
        }
        else
        {
            int i;
            for (i = 0; i < root->keys.size(); i++)
            {
                if (root->keys[i] >= key)
                {
                    root->keys.insert(root->keys.begin() + i, key);
                    break;
                }
            }
        }
        // split check
        if (root->keys.size() >= root->num_keys)
        {
            root = Leaf_node_split_type1(root);
        }
        //Print_now(root); std::cout << endl;
        return root;
    }
    else if (root->is_leaf == 0) // leaf������ Ž��
    {
        BNode* Leaf_node = find_leaf_node(root, key);
        if (key == 9114)
            cout << endl;
        // data input
        root = data_insert(root, Leaf_node, key);
        
        // node is full -> split, left-right move
        if (Leaf_node->keys.size() >= Leaf_node->num_keys) 
        {
            //  key ���� �¿� ��忡 �Ѱ��ֱ�
            if (Insertion_left_right_check(Leaf_node, Leaf_node->num_keys - 1) == true)
            {
                root = left_right_key_move(root, Leaf_node);
            }
            else // left, right ��忡 �Ѱ��� �� ���ٸ� node split
            {
                root = Leaf_node_split_type2(root, Leaf_node->prev, Leaf_node);
            }
        }

        //Print_now(root); std::cout << endl;
        //Print_right_key_type(root); cout << endl;
        return root;
    }
}

// key_delete �Լ����� node�� 0�� key ������  prev��� ������Ʈ �����ϴ� �Լ�
BNode* Delete_prev_key_update(BNode* root, BNode* tmp, int old_key)
{
    BNode* target_node = tmp->prev;
    while (std::find(target_node->keys.begin(), target_node->keys.end(), old_key) == target_node->keys.end())
    {
        target_node = target_node->prev;
    }

    std::replace(target_node->keys.begin(), target_node->keys.end(), old_key, tmp->keys[0]);

    return root;
}

// ���� tree���� key���� ����� �Լ�. leaf_node 0�� key ������ prev��尪 ������Ʈ�� ����
BNode* key_delete(BNode* root, BNode* tmp, int key)
{
    if (tmp->keys[0] == key) // �� �� ����
    {
        // prev update �ʿ�
        int change_prev_key = tmp->keys[0];
        tmp->keys.erase(tmp->keys.begin());
        if (tmp != root && tmp->left != NULL)
            root = Delete_prev_key_update(root, tmp, change_prev_key);
    }
    else
    {
        auto it = std::find(tmp->keys.begin(), tmp->keys.end(), key);
        if (it != tmp->keys.end())
            tmp->keys.erase(it);
    }
    return root;
}


// key ������ min_M���� ���� key�� leaf_node�� Merge
BNode* Merge_Leaf_node(BNode* root, BNode* tmp)
{
    //// merge�� tmp�� ���� ���� �Ѵ�. tmp�� ���� ���� ��� ����
    BNode* prev_tmp = tmp->prev;
    if (tmp == prev_tmp->child[0]) // tmp�� prev�� ���� ���� �����, ������ ���� merge
    {
        for (int i = 0; i < tmp->keys.size(); i++)
        {
            tmp->right->keys.insert(tmp->right->keys.begin(), tmp->keys.back());
            tmp->keys.pop_back();
        }

        if (tmp->left == NULL) // B+ Ʈ���� ���� ���ʳ��
        {
            tmp->right->left = NULL;
        }
        else
        {
            tmp->left->right = tmp->right;
            tmp->right->left = tmp->left;
        }
        
        delete(prev_tmp->child[0]);
        prev_tmp->keys.erase(prev_tmp->keys.begin());
        prev_tmp->child.erase(prev_tmp->child.begin());
    }
    else
    {
        for (int i = 0; i < tmp->keys.size(); i++)
        {
            tmp->left->keys.push_back(tmp->keys[i]);
        }

        if (tmp->right == NULL) // B+ Ʈ���� ���� ������ leaf���
        {
            tmp->left->right = NULL;
        }
        else
        {
            tmp->left->right = tmp->right;
            tmp->right->left = tmp->left;
        }
        
        for (int i = 1; i < prev_tmp->child.size(); i++)
        {
            if (tmp == prev_tmp->child[i])
            {
                delete(prev_tmp->child[i]);
                prev_tmp->keys.erase(prev_tmp->keys.begin() + i - 1);
                prev_tmp->child.erase(prev_tmp->child.begin() + i);
                break;
            }
        }
    }
    return root;
}

// leaf_node merge�� ���� parent ����� key�� min_M���� ��������, left,right ��忡�� key�� ������ �� ���ٸ� parent ��带 Merge�Ѵ�.
BNode* Merge_parent_node(BNode* root, BNode* node)
{
    // ���� ���� ��常 ������ ���� merge, �������� �ڽ��� ���� ���� merge
    if (node->prev->child[0] != node)
    {
        node = node->left;
    }

    for (int i = 0; i < node->prev->keys.size(); i++)
    {
        if (node->prev->keys[i] <= node->right->keys[0])
        {
            node->keys.push_back(node->prev->keys[i]);
            node->prev->keys.erase(node->prev->keys.begin()+i);
            node->prev->child.erase(node->prev->child.begin() + i+1);
            break;
        }
    }

    for (int i = 0; i < node->right->keys.size(); i++)
        node->keys.push_back(node->right->keys[i]);        
    for (int i = 0; i < node->right->child.size(); i++)
        node->child.push_back(node->right->child[i]);
        
    BNode* tmp_d = node->right;
    if (node->right->right != NULL)
    {
        node->right = node->right->right;
        node->right->right->left = node;
    }
    else
    {
        node->right = NULL;
        // node->prev�� 1�̶�� �ǹ��ε� �̴� node->prev�� root�̱� ������ merge�ÿ� root�� ����
        delete(root);
        root = node;//����
        node->prev = NULL;
    }

    delete(tmp_d);

    return root;
}

// ������ ��尪�� �������鼭 right����� prev��� ���� ������Ʈ �Ҷ� ���. deletion_parent_left_right_move()���� ���
BNode* right_key_move_parent_change(BNode* root, BNode* tmp, int target_key, int change_key)
{
    while (tmp != NULL)
    {
        for (int i = 0; i < tmp->keys.size(); i++)
        {
            if (tmp->keys[i] == target_key)
            {
                tmp->keys[i] = change_key;
                return root;
            }
        }
        tmp = tmp->prev;
    }
    return root;
}

// left, right ��忡�� key�� �޾ƿ´�. Leaf_node ��Ȳ����
BNode* deletion_left_right_move(BNode* root, BNode* tmp, int min_M)
{
    if (tmp->left != NULL && tmp->left->keys.size() > min_M)
    {
        // left�� �� ���� key�� �̵��ϱ�
        tmp->keys.insert(tmp->keys.begin(), tmp->left->keys[tmp->left->keys.size() - 1]);
        tmp->left->keys.pop_back();
        root = Delete_prev_key_update(root, tmp, tmp->keys[1]);
    }
    else if (tmp->right != NULL && tmp->right->keys.size() > min_M)
    {
        int old_key = tmp->right->keys[0];
        tmp->keys.push_back(tmp->right->keys[0]);
        tmp->right->keys.erase(tmp->right->keys.begin());
        root = Delete_prev_key_update(root, tmp->right, old_key);
    }

    return root;
}

// left, right ��忡�� key�� �޾ƿ´�. parent_node ��Ȳ����
BNode* deletion_parent_left_right_move(BNode* root, BNode* tmp_prev, int min_M)
{
    if (Deletion_left_right_check(tmp_prev, min_M) == true)
    {
        if (tmp_prev->left != NULL && tmp_prev->left->keys.size() > min_M)
        {
            tmp_prev->right->keys.push_back(tmp_prev->keys.back());
            tmp_prev->right->child.push_back(tmp_prev->child.back());
            tmp_prev->keys.pop_back();
            tmp_prev->child.pop_back();
        }
        else if (tmp_prev->right != NULL && tmp_prev->right->keys.size() > min_M)
        {
            BNode* move_node = tmp_prev->right->child[0];
            root = right_key_move_parent_change(root, move_node->prev->prev, move_node->keys[0], move_node->prev->keys[0]);

            tmp_prev->keys.push_back(move_node->keys[0]);
            tmp_prev->child.push_back(move_node);
            move_node->prev = tmp_prev;

            tmp_prev->right->keys.erase(tmp_prev->right->keys.begin());
            tmp_prev->right->child.erase(tmp_prev->right->child.begin());
        }
    }
    return root;
}

// key delete �����Լ�.
BNode* Delete(BNode* root, int key)
{
    //std::cout << "delete: " << key << endl;

    int min_M = root->num_keys / 2;
    BNode* tmp = find_leaf_node(root, key);

    // 1. delete ����
    root = key_delete(root, tmp,key);
    
    // 2. M/2 ���� ��������  - leaf_node ó���κ�
    if (tmp->keys.size() < min_M && tmp != root)
    {
        // 2-1. left-right Ȯ���ϱ�
        if (Deletion_left_right_check(tmp, min_M) == true)
        {
            root = deletion_left_right_move(root, tmp, min_M);
        }
        else  // 2-2. merge �ϱ�
        {
            BNode* tmp_prev = tmp->prev;
            //// merge�� tmp�� ���� ���� �Ѵ�. tmp�� ���� ���� ��� ����
            root = Merge_Leaf_node(root, tmp);
            
            // merge���Ŀ� prev��� ������ M/2���� ���ٸ�-> left,right move �Ǵ� merge�� �ʿ��ϴٸ�!!
            if (tmp_prev->keys.size() < min_M && tmp_prev != root)
            {
                if (Deletion_left_right_check(tmp_prev, min_M) == true)
                {
                    root = deletion_parent_left_right_move(root, tmp_prev, min_M);
                }
                else
                {
                    if (tmp->prev != NULL) // tmp->prev�� null�̶�� ���� tmp�� root����� ��Ȳ�̱� ������ min_M���� ��� ������.
                        root = Merge_parent_node(root, tmp_prev);
                }
            }
        }
    }

    return root;
}

int main(int argc, char* argv[])
{
	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");

	int order;
	fscanf(fin, "%d", &order);
	BNode* root = CreateNode(order, 1);

    char cv;
    int key;
    while (!feof(fin))
    {
        fscanf(fin, "%c", &cv);
        switch (cv)
        {
        case 'i':
            fscanf(fin, "%d", &key);
            root = Insert(root, key);
            break;
        case 'd':
            fscanf(fin, "%d", &key);
            if (!Find(root, key))
            {
                fprintf(fout, "delete error : key %d is not in the tree!\n", key);
                printf("delete error : key %d is not in the tree!\n", key);
            }
            else
                root = Delete(root, key);
            break;
        case 'f':
            fscanf(fin, "%d", &key);
            if (Find(root, key))
                fprintf(fout, "key %d found\n", key);
            else
                fprintf(fout, "finding error : key %d is not in the tree!\n", key);
            break;
        case 'p':
            if (root->keys.size() == 0)
                fprintf(fout, "print error : tree is empty!");
            else
            {
                File_print_inorder(root);
                fprintf(fout, "\n");
            }
            break;
        }
    }

    cout << "Final Tree Print" << endl << endl;
    CMD_print_inorder(root); 
    cout << endl;
	return 0;
}