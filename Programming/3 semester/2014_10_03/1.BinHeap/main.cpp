#include <iostream>

template < typename K, typename V, typename Compare = std::less < K > >
class BinNode
{
    BinNode* parent;
    BinNode* child;
    BinNode* sibling;
    int degree;
    K key;
    V value;

    BinNode(K k, V v)
    {
        parent = 0;
        child = 0;
        sibling = 0;
        degree = 0;
        key = k;
        value = v;
    }
};

template < typename K, typename V, typename Compare = std::less < K > >
class BinHeap
{
private:

    BinNode<K, V>* head;

public:

    BinHeap()
    {
        head = 0;
    }

    BinNode<K, V>* binHeapMinimum()
    {
        bool flag = false;
        BinNode<K, V>* y = 0;
        BinNode<K, V>* x = head;
        K m;
        while (x != 0)
        {
            if ((x->key < m) || (!flag))
            {
                flag = true;
                m = x->key;
                y = x;
            }
            x = x->sibling;
        }
        return y;
    }

    BinHeap binHeapUnion(BinHeap& other)
    {
        head = binMerge(head, other.head);
        if (head == 0)
        {
            return *this;
        }
        BinNode<K, V>* prev = 0;
        BinNode<K, V>* x = head;
        BinNode<K, V>* next = x->sibling;
        while (next != 0)
        {
            if ((x->degree != next->degree) || ((next->sibling != 0) && (next->sibling->degree == x->degree)))
            {
                prev = x;
                x = next;
            }
            else
            {
                if (x->key <= next->key)
                {
                    x->sibling = next->sibling;
                    binHeapLink(next, x);
                }
                else
                {
                    if (prev == 0)
                    {
                        head = next;
                    }
                    else
                    {
                        prev->sibling = next;
                    }
                    binHeapLink(x, next);
                    x = next;
                }
            }
            next = x->sibling;
        }
        delete other;
        return *this;
    }

    void binHeapInsert(BinNode<K, V>* x)
    {
        BinHeap<K, V> H;
        x->parent = 0;
        x->sibling = 0;
        x->child = 0;
        x->degree = 0;
        H->head = x;
        *this = binHeapUnion(*this, H);
    }

    BinNode<K, V>* binHeapExtract()
    {
        BinNode<K, V>* minNode = binHeapMinimum();
        if (minNode == head)
        {
            head = head->sibling;
        }
        else
        {
            BinNode<K, V>* temp = head;
            while (temp->sibling != minNode)
            {
                temp = temp->sibling;
            }
            temp->sibling = minNode->sibling;
        }
        minNode->sibling = 0;
        BinNode<K, V>* listChildrens = minNode->child;
        minNode->child = 0;
        if (minNode->child == 0)
        {
            return minNode;
        }
        BinNode<K, V>* next = listChildrens->sibling;
        listChildrens->sibling = 0;
        listChildrens->parent = 0;
        while (next != 0)
        {
            next = next->sibling;
            BinNode<K, V>* temp = listChildrens;
            listChildrens = listChildrens->sibling;
            listChildrens->sibling = temp;
            listChildrens->parent = 0;
        }
        BinHeap<K, V> temp = new BinHeap<K, V>();
        temp.head = listChildrens;
        *this = binHeapUnion(*this, temp);
        delete temp;
        return minNode;
    }

    void binHeapDecreaseKey(BinNode<K, V>* node, K key)
    {
        if (node->key <= key)
        {
            return;
        }
        node->key = key;
        BinNode<K, V>* y = node;
        BinNode<K, V>* z = node->parent;
        while ((z != 0) && (z->key < y->key))
        {
            BinNode<K, V>* temp = y;
            y->key = z->key;
            y->value = z->value;
            z->key = temp->key;
            z->value = temp->value;
            y = z;
            z = z->parent;
        }
    }

    void binHeapDelete(BinNode<K, V>* node)
    {
        K key = binHeapMinimum()->key;
        binHeapDecreaseKey(node, key - 1);
        BinNode<K, V>* tempNode = binHeapExtract();
        delete *tempNode;
    }

private:

    void binHeapLink(BinNode<K, V>* y, BinNode<K, V>* z)
    {
        y->parent = z;
        y->sibling = z->child;
        z->child = y;
        z->degree += 1;
    }

    BinNode<K, V>* binHeapMerge(BinNode<K, V>* first, BinNode<K, V>* second)
    {
        BinNode<K, V>* result;
        BinNode<K, V>* current;
        if (first->degree < second->degree)
        {
            result = first;
            first = first->sibling;
        }
        else
        {
            result = second;
            second = second->sibling;
        }
        current = result;
        while ((first != 0) && (second != 0))
        {
            if (first->degree < second->degree)
            {
                current->sibling = first;
                first = first->sibling;
            }
            else
            {
                current->sibling = second;
                second = second->sibling;
            }
            current = current->sibling;
        }
        if (first != 0)
        {
            current->sibling = first;
        }
        if (second != 0)
        {
            current->sibling = second;
        }
        return result;
    }

};

int main()
{
    return 0;
}
