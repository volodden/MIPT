#include <iostream>
#include <vector>

#include <fstream>
#include <exception>
#include <memory>

#include <list>
#include <stack>

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

private:

	int ssc_n, time;
	std::stack<int> stck;
	std::vector<int> ssc;
	std::vector<int> func;
	std::vector<int> time_in;
	
	void DFS(int root)
	{
		if (time_in[root] == 0)
		{
			stck.push(root);
			func[root] = time_in[root] = ++time;
			for (int i = 0; i < my_gr[root]->size(); ++i)
			{
				if (ssc[(*my_gr[root])[i]] == 0)
				{
					if (time_in[(*my_gr[root])[i]] == 0)
					{
						DFS((*my_gr[root])[i]);
					}
					func[root] = func[root] < func[(*my_gr[root])[i]] ? func[root] : func[(*my_gr[root])[i]];
				}
			}

			if (func[root] == time_in[root])
			{
				int u;
				++ssc_n;
				std::cout << ssc_n << ": ";
				do
				{
					u = stck.top();
					ssc[u] = ssc_n;
					stck.pop();
					std::cout << u << " ";
				} while (u != root);
				std::cout << "\n";
			}
		}
	}

public:

	int tarjan()
	{
		time = 0;
		ssc_n = 0;
		int n = my_gr.size();
		ssc.resize(n);
		func.resize(n);
		time_in.resize(n);

		for (int i = 0; i < n; ++i)
		{
			ssc[i] = 0;
			func[i] = -1;
			time_in[i] = 0;
		}

		for (int i = 0; i < n; i++)
		{
			if (ssc[i] == 0)
			{
				DFS(i);
			}
		}

		/*
		for (int i = 0; i < ssc_n; i++)
		{
			std::cout << i << ": ";
			for (int j = 0; j < n; j++)
			{
				if (ssc[j] == i + 1)
					std::cout << j << " ";
			}
			std::cout << "\n";
		}
		*/

		return ssc_n;
	}

};

int main()
{
	std::ifstream file_in("input.txt");
	
	int N, E;
	file_in >> N;
	file_in >> E;
	Graph gr(N);
	
	try
	{
		for (int i = 0; i < E; ++i)
		{
			int v, u;
			file_in >> v >> u;
			gr.addEdge(v, u);
		}
	}
	catch (char* str)
	{
		std::cout << str;
	}

	gr.tarjan();
	return 0;
}
/*
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
*/