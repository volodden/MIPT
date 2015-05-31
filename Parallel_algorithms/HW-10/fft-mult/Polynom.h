#ifndef POLYNOM_H_INCLUDED
#define POLYNOM_H_INCLUDED

#include <iostream>
#include <vector>
#include <complex>
#include <thread>
#include <bitset>

#include "CyclicBarrier.h"

#define M_PI 3.1415926535
#define COUNT_OF_THREADS 2

class Polynom
{
public:

	Polynom();
	Polynom(std::vector<int> newPolynom);
	Polynom(const Polynom& otherPolynom);

	~Polynom();

	std::vector<int> multiply(const Polynom& otherPolynom);

	friend std::ostream& operator << (std::ostream& out, const Polynom& otherPolynom);

private:

	void fft(std::vector<std::complex<double>>& data, bool inversion, int idOfThread);

	int sizeOfArrayForAnswer(unsigned int a, unsigned int b);
	void nestedFunction(int idOfThread);	
	int invert(bool inversion);
	int findCountOfThreads(int size);

	std::vector<int> polynom;
	
	std::vector<std::complex<double>> a;
	std::vector<std::complex<double>> b;
	std::vector<std::complex<double>> c;

	int size;
	int countOfThreads;

	CyclicBarrier barrier;
};


#endif // POLYNOM_H_INCLUDED