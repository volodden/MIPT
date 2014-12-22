#include <iostream>
#include <vector>
#include <cmath>

class HeapNode
{
public:

    HeapNode* parent;
    HeapNode* child;
    HeapNode* left;
    HeapNode* right;
    int degree;
    bool mark;
    double key;
    int value;

    HeapNode(double k, int v)
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

class FibHeap
{
private:

    HeapNode* min;
    int n;
    std::less<double> comp;

public:

    FibHeap()
    {
        n = 0;
        min = 0;
    }

    HeapNode* get_min()
    {
        return min;
    }

    HeapNode* extract_min()
    {
        HeapNode* z = min;
        if (z != 0)
        {
            if (min->child != 0)
            {
                std::vector< HeapNode* > childs;
                childs.push_back(min->child);
                for (HeapNode* it = min->child->right; it != min->child; it = it->right)
                {
                    childs.push_back(it);
                }
                for (int i = 0; i < childs.size(); ++i)
                {
                    childs[i]->left = min;
                    childs[i]->right = min->right;
                    childs[i]->parent = 0;
                    min->right->left = childs[i];
                    min->right = childs[i];
                }
            }
            if (min == min->right)
            {
                min = 0;
            }
            else
            {
                min->right->left = min->left;
                min->left->right = min->right;
                min = min->right;
                consolidate();
            }
            --n;
        }
        return z;
    }

    void insert(HeapNode* x)
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
            min->right = x;
            if (comp(x->key, min->key))
            {
                min = x;
            }
        }
        ++n;
    }

    FibHeap merge(FibHeap* other)
    {
        FibHeap* temp = new FibHeap();
        if (min == 0)
        {
            temp->min = other->min;
            temp->n = other->n;
            return *temp;
        }
        if (other->min == 0)
        {
            temp->min = min;
            temp->n = n;
            return *temp;
        }
        min->right->left = other->min;
        other->min->right = min->right;
        min->right = other->min;
        other->min->left = min;
        temp->min = min;
        if (comp(other->min->key, min->key))
        {
            temp->min = other->min;
        }
        temp->n = n + other->n;
        return *temp;
    }

    void decrease_key(HeapNode* node, double key)
    {
        if (comp(node->key, key))
        {
            return;
        }
        node->key = key;

        decrease(node, false);
    }

    void delete_node(HeapNode* node)
    {
        decrease(node, true);
        extract_min();
    }

private:

    void decrease(HeapNode* node, bool isKeyInf)
    {
        HeapNode* y = node->parent;
        if ((y != 0) && (isKeyInf || node->key < y->key))
        {
            cut(node, y);
            cascadingCut(y);
        }
        if (comp(node->key, min->key))
        {
            min = node;
        }
    }

    void consolidate()
    {
        std::vector<HeapNode*> A(n);
        for (unsigned int i = 0; i < A.size(); ++i)
        {
            A[i] = 0;
        }

        std::vector< HeapNode* > roots;
        roots.push_back(min);
        for (HeapNode* it = min->right; it != min; it = it->right)
        {
            roots.push_back(it);
        }
        for (int i = 0; i < roots.size(); ++i)
        {
            HeapNode* x = roots[i];
            int d = x->degree;
            while (A[d] != 0)
            {
                HeapNode* y = A[d];
                if (comp(y->key, x->key))
                {
                    HeapNode* temp = x;
                    x = y;
                    y = temp;
                }
                link(y, x);
                A[d] = 0;
                ++d;
            }
            A[d] = x;
        }
        min = 0;
        for (int i = 0; i < A.size(); ++i)
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
                A[i]->parent = 0;
                A[i]->left = min;
                A[i]->right = min->right;
                min->right->left = A[i];
                min->right = A[i];
                if (comp(A[i]->key, min->key))
                {
                    min = A[i];
                }
            }
        }
    }

    void link(HeapNode* y, HeapNode* x)
    {
        if (y == min)
        {
            min = y->right;
        }

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

    void cut(HeapNode* x, HeapNode* y)
    {
        if (x->left != x)
        {
            x->left->right = x->right;
            x->right->left = x->left;
            y->child = x->left;
        }
        else
        {
            y->child = 0;
        }
        y->degree -= 1;
        x->parent = 0;
        x->mark = false;
        x->left = min;
        x->right = min->right;
        min->right->left = x;
        min->right = x;
    }

    void cascadingCut(HeapNode* y)
    {
        HeapNode* z = y->parent;
        if (z != 0)
        {
            if (!(y->mark))
                y->mark = true;
            else
            {
                cut(y, z);
                cascadingCut(z);
            }
        }
    }
};

