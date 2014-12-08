#include <iostream>
#include <vector>

template < typename K, typename V, typename Compare = std::less < K > >
class FibNode
{
    FibNode* parent;
    FibNode* child;
    FibNode* left;
    FibNode* right;
    int degree;
    bool mark;
    K key;
    V value;

   FibNode(K k, V v)
    {
        parent = 0;
        child = 0;
        left = 0;
        right = 0;
        degree = 0;
        key = k;
        value = v;
    }
};

template < typename K, typename V, typename Compare = std::less < K > >
class FibHeap
{
private:

    FibNode<K, V>* min;
    int n;

public:

    FibHeap()
    {
        n = 0;
        min = 0;
    }

    FibNode<K, V>* fibHeapMinimum()
    {
        return min;
    }

    FibHeap fibHeapUnion(FibHeap& other)
    {
        FibHeap<K, V> temp = new FibHeap<K, V>();
        if (min == 0)
        {
            temp.min = other.min;
            temp.n = other.n;
            return temp;
        }
        if (other.min == 0)
        {
            temp.min = min;
            temp.n = n;
            return temp;
        }
        min->right->left = other.min;
        other.min->right = min->right;
        min->right = other.min;
        other.min->left = min;
        temp.min = min;
        if (min->key >= other.min->key)
        {
            temp.min = other.min;
        }
        temp.n = n + other.n;
        delete *this;
        delete other;
        return temp;
    }

    void fibHeapInsert(FibNode<K, V>* x)
    {
        x->degree = 0;
        x->parent = 0;
        x->child = 0;
        x->left = x;
        x->right = x;
        x->mark = false;
        if (min == 0)
        {
            min = x;
        }
        else
        {
            x->left = min;
            x->right = min->right;
            min->right->left = x;
            min->rigth = x;
            if (min->key > x->key)
            {
                min = x;
            }
        }
        ++n;
    }

    FibNode<K, V>* fibHeapExtract()
    {
        FibNode<K, V>* z = min;
        if (n == 1)
        {
            z = &(new FibNode<K, V>(min->key, min->value));
            delete *min;
            n = 0;
            min = 0;
            return z;
        }
        if (min != 0)
        {
            FibNode<K, V>* x = min->child;
            if (x != 0)
            {
                FibNode<K, V>* y = x->left;
                while (y != x)
                {
                    x->left->left->right = x;
                    x->left = x->left->left;
                    y->left = min;
                    y->right = min->right;
                    min->right->left = y;
                    min->right = y;
                    y->parent = 0;
                    y = x->left;
                }
                min->child = 0;
                x->left = min;
                x->right = min->right;
                min->right->left = x;
                min->right = x;
                x->parent = 0;
            }
            min->left->right = min->right;
            min->right->left = min->left;
            z = &(new FibNode<K, V>(min->key, min->value));
            if (z == z->right)
            {
                delete *min;
                min = 0;
            }
            else
            {
                min->right->left = min->left;
                min->left->right = min->right;
                FibNode<K, V>* temp = min->right;
                delete *min;
                min = temp;
                consolidate();
            }
            --n;
        }
        return z;
    }

    void fibHeapDecreaseKey(FibNode<K, V>* node, K key)
    {

    }

    void fibHeapDelete(FibNode<K, V>* node)
    {

    }

private:

    void consolidate()
    {
        std::vector< FibNode<K, V>* > A(n, 0);
        FibNode<K, V>* w = min;
        while (w != w->left)
        {
            FibNode<K, V>* x = w;
            int d = x->degree;
            while (A[d] != 0)
            {
                FibNode<K, V>* y = A[d];
                if (x->key > y->key)
                {
                    y->right->left = x;
                    y->left->right = x;
                    x->right->left = y;
                    x->left->right = y;
                    FibNode<K, V>* temp = y->right;
                    y->right = x->right;
                    x->right = temp;
                    temp = y->left;
                    y->left = x->left;
                    x->left = temp;
                }
                fibHeapLink(y, x);
                A[d] = 0;
                ++d;
            }
            A[d] = x;
            w = w->right;
        }
        min = 0;
        for (unsigned i = 0; i < A.size(); ++i)
        {
            if (A[i] != 0)
            {
                if (min == 0)
                {
                    min = A[i];
                    min->right = min;
                    min->left = min;
                    continue;
                }
                A[i]->left = min;
                A[i]->right = min->right;
                min->right->left = A[i];
                min->right = A[i];
                if (min->key > A[i]->key)
                {
                    min = A[i];
                }
            }
        }
    }

    void fibHeapLink(FibNode<K, V>* y, FibNode<K, V>* x)
    {
        y->left->right = y->right;
        y->right->left = y->left;
        y->parent = x;
        x->degree += 1;
        if (x->child == 0)
        {
            x->child = y;
            y->left = y;
            y->right = y;
        }
        else
        {
            y->right = x->child->right;
            y->left = x->child;
            x->child->right->left = y;
            x->child->right = y;
        }
        y->mark = false;
    }
};

int main()
{
    return 0;
}
