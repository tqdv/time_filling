#include "time_filling.hpp"
#include <iostream>

using std::cout;

int main () {
	t_fl::Coord a (0, 0);

	auto [x, y] = a;
	cout << "Simple test to see if Coord works\n";
	cout << x << ", " << y << "\n";

	return 0;
}
