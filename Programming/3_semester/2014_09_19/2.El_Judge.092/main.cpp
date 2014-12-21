#include <cstdio>
#include <vector>
#include <stack>
#include <set>

class Graph
{

private:

    int countCars;
    std::vector < std::set < int > > crossroad;
    std::vector < bool > incoming;
    std::vector < int > time_in;
    std::vector < int > func;
    std::vector < int > ssc;

public:

    Graph(int n)
    {
        countCars = 0;
        ssc_count = 0;
        crossroad.resize(n);
        incoming.resize(n);
        time_in.resize(n);
        func.resize(n);
        ssc.resize(n);
        for (int i = 0; i < n; ++i)
        {
            incoming[i] = false;
            time_in[i] = 0;
            ssc[i] = -1;
        }
    }

    Graph(int n, int r)
    {
        countCars = 0;
        ssc_count = 0;
        crossroad.resize(n);
        incoming.resize(n);
        time_in.resize(n);
        func.resize(n);
        ssc.resize(n);
        for (int i = 0; i < n; ++i)
        {
            incoming[i] = false;
            time_in[i] = 0;
            ssc[i] = -1;
        }
        for (int i = 0; i < r; ++i)
        {
            int a, b;
            scanf("%d %d", &a, &b);
            addEdge(a - 1, b - 1);
        }
    }

    void addEdge(int a, int b)
    {
        crossroad[a].insert(b);
        incoming[b] = true;
    }

    void solve()
    {
        for (unsigned int i = 0; i < crossroad.size(); ++i)
        {
            if (incoming[i] == false)
            {
                ++countCars;
                DFS(i);
            }
        }

        for (unsigned i = 0; i < crossroad.size(); ++i)
        {
            if (time_in[i] >= 0)
            {
                tarjan(i);
                break;
            }
        }

        if (ssc_count < 2)
        {
            printf("%d\n", countCars + ssc_count);
            return;
        }

        Graph temp(ssc_count);
        for (unsigned i = 0; i < crossroad.size(); ++i)
        {
            for (std::set < int >::iterator it = crossroad[i].begin(); it != crossroad[i].end(); ++it)
            {
                if ((ssc[i] != ssc[*it]) && (ssc[i] > 0) && (ssc[*it] > 0))
                {
                    temp.addEdge(ssc[i] - 1, ssc[*it] - 1);
                }
            }
        }


        for (unsigned int i = 0; i < temp.crossroad.size(); ++i)
        {
            if (temp.incoming[i] == false)
            {
                ++temp.countCars;
                temp.DFS(i);
            }
        }

        countCars += temp.countCars;
        printf("%d", countCars);
    }

private:

    void DFS(int root)
    {
        time_in[root] = -1;
        for (std::set < int >::iterator it = crossroad[root].begin(); it != crossroad[root].end(); ++it)
        {
            if (time_in[*it] == 0)
            {
                DFS(*it);
            }
        }
    }

    int ssc_count, time;
    void tarjan(int root)
    {
        ssc_count = 0;
        time = 0;
        for (unsigned int i = 0; i < crossroad.size(); ++i)
        {
            if (time_in[i] >= 0)
            {
                ssc[i] = 0;
                func[i] = 0;
                time_in[i] = 0;
            }
        }

        for (unsigned int i = 0; i < crossroad.size(); ++i)
        {
            if (ssc[i] == 0)
            {
                DFSforTarjan(i);
            }
        }
    }

    std::stack < int > stackTar;
    void DFSforTarjan(int root)
    {
        stackTar.push(root);
        func[root] = time_in[root] = ++time;
        for (std::set < int >::iterator it = crossroad[root].begin(); it != crossroad[root].end(); ++it)
        {
            if (ssc[*it] == 0)
            {
                if (time_in[*it] == 0)
                {
                    DFSforTarjan(*it);
                }
                func[root] = (func[root] < func[*it]) ? func[root] : func[*it];
            }
        }
        if (func[root] == time_in[root])
        {
            int u;
            ++ssc_count;
            do
            {
                u = stackTar.top();
                stackTar.pop();
                ssc[u] = ssc_count;
            } while (u != root);
        }
    }
};

int main()
{
    int N, R;
    scanf("%d %d", &N, &R);
    Graph gr(N, R);
    gr.solve();
    return 0;
}
