#include <iostream>
#include <vector>
#include <utility>
#include <fstream>

class Graph
{

private:

	std::vector < std::vector < std::pair < int, double > > > my_gr;

public:

	Graph(int n)
	{
		my_gr.reserve(n);

		for (int i = 0; i < n; ++i)
		{
			my_gr.push_back(std::vector < std::pair < int, double > >());
		}
	}

	bool find(int v, int u)
	{
		for (int i = 0; i < my_gr[v].size(); ++i)
		{
			if (my_gr[v][i].first == u)
			{
				return true;
			}
		}
		return false;
	}

	void addEdge(int u, double v, double r)
	{
		if ((v >= my_gr.size()) || (u >= my_gr.size()) || (v < 0) || (u < 0) || (v == u))
		{
			throw "Error: edge is wrong.";
		}
		if (find(v, u) == false)
		{
			my_gr[v].push_back(std::make_pair(u, r));
		}
	}

	void printGraphInConsole()
	{
		for (int i = 0; i < my_gr.size(); ++i)
		{
			std::cout << "\n" << i << "  ";
			for (int j = 0; j < my_gr[i].size(); ++j)
			{
				std::cout << my_gr[i][j].first << " (" << my_gr[i][j].second << ") ";
			}
		}
		std::cout << "\n";
	}

	std::vector < double > djekstra(int ST)
	{
		std::vector < double > dist;
		std::vector < bool > vist;
		std::vector < int > forest;

		int MX = 1000000;

		forest.reserve(my_gr.size());
		for (int i = 0; i < my_gr.size(); ++i)
		{
			dist.push_back(MX);
			vist.push_back(false);
		}
		dist[ST] = 0;
		vist[ST] = true;
		for (int i = 0; i < my_gr[ST].size(); ++i)
		{
			dist[my_gr[ST][i].first] = my_gr[ST][i].second;
		}
		forest.push_back(ST);

		int j = -1;
		do
		{
			int index1, index2, index3;
			++j;
			int mn = MX;
			for (int i = 0; i < forest.size(); ++i)
			{
				for (int k = 0; k < my_gr[forest[i]].size(); ++k)
				{
					if ((vist[my_gr[forest[i]][k].first] == false) && (dist[my_gr[forest[i]][k].first] <= mn))
					{
						mn = dist[my_gr[forest[i]][k].first];
						index1 = forest[i];
						index2 = my_gr[forest[i]][k].first;
						index3 = k;
					}
				}
			}
			vist[index2] = true;
			forest.push_back(index2);

			for (int i = 0; i < my_gr[index2].size(); ++i)
			{
				if ((vist[my_gr[index2][i].first] == false)
					&& (dist[index2] + my_gr[index2][i].second < dist[my_gr[index2][i].first]))
				{
					dist[my_gr[index2][i].first] = dist[index2] + my_gr[index2][i].second;
				}
			}
		} while ((j + 1 < my_gr.size()) && (forest.size() != my_gr.size()));

		return dist;
	}

};

int main()
{
	int N;
	double E;

	std::ifstream file_in("input.txt");
	file_in >> N;
	file_in >> E;

	Graph gr(N);

	for (int i = 0; i < E; ++i)
	{
		int u, v;
		double r;
		file_in >> u >> v >> r;
		gr.addEdge(u, v, r);
//		gr.addEdge(v, u, r);
	}

	gr.printGraphInConsole();

	std::vector < double > rast = gr.djekstra(0);
	for (int i = 0; i < N; ++i)
	{
		std::cout << i << ": " << rast[i] << "\n";
	}
	return 0;
}
