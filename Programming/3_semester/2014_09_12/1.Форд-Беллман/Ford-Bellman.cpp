#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <fstream>
#include <climits>

double min(double a, double b)
{
   return (a < b) ? a : b;
}

class Graph
{

private:
    std::vector< std::vector < std::pair < int, double > > > graph;

public:

    Graph(int n)
    {
        graph.reserve(n);
        for (int i = 0; i < n; ++i)
        {
            graph.push_back(std::vector < std::pair <int, double> >());
        }
    }

    void addEdge(int out, int in, double weight)
    {
        graph[out].push_back(std::make_pair(in, weight));
    }

    void printGraph()
    {
        for (int i = 0; i < graph.size(); ++i)
        {
            for (int j = 0; j < graph[i].size(); ++j)
            {
                std::cout << "(" << i << " : " << graph[i][j].first << ") = " << graph[i][j].second << "\n";
            }
        }
    }

    void FordBellman(int v)
    {
        std::vector <double> dist (graph.size(), INT_MAX);
        dist[v] = 0;
        for (int i = 0; i < graph.size() - 1; ++i)
        {
            for (int j = 0; j < graph.size(); ++j)
            {
                for (int k = 0; k < graph[j].size(); ++k)
                {
                    if (dist[j] < INT_MAX)
                    {
                        dist[graph[j][k].first] = min(dist[graph[j][k].first], dist[j] + graph[j][k].second);
                    }
                }
            }
        }
        bool flag = true;
        for (int j = 0; j < graph.size(); ++j)
        {
            for (int k = 0; k < graph[j].size(); ++k)
            {
                if (dist[graph[j][k].first] > dist[j] + graph[j][k].second)
                {
                    flag = false;
                }
            }
        }
        if (flag)
        {
            for (int i = 0; i < graph.size(); i++)
            {
                std::cout << "(" << v << " -> " << i << ") = " << dist[i] << "\n";
            }
            std::cout << "\n";
        }
        else
        {
            std::cout << "This graph has negative cycle\n";
        }
    }
};

int main()
{
    int count, edgeCount, out, in;
    double weight;
    std::ifstream fin("input.txt");
    fin >> count;
	Graph myGraph(count);
    fin >> edgeCount;
    for (int i = 0; i < edgeCount; ++i)
    {
        fin >> out >> in >> weight;
        myGraph.addEdge(out, in, weight);
    }
	myGraph.FordBellman(0);
    return 0;
}
