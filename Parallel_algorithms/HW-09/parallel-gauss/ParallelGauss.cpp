#include "ParallelGauss.h"

ParallelGauss::ParallelGauss(Matrix newMatrix) : size(newMatrix.size()), matrix(newMatrix), isSolve(true)
{
	correctInput = checker();

	countOfThreads = std::thread::hardware_concurrency();
	countOfThreads = (countOfThreads == 0 ? DEFAULT_COUNT_OF_THREADS : countOfThreads);

	maximum.resize(size);
	maximum.assign(countOfThreads, std::make_pair(0.0, 0));
}

ParallelGauss::~ParallelGauss()
{
}

bool ParallelGauss::solution(std::vector<double>& result)
{
	if (!correctInput)
	{
		return false;
	}

	result.resize(size);
	res.resize(size);
	for (unsigned int i = 0; i < size; ++i)
	{
		result[i] = res[i];
	}

	CyclicBarrier barrier(countOfThreads);

	std::vector<std::thread> threads;
	for (unsigned int i = 0; i < countOfThreads; ++i)
	{
		threads.emplace_back([&]() { nestedFunction(i, std::ref(barrier)); });
	}
	for (auto& thread : threads)
	{
		thread.join();
	}

	res.resize(size);
	for (unsigned int i = 0; i < size; ++i)
	{
		result[i] = res[i];
	}

	return isSolve;
}

bool ParallelGauss::checker()
{
	for (unsigned int i = 0; i < size; ++i)
	{
		if (matrix[i].size() - 1 != size)
		{
			return false;
		}
	}
	return true;
}


void ParallelGauss::nestedFunction(size_t id, CyclicBarrier& barrier)
{
	for (int column = 0; column < size - 1; ++column)
	{
		for (int i = column + id; i < size; i += countOfThreads)
		{
			if (abs(matrix[i][column]) > maximum[id].first)
			{
				maximum[id].first = abs(matrix[i][column]);
				maximum[id].second = i;
			}
		}

		barrier.enter();

		if (id == 0)
		{
			auto maxElement = std::max_element(maximum.begin(), maximum.end());
			std::swap(matrix[column], matrix[maxElement->second]);
		}

		barrier.enter();

		for (int i = column + 1 + id; i < size; i += countOfThreads)
		{
			double coef = matrix[i][column] / matrix[column][column];
			for (int c = column; c < size + 1; ++c)
			{
				matrix[i][c] -= coef * matrix[column][c];
			}
		}

		barrier.enter();
		
		if (id == 0)
		{
			maximum.assign(countOfThreads, std::make_pair(0.0, 0));
		}

		barrier.enter();
	}

	for (int column = size - 1; column >= 0; --column)
	{
		if (matrix[column][column] == 0.0)
		{
			if (matrix[column][size] != 0.0)
			{
				if (id == 0)
				{
					isSolve = false;
				}

				barrier.enter();

				return;
			}
			else
			{
				if (id == 0)
				{
					res[column] = 0.0; // or any number, but it more difficult
				}
			}
		}
		else
		{
			double coef = matrix[column][size] / matrix[column][column];
			if (id == 0)
			{
				res[column] = coef;
			}
			for (int i = column - 1 - id; i >= 0; i -= countOfThreads)
			{
				matrix[i][size] -= coef * matrix[i][column];
				matrix[i][column] = 0;
			}
		}

		barrier.enter();
	}

	barrier.enter();
}