#include <cstdio>
#include <vector>

class RMQSparseTable
{
private:

    std::vector < std::vector < float > > ST;
    std::vector < short > logarithm;
    std::vector < int > powerOfTwo;

public:

    RMQSparseTable(int N)
    {
        logarithm.resize(N + 1);
        char r = 0;
        int q = 1;
        powerOfTwo.push_back(1);
        powerOfTwo.push_back(2);
        for (int i = 1; i < N + 1; ++i)
        {
            if (i == powerOfTwo[powerOfTwo.size() - 1])
            {
                ++r;
                powerOfTwo.push_back(i * 2);
            }
            logarithm[i] = r;
        }
        ST.resize(logarithm[N] + 1);
        ST[0].resize(N);
        for (int i = 0; i < N; ++i)
        {
            float k;
            scanf("%f", &k);
            ST[0][i] = k;
        }
        int k = logarithm[ST[0].size()];
        for (int i = 1; i <= k; ++i)
        {
            ST[i].resize(ST[i-1].size() - powerOfTwo[i - 1]);
            for (int j = 0; j < ST[i].size(); ++j)
            {
                ST[i][j] = minimum(ST[i - 1][j], ST[i - 1][j + powerOfTwo[i - 1]]);
            }
        }
    }

    float min(int a, int b)
    {
        if (a + 1 != b)
        {
            return minimum(ST[logarithm[b - a]][a], ST[logarithm[b - a]][b - powerOfTwo[logarithm[b - a]]]);
        }
        else
        {
            return ST[0][a];
        }
    }

private:

    float minimum(float A, float B)
    {
        return (A < B) ? A : B;
    }
};

int main()
{
    int N = 0;
    scanf("%d", &N);
    RMQSparseTable rmq = RMQSparseTable(N);
    scanf("%d", &N);
    int a, b;
    for (int i = 0; i < N; ++i)
    {
        scanf("%d %d", &a, &b);
        printf("%f\n", rmq.min(a, b));
    }
    return 0;
}
