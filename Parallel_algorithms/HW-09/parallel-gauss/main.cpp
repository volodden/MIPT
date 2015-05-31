#include <iostream>
#include <vector>

#include "ParallelGauss.h"

int main()
{
    unsigned int n;
    std::cin >> n;
    std::vector<std::vector<double>> matrix(n);
	std::vector<double> result;

	// equations
	for (unsigned int i = 0; i < n; ++i)
	{
		matrix[i].resize(n + 1);
		for (unsigned int j = 0; j < n; ++j)
		{
            std::cin >> matrix[i][j];
        }
    }

	// free values
	for (unsigned int j = 0; j < n; ++j)
	{
        std::cin >> matrix[j][n];
    }

	ParallelGauss solution(matrix);
	if (solution.solution(result))
	{
		for (int i = 0; i < n; i++)
		{
			std::cout << result[i] << " ";
		}
		std::cout << "\n";
	}
	else
	{
		std::cout << "No solution\n";
	}

    return 0;
}