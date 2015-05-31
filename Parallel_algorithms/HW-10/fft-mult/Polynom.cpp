#include "Polynom.h"

Polynom::Polynom() : countOfThreads(COUNT_OF_THREADS), barrier(COUNT_OF_THREADS)
{
	int n, x;
	std::cout << "Enter the max degree of polynom.\n";
	std::cin >> n;
	polynom.resize(n + 1);
	for (int i = 0; i <= n; ++i)
	{
		std::cin >> x;
		polynom[n - i] = x;
	}
}

Polynom::Polynom(std::vector<int> newPolynom) : polynom(newPolynom), countOfThreads(COUNT_OF_THREADS), barrier(COUNT_OF_THREADS)
{
}

Polynom::Polynom(const Polynom& otherPolynom) : polynom(otherPolynom.polynom), countOfThreads(COUNT_OF_THREADS), barrier(COUNT_OF_THREADS)
{
}

Polynom::~Polynom()
{
}

std::vector<int> Polynom::multiply(const Polynom& otherPolynom)
{
	size = sizeOfArrayForAnswer(polynom.size(), otherPolynom.polynom.size());
	countOfThreads = findCountOfThreads(size);
	barrier.setCountOfThreads(countOfThreads);

	a.resize(size);
	b.resize(size);
	c.resize(size);
	std::vector<int> answer(size);
	for (unsigned int i = 0; i < polynom.size(); ++i)
	{
		a[i] = polynom[i];
	}
	for (unsigned int i = 0; i < otherPolynom.polynom.size(); ++i)
	{
		b[i] = otherPolynom.polynom[i];
	}

	std::vector<std::thread> threads;

	for (int id = 0; id < COUNT_OF_THREADS; id++)
	{
		threads.emplace_back([&]() { nestedFunction(id); });
	}
	for (auto& thread : threads)
	{
		thread.join();
	}

	for (int i = 0; i < size; ++i)
	{
		answer[i] = floor(c[i].real() + 0.5) / size;
	}

	int answerSize = answer.size() - 1;
	while ((answerSize > 0) && (answer[answerSize] == 0))
	{
		--answerSize;
	}
	answer.resize(answerSize + 1);

	return answer;
}

std::ostream& operator << (std::ostream& out, const Polynom& otherPolynom)
{
	for (unsigned int i = 0; i < otherPolynom.polynom.size(); ++i)
	{
		out << otherPolynom.polynom[i] << " ";
	}
	out << "\n";
	return out;
}

void Polynom::fft(std::vector<std::complex<double>>& data, bool inversion, int idOfThread)
{
	if (idOfThread == 0)
	{
		int n = data.size();
		int p = log2(n);
		std::vector<std::complex<double>> b(n);
		for (int k = 0; k < n; ++k)
		{
			std::bitset<sizeof(k) * CHAR_BIT> x = k;
			std::bitset<sizeof(k) * CHAR_BIT> y;
			for (int i = 0; i < p; i++)
			{
				y[i] = x[p - i - 1];
			}
			b[y.to_ulong()] = data[k];
		}
		for (int k = 0; k < n; k += 1)
		{
			data[k] = b[k];
		}
	}

	barrier.enter();

	int sizeOfData = data.size();

	int countOfBlockThreads = (sizeOfData / COUNT_OF_THREADS > COUNT_OF_THREADS ? COUNT_OF_THREADS : sizeOfData / COUNT_OF_THREADS);

	if (idOfThread < countOfBlockThreads)
	{
		int logarithm = log2(COUNT_OF_THREADS);
		for (int degree = 1; degree <= logarithm; ++degree)
		{
			double m = pow(2, degree);
			double theta = 2 * M_PI / m * invert(inversion);
			std::complex<double> omegaM(cos(theta), sin(theta));

			int begin = sizeOfData / countOfBlockThreads * idOfThread;
			int end = sizeOfData / countOfBlockThreads * (idOfThread + 1);
			for (int k = begin; k < end; k += m)
			{
				std::complex<double> omega(1, 0);
				for (int j = 0; j < m / 2; ++j)
				{
					std::complex<double> t = omega * data[k + j + m / 2];
					std::complex<double> u = data[k + j];
					data[k + j] = u + t;
					data[k + j + m / 2] = u - t;
					omega *= omegaM;
				}
			}
		}
	}

	barrier.enter();

	int logarithm = log2(sizeOfData);
	for (int degree = log2(COUNT_OF_THREADS) + 1; degree <= logarithm; ++degree)
	{
		double m = pow(2, degree);
		double theta = 2 * M_PI / m * invert(inversion);
		std::complex<double> omegaM(cos(theta), sin(theta));
		for (int k = idOfThread; k < sizeOfData; k += m)
		{
			std::complex<double> omegaTh(pow(omegaM, idOfThread));
			for (int j = 0; j < m / 2; j += COUNT_OF_THREADS)
			{
				std::complex<double> t = omegaTh * data[k + j + m / 2];
				std::complex<double> u = data[k + j];
				data[k + j] = u + t;
				data[k + j + m / 2] = u - t;
				omegaTh *= pow(omegaM, COUNT_OF_THREADS);
			}
		}
	}

	barrier.enter();
}

int Polynom::sizeOfArrayForAnswer(unsigned int a, unsigned int b)
{
	int currentSize = 1;
	int maxSize = (a > b ? a : b);
	while (currentSize < maxSize)
	{
		currentSize <<= 1;
	}
	return (currentSize << 1);
}

void Polynom::nestedFunction(int idOfThread)
{
	fft(a, false, idOfThread);
	fft(b, false, idOfThread);
	for (int i = idOfThread; i < size; i += COUNT_OF_THREADS)
	{
		c[i] = a[i] * b[i];
	}

	barrier.enter();

	fft(c, true, idOfThread);
}

int Polynom::invert(bool inversion)
{
	return (inversion ? -1 : 1);
}

int Polynom::findCountOfThreads(int size)
{
	int currentCount = 1;
	while (currentCount * currentCount < size)
	{
		currentCount <<= 1;
	}
	if (currentCount * currentCount > size)
	{
		currentCount >>= 1;
	}
	return currentCount;
}