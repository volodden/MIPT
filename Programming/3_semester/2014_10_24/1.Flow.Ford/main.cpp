#include <iostream>
#include <limits.h>
#include <vector>

int findPath(std::vector < std::vector < int > > &array, std::vector < bool > isVisited, int start, int finish, int f)
{
    if (start == finish)
    {
        return f;
    }
    isVisited[start] = true;
    for (int next = 0; next < isVisited.size(); ++next)
    {
        if ((!isVisited[next]) && (array[start][next] > 0))
        {
            int flow = findPath(array, isVisited, next, finish, f < array[start][next] ? f : array[start][next]);
            if (flow > 0)
            {
                array[start][next] -= flow;
                array[next][start] += flow;
                return flow;
            }
        }
    }
    return 0;
}

int maxFlow(std::vector < std::vector < int > > array, int start, int finish)
{
    int flow = 0;
    while (true)
    {
        std::vector < bool > vct(array.size());
        int df = findPath(array, vct, start, finish, INT_MAX);
        if (df == 0)
        {
            return flow;
        }
        flow += df;
    }
}

int main()
{
    return 0;
}
