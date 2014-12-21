#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <queue>

//#include <fstream>

class Node
{
public:

    Node* parent;
    Node* grandpa;
    int level;
    int number;
    std::set < int > childs;

    Node(int n)
    {
        parent = 0;
        grandpa = 0;
        level = 0;
        number = n;
    }
};

class Tree
{
public:

    std::vector < Node > nodes;

    Tree(int n)
    {
//        std::ifstream in("input.txt");
        for (unsigned i = 0; i < n + 1; ++i)
        {
            nodes.push_back(Node(i));
        }

        for (int i = 0; i < n; ++i)
        {
            int v, p;
//            in >> v >> p;
            scanf("%d%d", &v, &p);
            nodes[v].parent = &(nodes[p]);
            nodes[v].grandpa = &(nodes[p]);
            nodes[v].number = v;
            nodes[p].childs.insert(v);
        }

        std::queue < int > q;
        q.push(0);
        nodes[0].level = 0;
        nodes[0].parent = &(nodes[0]);
        nodes[0].grandpa = &(nodes[0]);
        while (!q.empty())
        {
            int t = q.front();
            q.pop();
            for (std::set < int >::iterator it = nodes[t].childs.begin(); it != nodes[t].childs.end(); ++it)
            {
                q.push(*it);
                nodes[*it].level = nodes[t].level + 1;
                if (nodes[t].childs.size() == 1)
                {
                    nodes[*it].grandpa = nodes[t].grandpa;
                }
            }
        }
    }

    void find(int first, int second)
    {
        std::vector< Node >::iterator f = nodes.begin() + first;
        std::vector< Node >::iterator s = nodes.begin() + second;
        while (true)
        {
            while (f->level != s->level)
            {
                if (f->grandpa == s->grandpa)
                {
                    std::vector< Node >::iterator p = nodes.begin() + (f->level < s->level ? f : s)->number;
                    std::vector< Node >::iterator c = nodes.begin() + (f->level > s->level ? f : s)->number;
                    while (p->level != c->level)
                    {
                        c = nodes.begin() + c->parent->number;
                    }
                    if (p == c)
                    {
                        std::cout << (f->level < s->level ? f : s)->number << '\n';
                    }
                    else
                    {
                        std::cout << (f->level < s->level ? f : s)->grandpa->number << '\n';
                    }
                    return;
                }
//                while (f->level > s->level)
                if (f->level > s->level)
                {
                    f = nodes.begin() + f->grandpa->number;
                }
//                while (f->level < s->level)
                else
                {
                    s = nodes.begin() + s->grandpa->number;
                }
            }
            if (f == s)
            {
                std::cout << f->number << '\n';
                return;
            }
            f = nodes.begin() + f->grandpa->number;
            s = nodes.begin() + s->grandpa->number;
        }
    }

    void print()
    {
        std::cout << "Root 0: level = " << nodes[0].level << '\n';
        for (int i = 1; i < nodes.size(); ++i)
        {
            std::cout << "Node #" << i << ": level = " << nodes[i].level << "; parent = " << nodes[i].parent->number << "; grandpa = " << nodes[i].grandpa->number << '\n';
        }
    }
};

int main()
{
    int n = 0;
    scanf("%d", &n);
    Tree tree(n);
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        int f, s;
        scanf("%d%d", &f, &s);
        tree.find(f, s);
    }
    return 0;
}
