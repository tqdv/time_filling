#include "time_filling.hpp"
#include <iostream>

using std::cout;

int main () {
	t_fl::init_default_base (1);
	t_fl::Coord a (0, 0);
	t_fl::Hexagon h (a, 1);
	auto v = h.explode();


	cout << "Simple test to see if Hexagon.explode works\n";
	for (const auto &e : v) {
		const auto &[x, y] = e.center;
		cout << x << ", " << y << "\n";
	}

	return 0;
}
