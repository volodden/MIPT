#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
//#include <fstream>

class Labirinth
{
private:

	int startX;
	int startY;
	int n;
	int m;
	std::vector < std::vector < int > > rectangle;
	std::map < std::pair < int, int >, std::pair < int, int > > tunnels;
	std::set < std::pair < int, int > > exits;
	std::map < std::pair < int, int >, std::pair < int, int > > path;

public:

	Labirinth()
	{
		//		std::ifstream in("input.txt");
		//  in >> n >> m >> startX >> startY;
		std::cin >> n >> m >> startX >> startY;
		--startX;
		--startY;

		rectangle.resize(n);
		int wall;
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < m; ++j)
			{
				//				in >> wall;
				scanf("%d", &wall);
				rectangle[i].push_back(wall == 0 ? 0 : -1);
			}
		}
		int t;
		//		in >> t;
		std::cin >> t;
		for (int i = 0; i < t; ++i)
		{
			int ix, iy, ox, oy;
			//			in >> ix >> iy >> ox >> oy;
			scanf("%d%d%d%d", &ix, &iy, &ox, &oy);
			tunnels.insert(std::make_pair(std::make_pair(ix - 1, iy - 1), std::make_pair(ox - 1, oy - 1)));
		}
		//		in >> t;
		std::cin >> t;
		for (int i = 0; i < t; ++i)
		{
			int ex, ey;
			//			in >> ex >> ey;
			scanf("%d%d", &ex, &ey);
			exits.insert(std::make_pair(ex - 1, ey - 1));
			rectangle[ex - 1][ey - 1] = -2;
		}
		rectangle[startX][startY] = 1;
	}

	void solve()
	{
		std::pair < int, int > answer(preSolve());
		if ((answer.first == -1) && (answer.second == -1))
		{
			return;
		}
		print(answer.first, answer.second);
	}

private:

	void print(int x, int y)
	{
		std::map < std::pair < int, int >, std::pair < int, int > >::iterator it = path.find(std::make_pair(x, y));
		if ((it->second.first != -2) && (it->second.second != -2))
		{
			print(it->second.first, it->second.second);
		}
		std::cout << x + 1 << ' ' << y + 1 << '\n';
	}

	std::pair < int, int > preSolve()
	{
		std::multimap < int, std::pair < int, int > > road;
		road.insert(std::make_pair(1, std::make_pair(startX, startY)));
		path.insert(std::make_pair(std::make_pair(startX, startY), std::make_pair(-2, -2)));
		int x;
		int y;
		int steps;
		while (true)
		{
			if (road.empty())
			{
				std::cout << "Impossible\n";
				return std::make_pair(-1, -1);
			}
			x = road.begin()->second.first;
			y = road.begin()->second.second;
			steps = rectangle[x][y];
			road.erase(road.begin());
			std::map < std::pair < int, int >, std::pair < int, int > >::iterator it = tunnels.find(std::make_pair(x, y));
			if (it != tunnels.end())
			{
				if (rectangle[it->second.first]
					[it->second.second] == 0)
				{
					rectangle[it->second.first][it->second.second] = steps + 1;
					road.insert(std::make_pair(steps + 1, std::make_pair(it->second.first, it->second.second)));
					path.insert(std::make_pair(std::make_pair(it->second.first, it->second.second), std::make_pair(x, y)));
				}
			}
			for (int i = 0; i < 2; ++i)
			{
				for (int j = -1; j < 1; ++j)
				{
					if ((x + i + j < n) && (x + i + j >= 0) && (y + i - j - 1 < m) && (y + i - j - 1 >= 0))
					{
						if (rectangle[x + i + j][y + i - j - 1] == 0)
						{
							rectangle[x + i + j][y + i - j - 1] = steps + 1;
							road.insert(std::make_pair(steps + 1, std::make_pair(x + i + j, y + i - j - 1)));
							path.insert(std::make_pair(std::make_pair(x + i + j, y + i - j - 1), std::make_pair(x, y)));
						}
						if (rectangle[x + i + j][y + i - j - 1] == -2)
						{
							std::cout << steps + 1 << '\n';
							path.insert(std::make_pair(std::make_pair(x + i + j, y + i - j - 1), std::make_pair(x, y)));
							return std::make_pair(x + i + j, y + i - j - 1);
						}
					}
				}
			}
		}
	}
};

int main()
{
	Labirinth lab;
	lab.solve();
	return 0;
}
