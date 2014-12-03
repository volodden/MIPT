#include <iostream>
#include <vector>

int main()
{
    long long int N, K, c, l = 0, r = 0, m, mm = 0;
    std::cin >> N >> K;
    std::vector<long long int> lengths(N);
    for (long long int i = 0; i < N; ++i)
    {
        std::cin >> lengths[i];
        r += lengths[i];
    }
    ++r;

    while (r != l+1)
    {
        c = 0;
        m = (r + l) / 2;
        for (long long int i = 0; i < N; ++i)
        {
            c += lengths[i] / m;
        }
        if (c < K)
        {
            r = m;
        }
        else
        {
            l = m;
            mm = mm < m ? m : mm;
        }
    }
    std::cout << mm;
    return 0;
}
