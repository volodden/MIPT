#include <iostream>
#include <vector>
#include <limits.h>

int maxFlow(std::vector< std::vector <int> > &array, int start, int finish)
{
    int n = array.size();

    std::vector< int > h(n);
    h[start] = n - 1;

    std::vector< int > maxh(n);
    std::vector< int > e(n);
    std::vector< std::vector <int> > f(n, std::vector< int >(n));

    for (int i = 0; i < n; ++i)
    {
        f[start][i] = array[start][i];
        f[i][start] = -f[start][i];
        e[i] = array[start][i];
    }

    int sz = 0;
    while (true)
    {
        if (sz == 0)
        {
            for (int i = 0; i < n; ++i)
            {
                if ((i != start) && (i != finish) && (e[i] > 0))
                {
                    if ((sz != 0) && (h[i] > h[maxh[0]]))
                    {
                        sz = 0;
                    }
                    maxh[sz++] = i;
                }
            }
        }
        if (sz == 0)
        {
            break;
        }
        while (sz != 0)
        {
            int i = maxh[sz - 1];
            bool pushed = false;
            for (int j = 0; (j < n) && (e[i] != 0); ++j)
            {
                if ((h[i] == h[j] + 1) && (array[i][j] - f[i][j] > 0))
                {
                    int flow = array[i][j] - f[i][j] < e[i] ? array[i][j] - f[i][j] : e[i];
                    f[i][j] += flow;
                    f[j][i] -= flow;
                    e[j]    += flow;
                    e[i]    -= flow;
                    if (e[i] == 0)
                    {
                        --sz;
                    }
                    pushed = true;
                }
            }
            if (!pushed)
            {
                h[i] = INT_MAX;
                for (int j = 0; j < n; ++j)
                {
                    if ((h[i] > h[j] + 1) && (array[i][j] - f[i][j] > 0))
                    {
                        h[i] = h[j] + 1;
                    }
                }
                if (h[i] > h[maxh[0]])
                {
                    sz = 0;
                    break;
                }
            }
        }
    }

    int flow = 0;
    for (int i = 0; i < n; ++i)
    {
        flow += f[start][i];
    }
    return flow;
}

int main()
{
    return 0;
}
