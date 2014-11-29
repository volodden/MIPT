#include <iostream>
#include <vector>

#include <fstream>
#include <exception>
#include <memory>

class Graph
{

private:

	std::vector < std::shared_ptr < std::vector < int > > > my_gr;
	int count_edges;

public:

	Graph(int n)
	{
		my_gr.reserve(n);
		for (int i = 0; i < n; ++i)
		{
			my_gr.push_back(std::make_shared < std::vector < int > >());
		}
	}

	void addVertex()
	{
		my_gr.push_back(std::make_shared < std::vector < int > >());
	}

	bool find(int v, int u)
	{
		for (int i = 0; i < my_gr[v]->size(); ++i)
		{
			if ((*my_gr[v])[i] == u)
			{
				return true;
			}
		}
		return false;
	}

	void addEdge(int v, int u)
	{
		if ((v >= my_gr.size()) || (u >= my_gr.size()) || (v < 0) || (u < 0) || (v == u))
		{
			throw "Error: edge is wrong.";
		}
		if (find(v, u) == false)
		{
			my_gr[v]->push_back(u);
		}
	}

	void printGraphInConsole()
	{
		for (int i = 0; i < my_gr.size(); ++i)
		{
			std::cout << i << " : ";
			if (my_gr[i]->empty() == true)
			{
				std::cout << "empty.\n";
			}
			else
			{
				for (int j = 0; j < my_gr[i]->size(); ++j)
				{
					std::cout << (*my_gr[i])[j];
					if (j + 1 != my_gr[i]->size())
					{
						std::cout << ", ";
					}
					else
					{
						std::cout << "\n";
					}
				}
			}
		}
	}
};

int main()
{
	int N, E;

	std::cin >> N;
	std::cin >> E;

	Graph gr(N);

	for (int i = 0; i < E; i++)
	{
		int v, u;
		std::cin >> v >> u;
		gr.addEdge(v, u);
	}

	gr.printGraphInConsole();
	return 0;
}
