#include <iostream>
#include <fstream>

//All keys are different!

class RBTree
{

private:

    class Node
    {
    public:

        int key;
        int value;
        Node* parent;
        Node* left;
        Node* right;
        bool color;

        Node()
        {
            key = 0;
            value = 0;
            parent = 0;
            left = 0;
            right = 0;
            color = false;
        }

        Node(int key, int value)
        {
            this->key = key;
            this->value = value;
            parent = 0;
            left = 0;
            right = 0;
            color = false;
        }
    };

    Node* root;
    Node* NIL;

    void leftRotate(Node* x)
    {
        Node* y = x->right;
        x->right = y->right;
        if (y->left != NIL)
        {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == NIL)
        {
            root = y;
        }
        else
        {
            if (x == x->parent->left)
            {
                x->parent->left = y;
            }
            else
            {
                x->parent->right = x;
            }
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* x)
    {
        Node* y = x->left;
        x->left = y->left;
        if (y->right != NIL)
        {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == NIL)
        {
            root = y;
        }
        else
        {
            if (x == x->parent->left)
            {
                x->parent->left = y;
            }
            else
            {
                x->parent->right = x;
            }
        }
        y->right = x;
        x->parent = y;
    }

    Node* search(Node* x, int key) const
    {
        while ((x != NIL) && (key != x->key))
        {
            x = key < x->key ? x->left : x->right;
        }
        return x;
    }

    Node* minimum(Node* x) const
    {
        while (x->left != NIL)
        {
            x = x->left;
        }
        return x;
    }

    Node* maximum(Node* x) const
    {
        while (x->right != NIL)
        {
            x = x->right;
        }
        return x;
    }

    Node* successor(Node* x) const
    {
        if (x == NIL)
        {
            return x;
        }
        if (x->right != NIL)
        {
            return minimum(x->right);
        }
        Node* y = x->parent;
        while ((y != NIL) && (x == y->right))
        {
            x = y;
            y = y->parent;
        }
        return y;
    }

    Node* predeccessor(Node* x) const
    {
        if (x == NIL)
        {
            return x;
        }
        if (x->left != NIL)
        {
            return maximum(x->left);
        }
        Node* y = x->parent;
        while ((y != NIL) && (x == y->left))
        {
            x = y;
            y = y->parent;
        }
        return y;
    }

    void transplant(Node* u, Node* v)
    {
        if (u->parent == NIL)
        {
            root = v;
        }
        else
        {
            if (u == u->parent->left)
            {
                u->parent->left = v;
            }
            else
            {
                u->parent->right = v;
            }
        }
        v->parent = u->parent;
    }

public:

    RBTree()
    {
        NIL = new Node();
        root = NIL;
        root->parent = NIL;
        root->left = NIL;
        root->right = NIL;
    }

    bool rbInsert(std::pair<int, int> param)
    {
        Node* z = new Node(param.first, param.second);
        Node* y = NIL;
        Node* x = root;
        while (x != NIL)
        {
            y = x;
            if (z->key < x->key)
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }

        z->parent = y;
        if (y == NIL)
        {
            root = z;
        }
        else
        {
            if (z->key < y->key)
            {
                y->left = z;
            }
            else
            {
                if (z->key > y->key)
                {
                    y->right = z;
                }
                else
                {
                    delete z;
                    return false;
                }
            }
        }
        z->left = NIL;
        z->right = NIL;
        z->color = true;
        while (z->parent->color == true)
        {
            if (z->parent == z->parent->parent->left)
            {
                y = z->parent->parent->right;
                if (y->color == true)
                {
                    z->parent->color = false;
                    y->color = false;
                    z->parent->parent->color = true;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->right)
                    {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = false;
                    z->parent->parent->color = true;
                    rightRotate(z->parent->parent);
                }
            }
            else
            {
                y = z->parent->parent->left;
                if (y->color == true)
                {
                    z->parent->color = false;
                    y->color = false;
                    z->parent->parent->color = true;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->left)
                    {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = false;
                    z->parent->parent->color = true;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = false;
        return true;
    }

    std::pair < bool, int > rbSearch(int key) const
    {
        Node* x = search(root, key);
        return std::make_pair(x == NIL ? false : true, x->value);
    }

    std::pair < bool, std::pair < int, int > > rbMinimum() const
    {
        Node* x = minimum(root);
        return std::make_pair(x == NIL ? false : true, std::make_pair(x->key, x->value));
    }

    std::pair < bool, std::pair < int, int > > rbMaximum() const
    {
        Node* x = maximum(root);
        return std::make_pair(x == NIL ? false : true, std::make_pair(x->key, x->value));
    }

    std::pair < bool, std::pair < int, int > > rbSuccessor(int key) const
    {
        Node* x = successor(search(root, key));
        return std::make_pair(x == NIL ? false : true, std::make_pair(x->key, x->value));
    }

    std::pair < bool, std::pair < int, int > > rbPredecessor(int key) const
    {
        Node* x = predeccessor(search(root, key));
        return std::make_pair(x == NIL ? false : true, std::make_pair(x->key, x->value));
    }

    bool rbDelete(int key)
    {
        Node* z = search(root, key);
        if (z == NIL)
        {
            return false;
        }
        Node* y = z;
        Node* x;
        bool original = y->color;
        if (z->left == NIL)
        {
            x = z->right;
            transplant(z, z->right);
        }
        else
        {
            if (z->right == NIL)
            {
                x = z->left;
                transplant(z, z->left);
            }
            else
            {
                y = minimum(z->right);
                original = y->color;
                x = y->right;
                if (y->parent == z)
                {
                    x->parent = y;
                }
                else
                {
                    transplant(y, y->right);
                    y->right = z->right;
                    y->right->parent = y;
                }
                transplant(z, y);
                y->left = z->left;
                y->left->parent = y;
                y->color = z->color;
            }
        }
        if (original == false)
        {
            while ((x != root) && (x->color == false))
            {
                if (x == x->parent->left)
                {
                    Node* w = x->parent->right;
                    if (w->color == true)
                    {
                        w->color = false;
                        x->parent->color = true;
                        leftRotate(x->parent);
                        w = x->parent->right;
                    }
                    if ((w->left->color == false) && (w->right->color == false))
                    {
                        w->color = true;
                        x = x->parent;
                    }
                    else
                    {
                        if (w->right->color == false)
                        {
                            w->left->color = false;
                            w->color = true;
                            rightRotate(w);
                            w = x->parent->right;
                        }
                        w->color = x->parent->color;
                        x->parent->color = false;
                        w->right->color = false;
                        leftRotate(x->parent);
                        x = root;
                    }
                }
                else
                {
                    Node* w = x->parent->left;
                    if (w->color == true)
                    {
                        w->color = false;
                        x->parent->color = true;
                        rightRotate(x->parent);
                        w = x->parent->left;
                    }
                    if ((w->right->color == false) && (w->left->color == false))
                    {
                        w->color = true;
                        x = x->parent;
                    }
                    else
                    {
                        if (w->left->color == false)
                        {
                            w->right->color = false;
                            w->color = true;
                            leftRotate(w);
                            w = x->parent->left;
                        }
                        w->color = x->parent->color;
                        x->parent->color = false;
                        w->left->color = false;
                        rightRotate(x->parent);
                        x = root;
                    }
                }
            }
        }
        delete z;
        return true;
    }

    ~RBTree()
    {
        while (root != NIL)
        {
            rbDelete(root->key);
        }
        delete NIL;
    }
};


int main()
{
    RBTree tree;
    tree.rbInsert(std::make_pair(0, 0));
    tree.rbDelete(0);
    return 0;
}
