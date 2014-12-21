#include <cstdio>
#include <vector>

class RMQTree
{
private:

    float m;
    int t;
    std::vector < float > tree;

public:

    RMQTree(int N)
    {
        t = 1;
        while (t < N)
        {
            t = t << 1;
        }
        tree.resize(2 * t - 1);
        m = -1;
        for (int i = t - 1; i < t + N - 1 ; ++i)
        {
            float k;
            scanf("%f", &k);
            tree[i] = k;
            m = (m < k) ? k : m;
        }
        ++m;
        for (int i = t + N - 1; i < 2 * t - 1; ++i)
        {
            tree[i] = m;
        }
        for (int i = t - 2; i >= 0; --i)
        {
            tree[i] = minimum(tree[i * 2 + 1], tree[i * 2 + 2]);
        }
    }

    float min(int a, int b)
    {
        a = a + t - 1;
        b = b + t - 2;
        float mm = m;
        while (a <= b)
        {
            if (a % 2 == 0)
            {
                mm = minimum(mm, tree[a]);
            }
            if (b % 2 == 1)
            {
                mm = minimum(mm, tree[b]);
            }
            a = a / 2;
            b = b / 2 - 1;
        }
        return mm;
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
    RMQTree rmq = RMQTree(N);
    scanf("%d", &N);
    int a, b;
    for (int i = 0; i < N; ++i)
    {
        scanf("%d %d", &a, &b);
        printf("%f\n", rmq.min(a, b));
    }
    return 0;
}
