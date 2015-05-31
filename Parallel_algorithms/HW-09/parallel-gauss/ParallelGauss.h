#ifndef PARALLEL_GAUSS_H_INCLUDED
#define PARALLEL_GAUSS_H_INCLUDED

#include <algorithm>
#include <thread>
#include <vector>
#include <utility>

#include "CyclicBarrier.h"
#include "ShellForAtomic.hpp"

#define DEFAULT_COUNT_OF_THREADS 4

#define Matrix std::vector<std::vector<double>>

class ParallelGauss
{
public:
	
	ParallelGauss(Matrix newMatrix);

	~ParallelGauss();

	bool solution(std::vector<double>& result);

private:

	bool checker();

	void nestedFunction(size_t id, CyclicBarrier& barrier);

	bool correctInput;
	unsigned int size;
	Matrix matrix;

	std::vector<double> res;
	std::vector<std::pair<double, int>> maximum;

	bool isSolve; // because only thread #0 change this value

	size_t countOfThreads;
};

#endif // PARALLEL_FAUSS_H_INCLUDED