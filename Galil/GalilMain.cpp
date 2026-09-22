#include <iostream>
#include "Galil.h"

int main(void) {
	int a, b;
	std::cin >> a >> b;

	int c = a * b;

	std::cout << "Result is " << c << '\n';

	return 0;
}