#include <iostream>
#include <vector>
#include <cmath>

class Graph
{

private:

	std::vector < std::vector < double > > my_gr;
	std::vector < std::pair < double, double> > vers;

public:

	Graph(int n)
	{
		my_gr.resize(n);
		for (int i = 0; i < n; ++i)
		{
			my_gr[i].resize(n);
		}
	}

	void addEdge(int I, double R, double a, double b)
	{
		vers.push_back(std::make_pair(a, b));
		for (int i = 0; i < I; ++i)
		{
			if ((vers[i].first - vers[I].first)*(vers[i].first - vers[I].first) +
				(vers[i].second - vers[I].second)*(vers[i].second - vers[I].second) <= R*R)
			{
				my_gr[I][i] = my_gr[i][I] =
					sqrt((vers[i].first - vers[I].first)*(vers[i].first - vers[I].first) +
					(vers[i].second - vers[I].second)*(vers[i].second - vers[I].second));
			}
			else
			{
				my_gr[I][i] = my_gr[i][I] = 0;
			}
		}
	}

	void printGraphInConsole()
	{
		for (int i = 0; i < my_gr.size(); ++i)
		{
			std::cout << "\n" << i << "  ";
			for (int j = 0; j < my_gr[i].size(); ++j)
			{
				std::cout << my_gr[i][j] << " ";
			}
		}
	}

	std::vector < double > djekstra(int ST)
	{
		std::vector < double > dist;
		std::vector < bool > vist;

		int MX = 1000000;

		for (int i = 0; i < my_gr.size(); ++i)
		{
			dist.push_back(MX);
			vist.push_back(false);
		}
		dist[ST] = 0;

		int index;

		for (int j = 0; j < my_gr.size(); ++j)
		{
			int mn = MX;
			for (int i = 0; i < my_gr.size(); ++i)
			{
				if ((vist[i] == false) && (dist[i] <= mn))
				{
					mn = dist[i];
					index = i;
				}
			}
			vist[index] = true;
			for (int i = 0; i < my_gr.size(); ++i)
			{
				if ((vist[i] == false)
					&& (my_gr[index][i] != 0)
					&& (dist[index] != MX)
					&& (dist[index] + my_gr[index][i] < dist[i]))
				{
					dist[i] = dist[index] + my_gr[index][i];
				}
			}
		}

		//        std::cout << "—тоимость пути из начальной вершины до остальных:\t\n";
		//        for (int i = 0; i < my_gr.size(); ++i)
		//        {
		//            if (dist[i] != MX)
		//            {
		//                std::cout << ST << " > " << i + 1 << " = " << dist[i] << std::endl;
		//            }
		//            else
		//            {
		//                std::cout << ST << " > " << i + 1 << " = " << "маршрут недоступен" << std::endl;
		//            }
		//        }
		return dist;
	}

};

int main()
{
	int N;
	double R;

	std::cin >> N;
	std::cin >> R;

	Graph gr(N);

	std::vector < int > otr;

	for (int i = 0; i < N; ++i)
	{
		double a, b;
		std::cin >> a >> b;
		if (a < 0)
		{
			otr.push_back(i);
		}
		gr.addEdge(i, R, a, b);
	}

	std::vector < double > otr1;
	std::vector < double > otr2;

	otr1 = gr.djekstra(0);
	otr2 = gr.djekstra(1);

	double Rast = otr1[otr[0]] + otr2[otr[0]];
	for (int i = 1; i < otr.size(); ++i)
	{
		if (otr1[otr[i]] + otr2[otr[i]] < Rast)
		{
			Rast = otr1[otr[i]] + otr2[otr[i]];
		}
	}
	std::cout << Rast << "\n";
	return 0;
}
