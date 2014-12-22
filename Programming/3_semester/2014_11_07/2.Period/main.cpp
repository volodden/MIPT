#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::string s;
    std::cin >> s;
    std::vector <int> pref;
    int k = 0;
    for (int i = 1; i < s.length(); ++i)
    {
        while ((k > 0) && (s[i] != s[k]))
        {
            k = pref[k - 1];
        }
        if (s[i] == s[k])
        {
            ++k;
        }
        pref.push_back(k);
    }
    int answer = s.length() - pref[pref.size() - 1];
    std::cout << (s.length() % answer == 0 ? answer : s.length()) << '\n';
    return 0;
}
