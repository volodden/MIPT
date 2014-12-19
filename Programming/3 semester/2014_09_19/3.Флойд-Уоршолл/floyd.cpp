#include <iostream>
#include <vector>
#include <fstream>
#include <limits>

double min(double a, double b)
{
    return a < b ? a : b;
}

class Graph
{
private:

    std::vector < std::vector < double > > _graph;

public:
    Graph(int n) :_graph(n, std::vector< double >(n, std::numeric_limits<double>::infinity()))
    {
        for (int i = 0; i < n; i++)
            _graph[i][i] = 0;
    }

    void addEdge(int v1, int v2, double w)
    {
        _graph[v1][v2] = w;
    }

    std::vector < std::vector < double > > getGraph()
    {
        return _graph;
    }
};

void FloydWarshall(Graph& graph)
{
    std::vector < std::vector < double > > dist = graph.getGraph();
    int n = dist.size();
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            for (int k = 0; k < n; ++k)
            {
                if (dist[j][i] < std::numeric_limits < double >::infinity()
                    && dist[i][k] < std::numeric_limits < double >::infinity())
                {
                    dist[j][k] = min(dist[j][k], dist[j][i] + dist[i][k]);
                }
            }
        }
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (dist[i][j] != std::numeric_limits < double >::infinity())
            {
                std::cout << i << " -> " << j << ": " << dist[i][j] << '\n';
            }
            else
            {
                std::cout << i << " -> " << j << ": INF (NO WAY)" << '\n';
            }
        }
    }
}

int main()
{
    std::ifstream input("input.txt");

    int verticesNumber = 0;
    int edgesNumber = 0;
    int vertexFrom = 0;
    int vertexTo = 0;
    double weight;


    input >> verticesNumber;

    if (verticesNumber == 0)
    {
        return 0;
    }

    input >> edgesNumber;

    Graph graph(verticesNumber);
    return 0;

    for (int i = 0; i < edgesNumber; ++i)
    {
        input >> vertexFrom >> vertexTo >> weight;
        graph.addEdge(vertexFrom, vertexTo, weight);
    }
    input.close();

    FloydWarshall(graph);
    return 0;
}
