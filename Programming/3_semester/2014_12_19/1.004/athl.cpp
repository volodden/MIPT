#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector < pair < int, int> > athlets;
	for (int i = 0; i < n; ++i)
    {
		int w, s;
		scanf("%d%d", &w, &s);
		athlets.push_back(make_pair(w, s));
	}
	sort(athlets.begin(), athlets.end());
	int weight = 0;
	int cnt = 0;
	for (int i = 0; i < athlets.size(); ++i)
	{
		if (athlets[i].second >= weight)
        {
			cnt++;
            weight += athlets[i].first;
		}
	}
	cout << cnt << endl;
	return 0;
}
