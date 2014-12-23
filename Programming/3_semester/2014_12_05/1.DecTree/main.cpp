#include <iostream>
#include <vector>

class Node
{
public:
    Node* left_child;
    Node* right_child;
    Node* parent;
    int key;
    int priority;

    Node(int k, int p)
    {
        key = k;
        priority = p;
        left_child = 0;
        right_child = 0;
        parent = 0;
    }
};

void split(Node* root, int key, Node* &a, Node* &b)
{
    if (root == 0)
    {
        a = 0;
        b = 0;
    }
    else
    {
        if (key >= root->key)
        {
            split(root->right_child, key, root->right_child, b);
            a = root;
        }
        else
        {
            split(root->left_child, key, a, root->left_child);
            b = root;
        }
    }
}

Node* merge(Node* a, Node* b)
{
    if ((a == 0) || (b == 0))
    {
        return (a != 0) ? a : b;
    }
    if (a->priority > b->priority)
    {
        a->right_child = merge(a->right_child, b);
        return a;
    }
    else
    {
        b->left_child = merge(a, b->left_child);
        return b;
    }
}

void insert(Node* &root, int key, int priority)
{
    Node* new_node = new Node(key, priority);
    Node* t1, *t2;
    split(root, key, t1, t2);
    root = merge(t1, new_node);
    root = merge(root, t2);
}

void sortByKey(Node* start)
{
    if (start == 0)
    {
        return;
    }
    if (start->left_child != 0)
    {
        sortByKey(start->left_child);
    }
    std::cout << start->key << ' ';
    if (start->right_child != NULL)
    {
        sortByKey(start->right_child);
    }
}

int main()
{
    return 0;
}
