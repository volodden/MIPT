#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
class Answer
{
private:

    std::vector< unsigned short > answer;
    std::vector< std::vector < int > > MaxSt;
    std::vector< int > M;
    std::vector< int > Q;
    unsigned short N, A, B;

    int max(int a, int b)
    {
        return (a > b) ? a : b;
    }

public:

    Answer()
    {
        scanf("%d %d %d ", &N, &A, &B);
        std::vector< int > P(N);
        M.resize(N);
        Q.resize(N);
        for (unsigned short i = 0; i < N; ++i)
        {
            scanf("%d %d %d", &P[i], &M[i], &Q[i]);
        }
        MaxSt.resize(N + 1);
        for (unsigned short int i = 0; i < N + 1; ++i)
        {
            MaxSt[i].resize(B + 1);
        }
        for (unsigned short i = 0; i < N + 1; ++i)
        {
            MaxSt[i][0] = 0;
        }
        for (unsigned short i = 1; i <= B; ++i)
        {
            MaxSt[0][i] = -1;
        }

        for (unsigned short i = 1; i < N + 1; ++i)
        {
            int t = 0;
            for (unsigned short j = 1; j <= B; ++j)
            {
                MaxSt[i][j] = MaxSt[i - 1][j];
                if (j >= M[i - 1])
                {
                    if ((j == M[i - 1] * (t + 1)) && (t < Q[i - 1]))
                    {
                        ++t;
                    }
                    for (int r = 1; r <= t; ++r)
                    {
                        if (MaxSt[i][j] < ((MaxSt[i - 1][j - r * M[i - 1]] == -1) ? -1 : MaxSt[i - 1][j - r * M[i - 1]] + r * P[i - 1]))
                        {
                            MaxSt[i][j] = MaxSt[i - 1][j - r * M[i - 1]] + r * P[i - 1];
                        }
                    }
                }
            }
        }
    }

    void solve()
    {
        int x = 0;
        for (int i = A; i <= B; ++i)
        {
            if (MaxSt[N][i] > MaxSt[N][x])
            {
                x = i;
            }
        }
        if (x == 0)
        {
            printf("-1\n");
            return;
        }
        printf("%d\n", MaxSt[N][x]);
        answer.resize(N);
        for (unsigned short i = 0; i < N; ++i)
        {
            answer[i] = 0;
        }
        findAns(N, x);
        for (unsigned short i = 0; i < N; ++i)
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
            if (MaxSt[i - 1][j] != MaxSt[i][j])
            {
                unsigned short r = j;
                for (int k = Q[i - 1]; k > 0; --k)
                {
                    if (j >= k * M[i - 1])
                    {
                        if (MaxSt[i - 1][j - k * M[i - 1]] > -1)
                        {
                            r = k;
                            break;
                        }
                    }
                }
                answer[i - 1] = r;
                j -= r * M[i - 1];
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