class Edge
{
public:
    int to;
    double length;

    Edge(int a, double b)
    {
        to = a;
        length = b;
    }
};

class Graph
{
public:
    bool addVertices(int n)
    {
        if (n < 1)
            return false;

        for (int i = 0; i < n; ++i)
            _graph.push_back(std::vector<Edge>());
        return true;
    }

    bool addEdge(int v1, int v2, double length)
    {
        if (v1 >= _graph.size() || v2 >= _graph.size())
            return false;

        _graph[v1].push_back(Edge(v2, length));
        return true;
    }

    void print()
    {
        int v = 0, e = 0;
        v = _graph.size();

        for (int i = 0; i < v; ++i)
        {
            e = _graph[i].size();
            std::cout << i << ": ";
            for (int j = 0; j < e; ++j)
                std::cout << _graph[i][j].to << " (" << _graph[i][j].length << ") ";

            std::cout << "\n";
        }
    }

    int getSize()
    {
        return _graph.size();
    }

    std::vector<Edge> getListOfEdges(int n)
    {
        if (n > _graph.size())
            return std::vector<Edge>();

        return _graph[n];
    }

private:
    std::vector<std::vector< Edge > > _graph;
};

std::vector<double> Dijkstra(Graph graph, int from)
{
    if (graph.getSize() < 1)
        return std::vector<double>();
    if (from < 0 || from >= graph.getSize())
        return std::vector<double>();

    std::vector<double> way;
    way = std::vector<double>(graph.getSize(), -1);
    way.at(from) = 0;

    FibHeap wayset;

    int currentVertex = from;
    for (int i = 0; i < graph.getSize(); ++i)
    {
        std::vector<Edge> vertex = graph.getListOfEdges(currentVertex);
        for (int j = 0; j < vertex.size(); ++j)
        {
            double dist = vertex.at(j).length + way.at(currentVertex);
            HeapNode* node = new HeapNode(dist, vertex.at(j).to);
            wayset.insert(node);

        }
        if (wayset.get_min() == 0)
        {
            break;
        }
        HeapNode* min = wayset.extract_min();
        while (way.at(min->value) != -1)
        {
            delete min;
            min = wayset.extract_min();
            if (min == 0)
                break;

        }

        if (min == 0)
        {
            break;
        }
        currentVertex = min->value;
        way.at(min->value) = min->key;
    }

    return way;
}

int main()
{
    Graph graph;
    std::vector<std::pair<double, double> > coord;

    int N = 0;
    double R = 0;

    std::cin >> N >> R;
    if (N < 3)
    {
        return -1;
    }
    double R2 = R*R;
    graph.addVertices(N);

    double bufX, bufY;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> bufX >> bufY;

        coord.push_back(std::make_pair(bufX, bufY));
    }

    for (int i = 0; i < N; ++i)
    {
        for (int j = i + 1; j < N; ++j)
        {
            double dist = (coord[i].first - coord[j].first) * (coord[i].first - coord[j].first)
                + (coord[i].second - coord[j].second) * (coord[i].second - coord[j].second);
            if (dist <= R2)
            {
                double sqrtDist = sqrt(dist);
                graph.addEdge(i, j, sqrtDist);
                graph.addEdge(j, i, sqrtDist);
            }
        }
    }

    std::vector<double> fromA = Dijkstra(graph, 0);
    std::vector<double> fromB = Dijkstra(graph, 1);

    std::pair<int, double> stats = std::make_pair(-1, -1);
    for (int i = 2; i < N; ++i)
    {
        if (coord[i].first < 0 &&
            fromA.at(i) != -1 && fromB.at(i) != -1 &&
            (fromA.at(i) + fromB.at(i) < stats.second || stats.second == -1))
            stats = std::make_pair(i, fromA.at(i) + fromB.at(i));
    }

    std::cout << stats.second;
    return 0;
}
