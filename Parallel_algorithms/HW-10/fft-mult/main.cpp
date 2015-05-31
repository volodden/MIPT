#include <iostream>
#include <vector>

#include "Polynom.h"

int main()
{
	Polynom aa({ 1, 3, 15 });
	Polynom bb({ 1, 2, 0, 5});

	Polynom answer = aa.multiply(bb);
	std::cout << answer;

	return 0;
}
