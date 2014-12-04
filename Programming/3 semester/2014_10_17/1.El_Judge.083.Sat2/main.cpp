#include <iostream>
#include <vector>
#include <set>
#include <stack>

class Graph
{
private:

    int N, M;
    std::vector < std::set < int > > links;
    std::vector < int > ssc;
    std::vector < std::pair < int, int > > rules;
    std::vector < short > values;
    std::vector < short > clean;

public:

    Graph()
    {
        std::cin >> N >> M;
        links.resize(2 * N + 1);
        values.assign(N + 1, -1);
        clean.assign(N + 1, -1);
        for (int i = 0; i < M; ++i)
        {
            int in, out, zero;
            std::cin >> in >> out;
            if (out != 0)
            {
                std::cin >> zero;
                rules.push_back(std::make_pair(absN(in), absN(out)));
                if (clean[absLessN(absN(in))] == -1)
                {
                    clean[absLessN(absN(in))] = 1 - ((absN(in) - 1) / N);
                }
                else
                {
                    if (clean[absLessN(absN(in))] != 1 - ((absN(in) - 1) / N))
                    {
                        clean[absLessN(absN(in))] = -2;
                    }
                }
                if (clean[absLessN(absN(out))] == -1)
                {
                    clean[absLessN(absN(out))] = 1 - ((absN(out) - 1) / N);
                }
                else
                {
                    if (clean[absLessN(absN(out))] != (1 - (absN(out) - 1) / N))
                    {
                        clean[absLessN(absN(out))] = -2;
                    }
                }
            }
            else
            {
                rules.push_back(std::make_pair(absN(in), -1));
                if (clean[absLessN(absN(in))] == -1)
                {
                    clean[absLessN(absN(in))] = 1 - ((absN(in) - 1) / N);
                }
                else
                {
                    if (clean[absLessN(absN(in))] != (1 - (absN(in) - 1) / N))
                    {
                        clean[absLessN(absN(in))] = -2;
                    }
                }
            }
        }
        if (!deleteUselessRules())
        {
            std::cout << "No\n";
        }
        else
        {
            sat2();
        }
    }

private:

    void sat2()
    {
        for (int i = 0; i < M; ++i)
        {
            if (rules[i].first != -1)
            {
                addVerix(otr(absN(rules[i].first)), absN(rules[i].second));
                addVerix(otr(absN(rules[i].second)), absN(rules[i].first));
            }
        }

        tarjan();

        for (int i = 1; i <= N; ++i)
        {
            if ((ssc[i] == ssc[i + N]) && (ssc[i] != 0))
            {
                std::cout << "No\n";
                return;
            }
        }
        std::cout << "Yes\n";
        for (int i = 1; i <= N; ++i)
        {
            if (((ssc[i] == 0) && (values[i] == 1)) || ((ssc[i] != 0) && (ssc[i] < ssc[i + N])))
            {
                std::cout << i << " ";
            }
        }
        std::cout << "0";
    }

    int absN(int A)
    {
        return (A > 0) ? A : N - A;
    }

    int otr(int A)
    {
        return ((A - 1 + N) % (2 * N) + 1);
    }

    int absLessN(int A)
    {
        return (A <= N) ? A : A - N;
    }

    void addVerix(int in, int out)
    {
        links[in].insert(out);
    }

