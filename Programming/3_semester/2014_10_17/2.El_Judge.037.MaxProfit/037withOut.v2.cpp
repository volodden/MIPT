#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <fstream>

class Answer
{
private:

    std::vector< int > answer;
    std::vector< std::vector < int > > MaxSt;
    std::vector< int > M;
    std::map< int, int > W;
    std::map< int, int >::iterator it;
    int N, A, B, k;

    int max(int a, int b)
    {
        return (a > b) ? a : b;
    }

public:

    Answer()
    {
        k = 0;
        scanf("%d %d %d ", &N, &A, &B);
        std::vector< int > P = std::vector<int>(N);
        M = std::vector<int>(N);
        std::vector< int > Q = std::vector<int>(N);
        for (int i = 0; i < N; ++i)
        {
            scanf("%d %d %d", &P[i], &M[i], &Q[i]);
            W.insert(std::make_pair(k+1, i));
            k += Q[i];
        }
        MaxSt.resize(k+1);
        for (int i = 0; i < MaxSt.size(); ++i)
        {
            MaxSt[i].resize(B+1);
        }
        for (int i = 0; i <= k; ++i)
        {
            MaxSt[i][0] = 0;
        }
        for (int i = 1; i <= B; ++i)
        {
            MaxSt[0][i] = -1;
        }

        int t = -1;
        for (int i = 1; i <= k; ++i)
        {
            if (W.find(i) != W.end())
            {
                ++t;
            }
            for (int j = 1; j <= B; ++j)
            {
                if (j >= M[t])
                {
                    MaxSt[i][j] = max(MaxSt[i-1][j], (MaxSt[i-1][j-M[t]] == -1) ? -1 : MaxSt[i-1][j-M[t]] + P[t]);
                }
                else
                {
                    MaxSt[i][j] = MaxSt[i-1][j];
                }
            }
        }

#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <fstream>

class Answer
{
private:

    std::vector< int > answer;
    std::vector< std::map < int, int> > MaxSt;
    std::vector< int > M;
    std::map< int, int > W;
    std::map< int, int >::iterator it;
    int N, A, B, k;

    int max(int a, int b)
    {
        return (a > b) ? a : b;
    }

public:

    Answer()
    {
        k = 0;
        scanf("%d %d %d ", &N, &A, &B);
        std::vector< int > P = std::vector<int>(N);
        M = std::vector<int>(N);
        std::vector< int > Q = std::vector<int>(N);
        for (int i = 0; i < N; ++i)
        {
            scanf("%d %d %d", &P[i], &M[i], &Q[i]);
            W.insert(std::make_pair(k+1, i));
            k += Q[i];
        }
        MaxSt.resize(k+1);
        for (int i = 0; i <= k; ++i)
        {
            MaxSt[i].insert(std::make_pair(0, 0));
        }

        int t = -1;
        for (int i = 1; i <= k; ++i)
        {
            if (W.find(i) != W.end())
            {
                ++t;
            }
            for (int j = 1; j <= B; ++j)
            {
                if (j >= M[t])
                {
                    if (MaxSt[i-1].find(j) != MaxSt[i-1].end())
                    {
                        if (MaxSt[i-1].find(j-M[t]) != MaxSt[i-1].end())
                        {
                            MaxSt[i].insert(std::make_pair(j, max(MaxSt[i-1].find(j)->second,
                                                                  MaxSt[i-1].find(j-M[t])->second + P[t])));
                        }
                        else
                        {
                            MaxSt[i].insert(std::make_pair(j, MaxSt[i-1].find(j)->second));
                        }
                    }
                    else
                    {
                        if (MaxSt[i-1].find(j-M[t]) != MaxSt[i-1].end())
                        {
                            MaxSt[i].insert(std::make_pair(j, MaxSt[i-1].find(j-M[t])->second + P[t]));
                        }
                    }
                }
                else
                {
                    if (MaxSt[i-1].find(j) != MaxSt[i-1].end())
                    {
                        MaxSt[i].insert(std::make_pair(j, MaxSt[i-1].find(j)->second));
                    }
                }
            }
        }

        std::ofstream out("output.csv");

        out << ";";
        for (int i = 0; i <= k; ++i)
        {
            out << i << ";";
        }
        out << "\n";
        for (int j = 0; j <= B; ++j)
        {
            out << j << ";";
            for (int i = 0; i <= k; ++i)
            {
                if (MaxSt[i].find(j) != MaxSt[i].end())
                {
                    out << MaxSt[i].find(j)->second;
                }
                out << ";";
            }
            out << "\n";
        }
    }

    void solve()
    {
        int x = 0;
        for (int i = A; i <= B; ++i)
        {
            if ((MaxSt[k].find(i) != MaxSt[k].end()) && (MaxSt[k].find(i)->second > MaxSt[k].find(x)->second))
            {
                x = i;
            }
        }
        if (MaxSt[k].find(x)->second < A)
        {
            printf("-1\n");
            return;
        }
        printf("%d\n", MaxSt[k].find(x)->second);
        answer = std::vector< int >(N, 0);
        it = W.end();
        --it;
        findAns(k, x);
        for (int i = 0; i < answer.size(); ++i)
        {
            std::cout << answer[i] << "\n";
        }
    }

private:

    void findAns(int i, int j)
    {
        while (true)
        {
            if (MaxSt[i].find(j)->second == 0)
            {
                break;
            }
            if ((MaxSt[i-1].find(j) == MaxSt[i-1].end()) || (MaxSt[i-1].find(j)->second != MaxSt[i].find(j)->second))
            {
                while(it->first > i)
                {
                    --it;
                }
                ++answer[it->second];
                j -= M[it->second];
            }
            --i;
        }
    }
};

int main()
{
    Answer answer;
    answer.solve();
    return 0;
}

    }

    void solve()
    {
        int x = 0;
        for (int i = A; i <= B; ++i)
        {
            if (MaxSt[k][i] > MaxSt[k][x])
            {
                x = i;
            }
        }
        if (MaxSt[k][x] < A)
        {
            printf("-1\n");
            return;
        }
        printf("%d\n", MaxSt[k][x]);
        answer = std::vector< int >(N, 0);
        it = W.end();
        --it;
        findAns(k, x);
        for (int i = 0; i < answer.size(); ++i)
        {
            std::cout << answer[i] << "\n";
        }
    }

private:

    void findAns(int i, int j)
    {
        while (true)
        {
            if (MaxSt[i][j] == 0)
            {
                break;
            }
            if (MaxSt[i-1][j] != MaxSt[i][j])
            {
                while(it->first > i)
                {
                    --it;
                }
                ++answer[it->second];
                j -= M[it->second];
            }
            --i;
        }
    }

};

int main()
{
    Answer answer;
    answer.solve();
    return 0;
}
