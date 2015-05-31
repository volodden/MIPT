#include <iostream>
#include <vector>

#include "Polynom.h"

int main()
{
	Polynom aa({ 1, 3, 2 });
	Polynom bb({ 1, 2 });

	Polynom answer = aa.multiply(bb);
	std::cout << answer;

	return 0;
}