    bool deleteUselessRules()
    {
        std::set < int > proofs;
        bool flag = true;
        for (int i = 1; i <= N; ++i)
        {
            if (clean[i] >= 0)
            {
                values[i] = clean[i];
                proofs.insert(i);
            }
            if (clean[i] == -1)
            {
                values[i] == 0;
            }
        }
        while (flag)
        {
            flag = false;
            for (int i = 0; i < M; ++i)
            {
                if (rules[i].second == -1)
                {
                    if (rules[i].first != -1)
                    {
                        if (rules[i].first <= N)
                        {
                            if (values[absLessN(rules[i].first)] == 0)
                            {
                                return false;
                            }
                            values[absLessN(rules[i].first)] = 1;
                        }
                        else
                        {
                            if (values[absLessN(rules[i].first)] == 1)
                            {
                                return false;
                            }
                            values[absLessN(rules[i].first)] = 0;

                        }
                        flag = true;
                        proofs.insert(absLessN(rules[i].first));
                        rules[i] = std::make_pair(-1, -1);
                    }
                    continue;
                }
                std::set < int >::iterator it = proofs.find(absLessN(rules[i].first));
                if (it != proofs.end())
                {
                    if (((values[*it] == 0) && (rules[i].first <= N))
                     || ((values[*it] == 1) && (rules[i].first > N)))
                    {
                        if (rules[i].second <= N)
                        {
                            if (values[absLessN(rules[i].second)] == 0)
                            {
                                return false;
                            }
                            values[absLessN(rules[i].second)] = 1;
                        }
                        else
                        {
                            if (values[absLessN(rules[i].second)] == 1)
                            {
                                return false;
                            }
                            values[absLessN(rules[i].second)] = 0;

                        }
                        flag = true;
                        proofs.insert(absLessN(rules[i].second));
                    }
                    rules[i] = std::make_pair(-1, -1);
                    continue;
                }
                it = proofs.find(absLessN(rules[i].second));
                if (it != proofs.end())
                {
                    if (((values[*it] == 0) && (rules[i].second <= N))
                     || ((values[*it] == 1) && (rules[i].second > N)))
                    {
                        if (rules[i].first <= N)
                        {
                            if (values[absLessN(rules[i].first)] == 0)
                            {
                                return false;
                            }
                            values[absLessN(rules[i].first)] = 1;
                        }
                        else
                        {
                            if (values[absLessN(rules[i].first)] == 1)
                            {
                                return false;
                            }
                            values[absLessN(rules[i].first)] = 0;

                        }
                        flag = true;
                        proofs.insert(absLessN(rules[i].first));
                    }
                    rules[i] = std::make_pair(-1, -1);
                    continue;
                }
                if (rules[i].first == rules[i].second)
                {
                    if (rules[i].first <= N)
                    {
                        if (values[absLessN(rules[i].first)] == 0)
                        {
                            return false;
                        }
                        values[absLessN(rules[i].first)] = 1;
                    }
                    else
                    {
                        if (values[absLessN(rules[i].first)] == 1)
                        {
                            return false;
                        }
                        values[absLessN(rules[i].first)] = 0;
                    }
                    flag = true;
                    proofs.insert(absLessN(rules[i].first));
                    rules[i] = std::make_pair(-1, -1);
                    continue;
                }
                if (absLessN(rules[i].first) == absLessN(rules[i].second))
                {
                    flag = true;
                    rules[i] = std::make_pair(-1, -1);
                }
            }
        }
        return true;
    }

    int time;
    int ssc_n;
    std::stack < int > st;
    std::vector < int > func;
    std::vector < int > time_in;

    void tarjan()
    {
        time = 0;
        ssc_n = 0;
        func.resize(2 * N + 1);
        time_in.resize(2* N + 1);
        ssc.resize(2 * N + 1);
        for (int i = 1; i < 2 * N + 1; ++i)
        {
            time_in[i] = 0;
            func[i] = 0;
            ssc[i] = 0;
        }

        for (int i = 1; i < 2 * N + 1; ++i)
        {
            if ((ssc[i] == 0) && (values[absLessN(i)] == -1))
                DFS(i);
        }
    }

    void DFS(int root)
    {
        st.push(root);
        func[root] = time_in[root] = ++time;
        for (std::set < int >::iterator it = links[root].begin(); it != links[root].end(); ++it)
        {
            if (ssc[*it] == 0)
            {
                if (time_in[*it] == 0)
                {
                    DFS(*it);
                }
                func[root] = (func[root] < func[*it] ? func[root] : func[*it]);
            }
        }

        if (func[root] == time_in[root])
        {
            ++ssc_n;
            int u;
            do
            {
                u = st.top();
                ssc[u] = ssc_n;
                st.pop();
            } while (u != root);
        }
    }
};

int main()
{
    Graph g;
    return 0;
}
